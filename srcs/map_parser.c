/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <sdurgan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:12:04 by sdurgan           #+#    #+#             */
/*   Updated: 2019/05/27 17:04:25 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	configure_sphere(char *map_name, t_sphere *sphere)
{
	int			fd;
	char		*line;
	int			ret;
	char		**split;

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
		ft_strchr(line, 'x') ? sphere->center.x = ret : 0;
		ft_strchr(line, 'y') ? sphere->center.y = ret : 0;
		ft_strchr(line, 'z') ? sphere->center.z = ret : 0;
		ft_strchr(line, 'r') ? sphere->radius = ret : 0;
		ret = ft_2darrayclean(&split);
	}
}

t_json	*init_line(char *line)
{
	t_json	*node;

	node = (t_json *)malloc(sizeof(t_json));
	node->param = NULL;
	node->next = NULL;
	node->value = line;
	return (node);
}

t_json		*ft_lstadd_to_end(t_json **data, char *line)
{
	t_json	*new_node;
	t_json	*head;

	if (!(new_node = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	head = *data;
	while (*data && (*data)->next)
		*data = (*data)->next;
	if (*data)
	{
		(*data)->next = new_node;
		*data = head;
	}
	else
		*data = new_node;
	new_node->next = NULL;
	new_node->value = line;
	return (new_node);
}

void	process_line(t_json *data)
{
	while (data->next)
	{
		//printf("hey");
		//printf("%s\n", data->value);
		data = data->next;
	}
}

void	parce_json(char *filename)
{
	int		fd;
	char	*line;
	int		ret;
	t_json	*file;
	t_json	*start;

	fd = open(filename, O_RDONLY);
	line = ft_strnew(0);
	start = file;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
		{
			{
				ft_strdel(&line);
				exit(0);
			}
		}
		else
		{
			file = ft_lstadd_to_end(&file, line);
		}
	}
	file = start;
	process_line(file);
}
