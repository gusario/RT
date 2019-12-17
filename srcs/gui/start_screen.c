/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 22:51:42 by lminta            #+#    #+#             */
/*   Updated: 2019/12/12 18:50:18 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ok_clicked(KW_Widget *widget, int b)
{
	t_gui	*gui;

	b = 0;
	widget = 0;
	gui = g_gui(0, 0);
	if (gui->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	gui->av = ft_strdup((char *)KW_GetEditboxText(gui->ed_w.ed_b));
	gui->quit = KW_TRUE;
}

void		play_stop_music(char *name)
{
	static Mix_Music *music = 0;

	if (Mix_PlayingMusic() && !name)
	{
		Mix_PauseMusic();
		if (music)
		{
			Mix_FreeMusic(music);
			music = 0;
		}
	}
	else if (name)
	{
		if (!(music = Mix_LoadMUS(name)))
			return ;
		Mix_PlayMusic(music, 1);
	}
}

void		start_screen(t_gui *gui)
{
	gui->ed_w.frect = (KW_Rect){10, 10, 300, 220};
	KW_RectCenterInParent(&gui->ed_w.winrect, &gui->ed_w.frect);
	gui->ed_w.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->ed_w.frect);
	gui->ed_w.titlerect = (KW_Rect){0, 10, 300, 30};
	gui->ed_w.labelrect = (KW_Rect){0, 100, 60, 30};
	gui->ed_w.editboxrect = (KW_Rect){0, 100, 100, 40};
	gui->ed_w.rects[0] = &gui->ed_w.labelrect;
	gui->ed_w.rects[1] = &gui->ed_w.editboxrect;
	gui->ed_w.weights[0] = 1;
	gui->ed_w.weights[1] = 4;
	KW_RectFillParentHorizontally(&gui->ed_w.frect,
	gui->ed_w.rects, gui->ed_w.weights, 2, 10, KW_RECT_ALIGN_MIDDLE);
	KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"Enter the path to the scene", &gui->ed_w.titlerect);
	KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"Path", &gui->ed_w.labelrect);
	gui->ed_w.ed_b = KW_CreateEditbox(gui->gui,
	gui->ed_w.frame, "scenes/", &gui->ed_w.editboxrect);
	gui->ed_w.buttonrect = (KW_Rect){250, 170, 40, 40};
	gui->ed_w.okbutton = KW_CreateButtonAndLabel(gui->gui,
	gui->ed_w.frame, "OK", &gui->ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->ed_w.okbutton, ok_clicked);
}

/*
**	KW_RemoveWidgetGeometryChangeHandler(gui->ed_w.frame, 0);
**	KW_RemoveWidgetTilesetChangeHandler(gui->ed_w.frame, 0);
**	KW_DestroyWidget(gui->ed_w.frame, 1);
*/

char		*start_gui(t_game *game, t_gui *gui)
{
	opencl(game, "scenes/start.json");
	start_screen(gui);
	scene_select(gui, -1, 0);
	play_stop_music(game->music);
	loopa(game, gui);
	play_stop_music(0);
	destr(gui, gui->ed_w.frame);
	KW_RemoveWidgetGeometryChangeHandler(gui->ed_w.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->ed_w.frame, 0);
	KW_HideWidget(gui->ed_w.frame);
	gui->ed_w.show = 0;
	free_list(game);
	game->texture_list = NULL;
	game->textures_num = 0;
	game->normal_list = NULL;
	game->normals_num = 0;
	return (gui->av);
}
