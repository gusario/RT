/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/10/14 19:26:28 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void text_load(t_game *game, t_gui *gui)
{
	struct dirent	*name_buff;
	DIR				*res;
	int				i;

	game->textures_num = 0;
	if (!(res = opendir("textures")))
		ft_exit(0);
	while ((name_buff = readdir(res)))
		if (name_buff->d_type == 8 && ft_isdigit(*(name_buff->d_name)))
			game->textures_num++;
	closedir(res);
		game->textures_num = 10;
	if (!(game->textures = (t_txture *)malloc(sizeof(t_txture) * game->textures_num + 1)))
	{
		ft_putstr("Memory error \n");
	}
	if (!(res = opendir("textures")))
		ft_exit(0);
	i = 0;
	while ((name_buff = readdir(res))){printf("ok\n");
		if (name_buff->d_type == 8 && ft_isdigit(*(name_buff->d_name)) && i < 10)
		{
			get_texture(name_buff->d_name, &(game->textures[i]));
			i++;
		}}
	closedir(res);
}

static void	main_loop(t_game *game, t_gui *gui, int argc)
{
	while (game->av)
	{
		opencl(game, game->av);
		main_screen(gui, game);
		if (argc != 2)
			ft_strdel(&game->av);
		argc = 0;
		gui->av = 0;
		game->quit = 0;
		gui->quit = 0;
		game->flag = 1;
		render_loop(game, gui);
		main_screen_free(gui);
	}
}

int			main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	gui.main_screen = 0;
	ft_init_window(&game.sdl, WIN_W, WIN_H);
	set_const(&game, &gui);
	if (argc != 2)
		game.av = start_gui(&gui);
	else
		game.av = argv[1];
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	init_kiwi(&gui);
	gui.main_screen = 1;
	scene_select(&gui);
	text_load(&game, &gui);
	main_loop(&game, &gui, argc);
	quit_kiwi_main(&gui);
	//release_gpu(game.gpu);
	ft_exit(NULL);
}
