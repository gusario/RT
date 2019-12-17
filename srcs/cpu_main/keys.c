/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:10:38 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:07:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	key_switch(t_game *game)
{
	if (game->keys.ed_box)
		return ;
	if (game->ev.key.keysym.sym == SDLK_COMMA)
	{
		game->gpu.samples = 0;
		game->cam_num--;
		if (game->cam_num < 0)
			game->cam_num = game->cam_quantity - 1;
		game->flag = 1;
	}
	else if (game->ev.key.keysym.sym == SDLK_PERIOD)
	{
		game->gpu.samples = 0;
		game->cam_num++;
		if (game->cam_num >= game->cam_quantity)
			game->cam_num = 0;
		game->flag = 1;
	}
	else if (game->ev.key.keysym.sym == SDLK_i)
		show_hide(game, g_gui(0, 0));
	else if (game->ev.key.keysym.sym == SDLK_r)
		game->keys.r = !game->keys.r;
}

static void	key_down(t_game *game)
{
	if (game->ev.key.keysym.sym == SDLK_q)
		game->keys.q = 1;
	else if (game->ev.key.keysym.sym == SDLK_w)
		game->keys.w = 1;
	else if (game->ev.key.keysym.sym == SDLK_e)
		game->keys.e = 1;
	else if (game->ev.key.keysym.sym == SDLK_a)
		game->keys.a = 1;
	else if (game->ev.key.keysym.sym == SDLK_s)
		game->keys.s = 1;
	else if (game->ev.key.keysym.sym == SDLK_d)
		game->keys.d = 1;
	else if (game->ev.key.keysym.sym == SDLK_z)
		game->keys.z = 1;
	else if (game->ev.key.keysym.sym == SDLK_x)
		game->keys.x = 1;
	else if (game->ev.key.keysym.sym == SDLK_SPACE)
		game->keys.space = 1;
	else
		key_switch(game);
}

static void	key_up(t_game *game)
{
	if (game->ev.key.keysym.sym == SDLK_q)
		game->keys.q = 0;
	else if (game->ev.key.keysym.sym == SDLK_w)
		game->keys.w = 0;
	else if (game->ev.key.keysym.sym == SDLK_e)
		game->keys.e = 0;
	else if (game->ev.key.keysym.sym == SDLK_a)
		game->keys.a = 0;
	else if (game->ev.key.keysym.sym == SDLK_s)
		game->keys.s = 0;
	else if (game->ev.key.keysym.sym == SDLK_d)
		game->keys.d = 0;
	else if (game->ev.key.keysym.sym == SDLK_z)
		game->keys.z = 0;
	else if (game->ev.key.keysym.sym == SDLK_x)
		game->keys.x = 0;
	else if (game->ev.key.keysym.sym == SDLK_SPACE)
		game->keys.space = 0;
}

void		key_check(t_game *game)
{
	game->mouse.mm = 0;
	while (SDL_PollEvent(&(game->ev)))
	{
		if (game->ev.type == SDL_QUIT ||
		(game->ev.type == SDL_KEYDOWN &&
		game->ev.key.keysym.sym == SDLK_ESCAPE))
			game->quit = 1;
		else if (game->ev.type == SDL_KEYDOWN && !game->samples_to_do)
			key_down(game);
		else if (game->ev.type == SDL_KEYUP && !game->samples_to_do)
			key_up(game);
		else if (game->ev.type == SDL_MOUSEBUTTONUP && !game->samples_to_do)
			mouse_up(game);
		else if (game->ev.type == SDL_MOUSEBUTTONDOWN && !game->samples_to_do)
			mouse_down(game, g_gui(0, 0));
		else if (game->ev.type == SDL_MOUSEMOTION && !game->samples_to_do)
			mouse_motion(game, g_gui(0, 0));
	}
}
