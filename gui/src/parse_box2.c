/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_box2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:30:38 by lminta            #+#    #+#             */
/*   Updated: 2019/11/21 18:42:25 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_radius(t_gui *gui, t_obj *obj, int *i)
{
	obj->radius = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void			parse_direction(t_gui *gui, t_obj *obj, int *i)
{
	obj->v.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->v.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->v.s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void			parse_position(t_gui *gui, t_obj *obj, int *i)
{
	obj->position.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->position.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->position.s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void			parse_prolapse(t_gui *gui, t_obj *obj, int *i)
{
	if (obj->type == PLANE)
		obj->prolapse.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->prolapse.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}
