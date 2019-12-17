/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smsht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:27:34 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:22:29 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		obj_if(t_gui *gui, t_obj *obj)
{
	if (obj->type == PLANE)
		change_plane(gui, obj);
	else if (obj->type == CONE)
		change_cone(gui, obj);
	else if (obj->type == CYLINDER)
		change_cylin(gui, obj);
	else if (obj->type == SPHERE)
		change_sphere(gui, obj);
	else if (obj->type == TRIANGLE)
		change_trian(gui, obj);
	else if (obj->type == TORUS)
		change_tor(gui, obj);
	else if (obj->type == PARABOLOID)
		change_hyper(gui, obj);
}

void		visibility_name(KW_Widget *widget, t_obj *obj)
{
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (obj->is_visible)
		KW_SetLabelText(wid, "Object is visible");
	else
		KW_SetLabelText(wid, "Object is invisible");
}

KW_Widget	*f_e(t_gui *gui, double db, KW_Rect *rect)
{
	KW_Widget	*result;
	char		str[100];

	gcvt(db, 5, str);
	result = KW_CreateEditbox(gui->gui, gui->c_o.frame, str, rect);
	return (result);
}

static void	move_eb(t_gui *gui)
{
	gui->c_o.labelrect = (KW_Rect){5, 5, 1, 30};
	gui->c_o.editboxrect[0] = (KW_Rect){5, 5, 1, 30};
	gui->c_o.editboxrect[1] = (KW_Rect){5, 5, 1, 30};
	gui->c_o.editboxrect[2] = (KW_Rect){5, 5, 1, 30};
	gui->c_o.weights[0] = 1;
	gui->c_o.weights[1] = 1;
	gui->c_o.weights[2] = 1;
	gui->c_o.weights[3] = 1;
	KW_RectFillParentHorizontally(&gui->c_o.frect, gui->c_o.rects,
	gui->c_o.weights, 4, 10, KW_RECT_ALIGN_MIDDLE);
	gui->c_o.labelrect.y -= 215;
	gui->c_o.editboxrect[0].y -= 215;
	gui->c_o.editboxrect[1].y -= 215;
	gui->c_o.editboxrect[2].y -= 215;
}

void		obj_same(t_gui *gui, t_obj *obj)
{
	char	*buff;

	gui->c_o.frect = (KW_Rect){WIN_W - FR_FZ * 5 / 2, WIN_H - FR_ZF * 5 + 60,
	FR_FZ * 5 / 2, FR_ZF * 5 - 60};
	gui->c_o.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->c_o.frect);
	gui->c_o.labelrect = (KW_Rect){5, 5, 100, 30};
	KW_RectHorizontallyCenterInParent(&gui->c_o.frect, &gui->c_o.labelrect);
	buff = fill_name_mass(obj);
	KW_CreateLabel(gui->gui, gui->c_o.frame, buff, &gui->c_o.labelrect);
	free(buff);
	gui->c_o.buttonrect[0] = (KW_Rect){5, gui->c_o.frect.h - 45, FR_FZ, 40};
	gui->c_o.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_o.frame, "tmp", &gui->c_o.buttonrect[0]);
	visibility_name(gui->c_o.buttons[0], obj);
	KW_AddWidgetMouseDownHandler(gui->c_o.buttons[0], visibility);
	KW_SetWidgetUserData(gui->c_o.buttons[0], obj);
	savebutton(gui, obj);
	delbutton(gui, obj);
	gui->c_o.rects[0] = &gui->c_o.labelrect;
	gui->c_o.rects[1] = &gui->c_o.editboxrect[0];
	gui->c_o.rects[2] = &gui->c_o.editboxrect[1];
	gui->c_o.rects[3] = &gui->c_o.editboxrect[2];
	move_eb(gui);
}
