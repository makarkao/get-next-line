/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:38:36 by makarkao          #+#    #+#             */
/*   Updated: 2024/12/30 12:24:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_nxt_line_prc(t_gnlsv *v, t_gnlnsv *x, int fd)
{
	while (v->s[0] != 0)
	{
		x->j += ft_strchr(v->s, &(v->k), '\n');
		x->l = ft_sub(x->l, v->s, &(v->k), (x->j - v->k));
		if (!x->l)
			return (free(v->s), v->s = NULL, NULL);
		if (v->s[v->k] == '\n')
		{
			(v->k)++;
			break ;
		}
		if (v->s[v->k] == '\0')
		{
			x->i = read(fd, v->s, BUFFER_SIZE);
			if (x->i == -1)
				return (free(x->l), NULL);
			(1) && (v->s[x->i] = '\0', v->k = 0);
		}
	}
	if (v->s[0] == 0)
	{
		free(v->s);
		v->s = NULL;
	}
	return (x->l);
}

char	*get_next_line(int fd)
{
	static t_gnlsv	v[1024];
	t_gnlnsv		x;

	if (fd < 0 || BUFFER_SIZE == 0 || fd >= 1024)
		return (NULL);
	(1) && (x.j = 0, x.l = NULL);
	if (v[fd].s == NULL || v[fd].s[v[fd].k] == '\0')
	{
		if (!v[fd].s)
		{
			v[fd].s = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
			if (!v[fd].s)
				return (NULL);
		}
		x.i = read(fd, v[fd].s, BUFFER_SIZE);
		if (x.i == -1)
			return (free(v[fd].s), v[fd].s = NULL, NULL);
		(1) && (v[fd].s[x.i] = '\0', v[fd].k = 0);
	}
	return (ft_get_nxt_line_prc(&(v[fd]), &x, fd));
}
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	int		fd2;
	int		fd3;

	fd = open("t.txt", O_RDONLY);
	fd2 = open("u.txt", O_RDONLY);
	fd3= open("v.txt", O_RDONLY);
	char	*line1 = get_next_line(fd);
	char	*line2 = get_next_line(fd2);
	char	*line3 = get_next_line(fd3);
	printf("%s", line1);
	printf("%s", line2);
	printf("%s", line3);
	free(line1);
	free(line2);
	free(line3);
	line1 = get_next_line(fd);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	printf("%s", line1);
	printf("%s", line2);
	printf("%s", line3);
	free(line1);
	free(line2);
	free(line3);

	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
