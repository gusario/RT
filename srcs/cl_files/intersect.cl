#include "options.cl"


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

				/* (__global Sphere* sphere, const t_ray *  ray) */
static float intersect_cone(const t_obj* cone, const t_ray *  ray) /* version using local copy of sphere */
{
	float3	x = ray->origin - cone->position;
	float angle = cos(cone->radius);
	float	a = dot(ray->dir, cone->v) * dot(ray->dir, cone->v) - angle * angle;
	float	b = 2.0 * (dot(ray->dir, cone->v) * dot(x, cone->v) - dot(ray->dir, x) * angle * angle);
	float	c = dot(x, cone->v) * dot(x, cone->v) - dot(x,x) * angle * angle;

	float d = b*b - 4.f * a * c;
	if(d < EPSILON) 
		return 0.f;
	d = sqrt(d);
	float t1 = (-b - d) / (2. * a);
	float t2 = (-b + d) / (2. * a);
	float t = t1;
	if(t < EPSILON || t2 > EPSILON && t2 < t)
		t = t2;

	return (t);
}

static float intersect_sphere(const t_obj* sphere,  t_ray *  ray) /* version using local copy of sphere */
{
	float3 rayToCenter = ray->origin - sphere->position;
    float a = 1;
    float b = 2*dot(rayToCenter, ray->dir);
    float c = dot(rayToCenter, rayToCenter) - sphere->radius*sphere->radius;	
	return (ft_solve(a, b, c));
}

float		intersect_plane(const t_obj* plane, const t_ray *ray)
{
	float	a;
	float	b;
	a = dot(plane->v, ray->dir);//ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, plane->point), plane->normal);
	//b = ft_vec3_dot_multiply(ray->dir, plane->normal);
	if (fabs(a) < EPSILON)
		return (0);
	b = -(dot(ray->origin - plane->position, plane->v)) / a;
	return (b < EPSILON) ? 0 : b;
}


static float		intersect_cylinder(const t_obj* cylinder, const t_ray *  ray)
{
	float3	x = ray->origin - cylinder->position;
	double	a = dot(ray->dir, cylinder->v);
	double	c = dot(x, cylinder->v);
	double	b = 2 * (dot(ray->dir, x) - a * dot(x, cylinder->v));

	a = dot(ray->dir, ray->dir) - a * a;
	c = dot(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (ft_solve(a, b, c));
}

static int inside_triangle(const t_obj* triangle, float3 collision)
{
	float3 edge_0;
	float3 edge_1;
	float3 edge_2;
	float3 c_0;
	float3 c_1;
	float3 c_2;

	c_0 = collision - triangle->vertices[0];
	c_1 = collision - triangle->vertices[1];
	c_2 = collision - triangle->vertices[2];
	edge_0 = triangle->vertices[1] - triangle->vertices[0];
	edge_1 = triangle->vertices[2] - triangle->vertices[1];
	edge_2 = triangle->vertices[0] - triangle->vertices[2];
	if (dot(triangle->v, cross(edge_0, c_0)) > 0 &&
		dot(triangle->v, cross(edge_1, c_1)) > 0 &&
		dot(triangle->v, cross(edge_2, c_2)) > 0)
		return(1);
	return(0);
}

static float		intersect_triangle(const t_obj* triangle,  t_ray *  ray)
{
	float	a;
	float	b;

	
	a = dot(triangle->v, ray->dir);
	if (fabs(a) < EPSILON)
		return (0);
	b = -(dot(ray->origin - triangle->vertices[1], triangle->v)) / a;
	if (!inside_triangle(triangle, ray->origin + ray->dir * b))
		return (0);
	return (b < EPSILON) ? 0 : b;
}