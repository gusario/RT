/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:06:11 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:25 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "malloc.h"

t_vect		*vect_new(void *data, size_t size)
{
	t_vect	*ret;

	MALLOC1(ret);
	vect_init(ret);
	vect_add(ret, data, size);
	return (ret);
}
