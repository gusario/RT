/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:53:01 by lminta            #+#    #+#             */
/*   Updated: 2019/10/19 19:14:36 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void opencl_init(t_game *game, char *argv)
{
	game->kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game->cl_info = ft_memalloc(sizeof(t_cl_info));
	game->gpu.objects = NULL;
	game->gpu.vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game->gpu.random = get_random(game->gpu.random);
	game->gpu.samples = 0;
	game->cam_num = 0;
	game->gpu.camera = NULL;
	game->cl_info->krl_names = ft_memalloc(sizeof(t_vect));
	vect_init(game->cl_info->krl_names);
	vect_str_add(game->cl_info->krl_names, "render_kernel");
	cl_init(game->cl_info);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	game->cl_info->ret = cl_krl_build(game->cl_info, game->kernels, fd, "-w -I srcs/cl_files/ -I includes/cl_headers/", game->cl_info->krl_names);


	read_scene(argv, game);
	cl_krl_init(&game->kernels[0], 5);
	game->kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game->kernels[0].sizes[1] =  sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].sizes[2] = sizeof(cl_float3) * WIN_H * WIN_W;
	game->kernels[0].sizes[3] = WIN_H * WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * game->textures_num;

	game->cl_info->ret = krl_set_args(game->cl_info->ctxt, &game->kernels[0]);	
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game->sdl.surface->data);
	//game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1], sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu.vec_temp);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3], WIN_H * WIN_W * sizeof(cl_ulong), game->gpu.random);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4], sizeof(t_txture) * game->textures_num, game->textures);

}


void		opencl(t_game *game, char *argv)
{
	 game->obj_quantity = 0; 
	read_scene(argv, game);
	printf("n->objs: %zu\n", game->obj_quantity);
	game->kernels[0].sizes[1] =  sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].args[1] =  clCreateBuffer(game->cl_info->ctxt, CL_MEM_READ_WRITE, game->kernels[0].sizes[1], NULL, &game->cl_info->ret);
	clSetKernelArg(game->kernels[0].krl, 1, sizeof(game->kernels[0].args[1]), (void*)&game->kernels[0].args[1]);
 	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1], sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
}

void	free_opencl(t_game *game)
{
	clReleaseMemObject(game->kernels[0].args[1]);
	// free(game->kernels);
	// free(game->cl_info);
	// free(game->gpu.vec_temp);
	// free(game->gpu.random);
}
