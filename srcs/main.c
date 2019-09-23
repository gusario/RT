/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/23 17:37:33 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	ft_init_window(&game.sdl, WIN_W, WIN_H);
	set_const(&game, &gui);
	if (argc != 2)
		game.av = start_gui(&gui);
	else
		game.av = argv[1];
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	init_kiwi(&gui);
	main_screen(&gui);
	while (game.av)
	{
		opencl(&game, game.av);
		ft_strdel(&game.av);
		gui.av = 0;
		game.quit = 0;
		gui.quit = 0;
		game.flag = 1;
		poopa(&game, &gui);
	}
	quit_kiwi_main(&gui);
	//release_gpu(game.gpu);
	ft_exit(NULL);
}
