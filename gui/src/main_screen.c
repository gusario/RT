/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:11 by lminta            #+#    #+#             */
/*   Updated: 2019/10/14 21:39:26 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	main_screen(t_gui *gui, t_game *game)
{
	obj_select(gui, game->gpu.objects, game->obj_quantity);
}

void	main_screen_free(t_gui *gui)
{
	int i;

	i = -1;
	while (gui->o_s.names[++i] && i < MAX_OBJ)
		free(gui->o_s.names[i]);
	KW_DestroyWidget(gui->o_s.frame, 1);
	//free(gui->o_s.frame);
}

void	quit_kiwi_main(t_gui *gui)
{
	KW_DestroyWidget(gui->s_s.frame, 1);
	KW_ReleaseSurface(gui->driver, gui->set);
	//KW_ReleaseRenderDriver(gui->driver);
	KW_Quit(gui->gui);
}
