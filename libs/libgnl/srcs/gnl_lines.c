/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:15:59 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:01:11 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"
#include "libgnl.h"

int		gnl_lines(int fd, t_vect *lines, int opts)
{
	char	*dup;
	int		ret;
	t_vect	buf;
	t_vect	line;

	vect_init(&buf);
	vect_init(&line);
	while ((ret = gnl_vect(fd, &buf, &line, opts | GNL_STR)) == 1)
	{
		if (!line.used)
			continue ;
		MALLOC_N(dup, line.used);
		ft_memcpy(dup, line.data, line.used);
		VECT_ADD(lines, dup);
		line.used = 0;
	}
	free(line.data);
	free(buf.data);
	return (ret);
}
