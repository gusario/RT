/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:11 by lminta            #+#    #+#             */
/*   Updated: 2019/10/28 20:12:42 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	main_screen(t_gui *gui, t_game *game)
{
	gui->inf_b.names = 0;
	obj_select(gui, game->gpu.objects, game->obj_quantity);
	info_button(game, gui);
}


void	main_screen_free(t_gui *gui)
{
	int i;

	i = -1;
	while (gui->o_s.names[++i] && i < MAX_OBJ)
		free(gui->o_s.names[i]);
	i = -1;
	while (gui->o_s.buttons[++i] && i < MAX_OBJ)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->o_s.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->o_s.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->o_s.buttons[i], 0);
	}
	if (gui->o_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->o_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->o_s.frame, 0);
		KW_DestroyWidget(gui->o_s.frame, 1);
	}
	KW_RemoveWidgetGeometryChangeHandler(gui->inf_b.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->inf_b.frame, 0);
	KW_DestroyWidget(gui->inf_b.frame, 1);
}

void	quit_kiwi_main(t_gui *gui)
{
	if (gui->s_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->s_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->s_s.frame, 0);
		KW_DestroyWidget(gui->s_s.frame, 1);
	}
	free(gui->inf_b.names);
	KW_ReleaseSurface(gui->driver, gui->set);
	KW_Quit(gui->gui);
}
