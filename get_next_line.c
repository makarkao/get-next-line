/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:38:36 by makarkao          #+#    #+#             */
/*   Updated: 2024/12/30 09:30:33 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static t_gnlsv	v;
	t_gnlnsv		x;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	(1) && (x.j = 0, x.l = NULL);
	if (v.s == NULL || v.s[v.k] == 0)
	{
		if (!v.s)
		{
			v.s = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
			if (!v.s)
				return (NULL);
		}
		x.i = read(fd, v.s, BUFFER_SIZE);
		if (x.i == -1)
			return (free(v.s), v.s = NULL, NULL);
		(1) && (v.s[x.i] = '\0', v.k = 0);
	}
	return (ft_get_nxt_line_prc(&v, &x, fd));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	//char	buffer[1024];
// 	//int		i;
// 	fd = open("ggggg.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		exit(EXIT_FAILURE);
// 	}
// 	//i = 0;
// 	line = get_next_line(fd);
// 	char *line2 = get_next_line(fd);
// 	printf("%s", line2);
// 	free(line2);
// 	close(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
