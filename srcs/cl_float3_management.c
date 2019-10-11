/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float3_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:16:46 by lminta            #+#    #+#             */
/*   Updated: 2019/10/11 15:23:53 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

cl_float3	create_cfloat3(float x, float y, float z)
{
	cl_float3	re;

	re.v4[0] = x;
	re.v4[1] = y;
	re.v4[2] = z;
	return (re);
}

cl_float3	sum_cfloat3(cl_float3 one, cl_float3 two)
{
	cl_float3	res;

	res.s[0] = one.s[0] + two.s[0];
	res.s[1] = one.s[1] + two.s[1];
	res.s[2] = one.s[2] + two.s[2];
	return (res);
}

cl_float3	mult_cfloat3(cl_float3 one, float f)
{
	cl_float3	res;

	res.s[0] = one.s[0] * f;
	res.s[1] = one.s[1] * f;
	res.s[2] = one.s[2] * f;
	return (res);
}

cl_float3	rotate(cl_float3 axis, cl_float3 vector, float angle)
{
	cl_float3	res;
	float		sin_a;
	float		cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	res.s[0] = (cos_a + (1 - cos_a) * axis.s[0] * axis.s[0]) * vector.s[0] +
	((1 - cos_a) * axis.s[0] * axis.s[1] - sin_a * axis.s[2]) * vector.s[1] +
	((1 - cos_a) * axis.s[0] * axis.s[2] + sin_a * axis.s[1]) * vector.s[2];
	res.s[1] = ((1 - cos_a) * axis.s[1] * axis.s[0] + sin_a * axis.s[2]) *
	vector.s[0] + (cos_a + (1 - cos_a) * axis.s[1] * axis.s[1]) * vector.s[1] +
	((1 - cos_a) * axis.s[2] * axis.s[1] - sin_a * axis.s[0]) * vector.s[2];
	res.s[2] = ((1 - cos_a) * axis.s[2] * axis.s[0] - sin_a * axis.s[1]) *
	vector.s[0] +
	((1 - cos_a) * axis.s[2] * axis.s[1] + sin_a * axis.s[0]) * vector.s[1] +
	(cos_a + (1 - cos_a) * axis.s[2] * axis.s[2]) * vector.s[2];
	return (res);
}
