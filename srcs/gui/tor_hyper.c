/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tor_hyper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:43:23 by lminta            #+#    #+#             */
/*   Updated: 2019/12/14 18:46:07 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_hyper(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc_exit(sizeof(t_obj));
	obj->v = create_cfloat3(0, 1, 0);
	obj->radius = 0.1;
	same_new(game, obj, PARABOLOID);
}

void	create_tor(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc_exit(sizeof(t_obj));
	obj->radius = 0.1;
	obj->tor_radius = 0.05;
	same_new(game, obj, TORUS);
}

void	change_hyper(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	direction(gui, obj, &i);
	radius(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
}

void	change_tor(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	direction(gui, obj, &i);
	radius(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
}
