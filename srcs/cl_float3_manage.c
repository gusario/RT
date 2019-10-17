/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float3_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:03:05 by sbrella           #+#    #+#             */
/*   Updated: 2019/10/17 22:11:02 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_float3	cross(cl_float3 one, cl_float3 two)
{
	cl_float3	ret;

	ret.s[0] = one.s[1] * two.s[2] - one.s[2] * two.s[1];
	ret.s[1] = one.s[2] * two.s[0] - one.s[0] * two.s[2];
	ret.s[2] = one.s[0] * two.s[1] - one.s[1] * two.s[0];
	return (ret);
}

cl_float3	vector_diff(cl_float3 one, cl_float3 two)
{
	cl_float3	res;

	res.s[0] = one.s[0] - two.s[0];
	res.s[1] = one.s[1] - two.s[1];
	res.s[2] = one.s[2] - two.s[2];
	return (res);
}

cl_float3	normalize(cl_float3 vector)
{
	cl_float3	res;
	float		norm;

	norm = sqrt(vector.s[0] * vector.s[0] + vector.s[1] *
	vector.s[1] + vector.s[2] * vector.s[2]);
	res.s[0] = vector.s[0] / norm;
	res.s[1] = vector.s[1] / norm;
	res.s[2] = vector.s[2] / norm;
	return (res);
}

void		rotate_horizontal(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = camera->normal;
	camera->direction = rotate(axis, camera->direction, -angle);
}

void		rotate_vertical(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = cross(camera->direction, camera->normal);
	camera->direction = rotate(axis, camera->direction, angle);
	camera->normal = rotate(axis, camera->normal, angle);
}
