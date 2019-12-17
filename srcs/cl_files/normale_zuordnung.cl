#include "options.cl"

static float3			interpolate_color_as_vector(int color)
{
	float3				new_color;

	// new_color.x = ((float)(color & 255) / 255.f) * 2.f - 1.f;
	// new_color.y = ((float)((color >> 8) & 255) / 255.f) * 2.f - 1.f;
	// new_color.z = ((float)((color >> 16) & 255) / 255.f);
	new_color = cl_int_to_float3(color);
	new_color.xz = new_color.zx;
	new_color.x = new_color.x * 2.f - 1.f;
	new_color.y = new_color.y * 2.f - 1.f;
	new_color.z = new_color.z * 2.f - 1.f;
	return (new_color);
}

static float3			plane_normal_map(t_obj *object, t_intersection *intersection, float3 normal, float2 *coord, float3 inter_vector)
{
	float3				end_vector;

	end_vector = inter_vector.x * normal + object->basis[0] * inter_vector.z + object->basis[1] * inter_vector.y;
	return (end_vector);
}

static float3			cone_normal_map(t_obj *object, t_intersection *intersection, float3 normal, float2 *coord, float3 inter_vector)
{
	float3				end_vector;
	float3				third_basis;

	third_basis = cross(object->v, normal);
	end_vector = inter_vector.x * normal + third_basis * inter_vector.z + object->v * inter_vector.y;
	return (end_vector);
}

static float3			cylinder_normal_map(t_obj *object, t_intersection *intersection, float3 normal, float2 *coord, float3 inter_vector)
{
	float3				end_vector;
	float3				third_basis;

	third_basis = cross(object->v, normal);
	end_vector = inter_vector.x * normal + third_basis * inter_vector.z + object->v * inter_vector.y;
	return (end_vector);
}

static float3			sphere_normal_map(t_obj *object, t_intersection *intersection, float3 normal, float2 *coord, float3 inter_vector)
{
	float3				end_vector;
	float3				third_basis;

	third_basis = cross(object->v, normal);
	end_vector = inter_vector.x * normal + object->basis[0] * inter_vector.z + object->basis[1] * inter_vector.y;
	return (end_vector);
}

float3					int_vect(t_obj *object, float2 *coord, t_scene *scene)
{
	float3				inter_vector;

	if (object->normal > 0)
	{
		__global t_txture *normal_map = &((scene->normals)[object->normal - 1]);
		int i = normal_map->texture[((int)(coord->y * (float)(normal_map->height))) * (normal_map->width) + (int)(coord->x * (float)(normal_map->width))];
		inter_vector = interpolate_color_as_vector(i);
	}
	else
	{
		float len = sin(length((*coord - (float2)(0.5f)) * 2 * PI * 10));
		float2 crd = normalize((float2)(0.5f) - *coord);
		inter_vector = normalize((float3)(1.0f, len * crd.x, len * crd.y));
	}
	return (inter_vector);
}

float3					normal_map(t_obj *object, t_intersection *intersection, float3 normal, float2 *coord, t_scene *scene)
{
	float3				inter_vector;

	inter_vector = int_vect(object, coord, scene);
	if (object->type == PLANE)
	 	normal = plane_normal_map(object, intersection, normal, coord, inter_vector);
	else if (object->type == CYLINDER)
	 	normal = cylinder_normal_map(object, intersection, normal, coord, inter_vector);
	else if (object->type == CONE)
	 	normal = cone_normal_map(object, intersection, normal, coord, inter_vector);
	else
		normal = sphere_normal_map(object, intersection, normal, coord, inter_vector);
	return (normalize(normal));
}