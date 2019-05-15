/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <sdurgan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:12:04 by sdurgan           #+#    #+#             */
/*   Updated: 2019/05/15 16:07:25 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere	configure_sphere(char **map_name)
{
	int			fd;
	char		*line;
	float			ret;
	char		**split;
	t_sphere	sphere;

	fd = open(map_name, O_RDONLY);
	line = ft_strnew(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
		{
			ft_strdel(&line);
			exit(0);
		}
		split = ft_strsplit(line, ':');
		ret = ft_atoi(split[1]);
		ft_strchr(line, 'x') ? sphere.center.x = ret : 0;
		ft_strchr(line, 'y') ? sphere.center.y = ret : 0;
		ft_strchr(line, 'z') ? sphere.center.z = ret : 0;
		ft_strchr(line, 'r') ? sphere.radius = ret : 0;
		ret = ft_2darrayclean(&split);
	}
	return (sphere);
}
