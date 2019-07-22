
#include "kernel.h"

__constant float EPSILON = 0.00003f; /* required to compensate for limited float precision */
__constant float PI = 3.14159265359f;
__constant int SAMPLES = 1;



Ray get_camera_ray(int x, int y, t_cam *cam, int *seed0, int *seed1);
Ray get_precise_ray(int x, int y, t_cam *cam);
static float get_random( int *seed0, int *seed1);
float3 reflect(float3 vector, float3 n);
float3 refract(float3 vector, float3 n, float refrIndex);


Ray get_precise_ray(int x, int y, t_cam *cam)
{
	Ray ray;

	ray.origin = (float3)(0,0,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
		-cam->f_length);
	ray.dir.x *= cam->ratio;
	ray.dir.y *= cam->ratio;
	ray.dir = normalize(ray.dir);
	return(ray);
}


static float get_random( int *seed0, int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);  
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union 
	{
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

Ray get_camera_ray(int x, int y, t_cam *cam, int *seed0, int *seed1)
{
	Ray ray;

	float a = get_random(seed0, seed1) * 2 * PI; //random angle
	float r = sqrt(get_random(seed0, seed1) * cam->aperture); //random radius
	float ax = r * cos(a); //random x
	float ay = r * sin(a); // random y

	ray.origin = (float3)(ax,ay,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
		-cam->f_length);
	ray.dir.x = (ray.dir.x + get_random(seed0, seed1) - 0.5f) * cam->ratio;
	ray.dir.y = (ray.dir.y + get_random(seed0, seed1) - 0.5f) * cam->ratio;
	ray.dir -= ray.origin;
	ray.dir = normalize(ray.dir);
	return(ray);
}



// float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds)
// {
// 	float rand1 = 2.0f * PI * get_random(seeds);
// 	float rand2 = get_random(seeds) * max_r;
// 	float rand2s = sqrt(rand2);

// 	float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) :
// 		(float3)(1.0f, 0.0f, 0.0f);
// 	float3 u = normalize(cross(axis, w));
// 	float3 v = cross(w, u);

// 	float3 newdir = normalize(u * cos(rand1)*rand2s +
// 		v*sin(rand1)*rand2s +w*sqrt(1.0f - rand2));

// 	return (newdir);
// }

float3 reflect(float3 vector, float3 n) 
{ 
    return vector - 2 * dot(vector, n) * n; 
} 

float3 refract(float3 vector, float3 n, float refrIndex)
{
	float cosI = -dot(n, vector);
	float cosT2 = 1.0f - refrIndex * refrIndex * (1.0f - cosI * cosI);
	return (refrIndex * vector) + (refrIndex * cosI - sqrt( cosT2 )) * n;
}

static Ray createCamRay(const int x_coord, const int y_coord, const int width, const int height){

	float fx = (float)x_coord / (float)width;  /* convert int in range [0 - width] to float in range [0-1] */
	float fy = (float)y_coord / (float)height; /* convert int in range [0 - height] to float in range [0-1] */

	/* calculate aspect ratio */
	float aspect_ratio = (float)(width) / (float)(height);
	float fx2 = (fx - 0.5f) * aspect_ratio;
	float fy2 = fy - 0.5f;

	/* determine position of pixel on screen */
	float3 pixel_pos = (float3)(fx2, -fy2, 0.0f);

	/* create camera ray*/
	Ray ray;
	ray.origin = (float3)(0.0f, 0.1f, 2.f); /* fixed camera position */
	ray.dir = normalize(pixel_pos - ray.origin); /* vector from camera to pixel on screen */
    return ray;
}
 
static float ft_solve(float a, float b, float c)
{
	float  disc = b * b - 4*a*c;
   	float temp = 1/(2*a);
	float res;

 	if (disc < 0.0f) 
		return 0.0f;
	
	disc = sqrt(disc);
	if ((res = (-b - disc) * temp) > EPSILON)
		return res;
    if ((res = (-b + disc) * temp) > EPSILON)
		return res;
	return(0.f);
}

				/* (__global Sphere* sphere, const Ray* ray) */
static float intersect_cone(const t_obj* cone, const Ray* ray) /* version using local copy of sphere */
{
	float3	x = ray->origin - cone->position;
	float	a = dot(ray->dir, cone->v);
	float	c = dot(x, cone->v);
	float	temp = 1 + cone->radius * cone->radius;
	float	b = 2.0 * (dot(ray->dir, x) - temp * a * c);

	a = dot(ray->dir, ray->dir) - temp * a * a;
	c = dot(x, x) - temp * c * c;	
	return (ft_solve(a, b, c));
}

static float intersect_sphere(const t_obj* sphere, const Ray* ray) /* version using local copy of sphere */
{
	float3 rayToCenter = ray->origin - sphere->position;
    float a = 1;
    float b = 2*dot(rayToCenter, ray->dir);
    float c = dot(rayToCenter, rayToCenter) - sphere->radius*sphere->radius;	
	return (ft_solve(a, b, c));
}

double		intersect_plane(const t_obj* plane, const Ray* ray)
{
	double	a;
	double	b;
	a = dot(plane->position, ray->dir);//ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, plane->point), plane->normal);
	//b = ft_vec3_dot_multiply(ray->dir, plane->normal);
	if (a == 0)
		return (0);
	b = -(dot(plane->position, ray->origin) + plane->plane_d) / a;
	return (b < EPSILON) ? 0 : b;
}

static double		intersect_cylinder(const t_obj* cylinder, const Ray* ray)
{
	float3	x = ray->origin - cylinder->position;
	double	a = dot(ray->dir, cylinder->v);
	double	c = dot(x, cylinder->v);
	double	b = 2 * (dot(ray->dir, x) - a * dot(x, cylinder->v));
	double	d;

	a = dot(ray->dir, ray->dir) - a * a;
	c = dot(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (ft_solve(a, b, c));
}

static bool intersect_scene(__constant t_obj* spheres, const Ray* ray, float* t, int* sphere_id, const int sphere_count)
{
	/* initialise t to a very large number, 
	so t will be guaranteed to be smaller
	when a hit with the scene occurs */

	float inf = 1e20f;
	*t = inf;

	/* check if the ray intersects each sphere in the scene */
	for (int i = 0; i < sphere_count; i++)  {
		
		t_obj sphere = spheres[i]; /* create local copy of sphere */
		
		/* float hitdistance = intersect_sphere(&spheres[i], ray); */
		float hitdistance = 0; 
		if (sphere.type == SPHERE)
			hitdistance = intersect_sphere(&sphere, ray);
		else if (sphere.type == CYLINDER)
			hitdistance = intersect_cylinder(&sphere, ray);
		else if (sphere.type == CONE)
			hitdistance = intersect_cone(&sphere, ray);
		else if (sphere.type == PLANE)
			hitdistance = intersect_plane(&sphere, ray);
		/* keep track of the closest intersection and hitobject found so far */
		if (hitdistance != 0.0f && hitdistance < *t) {
			*t = hitdistance;
			*sphere_id = i;
		}
	}
	return *t < inf; /* true when ray interesects the scene */
}


/* the path tracing function */
/* computes a path (starting from the camera) with a defined number of bounces, accumulates light/color at each bounce */
/* each ray hitting a surface will be reflected in a random direction (by randomly sampling the hemisphere above the hitpoint) */
/* small optimisation: diffuse ray directions are calculated using cosine weighted importance sampling */

static float3 trace(__constant t_obj* spheres, const Ray* camray, const int sphere_count, const int* seed0, const int* seed1)
{
	Ray ray = *camray;

	float3 accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
	unsigned int max_trace_depth = 16;

	for (int bounces = 0; bounces < max_trace_depth; bounces++)
	{
		float t;   /* distance to intersection */
		int hitsphere_id = 0; /* index of intersected sphere */

		/* if ray misses scene, return background colour */
		if (!intersect_scene(spheres, &ray, &t, &hitsphere_id, sphere_count))
			return mask * (float3)(0.7f, 0.7f, 0.7f);

		/* else, we've got a hit! Fetch the closest hit sphere */
		t_obj hitsphere = spheres[hitsphere_id]; /* version with local copy of sphere */

		/* compute the hitpoint using the ray equation */
		float3 hitpoint = ray.origin + ray.dir * t;
		
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		float3 normal = normalize(hitpoint - hitsphere.position); 
		float3 normal_facing = dot(normal, ray.dir) < 0.0f ? normal : normal * (-1.0f);

		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
		float rand1 = 2.0f * PI * get_random(seed0, seed1);
		float rand2 = get_random(seed0, seed1);
		float rand2s = sqrt(rand2);

		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float3 w = normal_facing;
		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
		float3 u = normalize(cross(axis, w));
		float3 v = cross(w, u);

		/* use the coordinte frame and random numbers to compute the next ray direction */
		float3 newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));

		/* add a very small offset to the hitpoint to prevent self intersection */
		if (hitsphere.reflection > 0) {
			ray.dir = reflect(ray.dir, normal_facing);
			ray.origin = hitpoint + ray.dir * EPSILON;

			accum_color += mask * hitsphere.emission; 	/* add the colour and light contributions to the accumulated colour */ 
			mask *= hitsphere.color * hitsphere.reflection;	/* the mask colour picks up surface colours at each bounce */
		} else {
			ray.dir = newdir;
			ray.origin = hitpoint + ray.dir * EPSILON;
			accum_color += mask * hitsphere.emission; 
			mask *= hitsphere.color;
		}
		mask *= dot(newdir, normal_facing);
	}

	return accum_color;
}

static int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static float clamp1(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int toInt(float x)
{ 
	return int(clamp1(x) * 255);
}

int rand(int* seed) // 1 <= *seed < m
{
    int const a = 16807; //ie 7**5
    int const m = 2147483647; //ie 2**31-1

    *seed = ((long)(*seed * a)) % m;
    return(*seed);
}

__kernel void render_kernel(__global int* output, int width, int height, int n_spheres, __constant t_obj* spheres)
{
	
	unsigned int work_item_id = get_global_id(0);	/* the unique global id of the work item for the current pixel */
	unsigned int x_coord = work_item_id % width;			/* x-coordinate of the pixel */
	unsigned int y_coord = work_item_id / width;			/* y-coordinate of the pixel */
	float fx = (float)x_coord / (float)width; 
 	float fy = (float)y_coord / (float)height;
	output[x_coord + y_coord * width] = ft_rgb_to_hex(toInt(fx), toInt(fy), toInt(0)); /* simple interpolated colour gradient based on pixel coordinates */
}
