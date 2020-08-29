/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:36:59 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/19 18:18:16 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Displays error and exits if called.
*/

void		error(void)
{
	write(2, "Input error", 11);
	write(2, "\n", 1);
	exit(0);
}

/*
** Gets the dimensions of the map.
*/

static void	get_dimensions(t_filler *f, char *buf)
{
	int i;

	i = 8;
	while (buf[i] != ' ')
	{
		if (ft_isdigit(buf[i]))
			MY = MY * 10 + (buf[i] - 48);
		else
			error();
		i = i + 1;
	}
	i = i + 1;
	while (buf[i] != ':')
	{
		if (ft_isdigit(buf[i]))
			MX = MX * 10 + (buf[i] - 48);
		else
			error();
		i = i + 1;
	}
}

/*
** Does some simple tests to the buf string.
*/

void		test_line(char *buf, int test)
{
	if (ft_strlen(buf) == 0)
		error();
	else if (test == 1)
	{
		if (buf[0] != '$' && !ft_isdigit(buf[10]))
			error();
	}
	else if (test == 2)
	{
		if (buf[0] != 'P')
			error();
	}
}

/*
** Reads player number and Plateau.
** Based on Plateau data, allocates MAP.
*/

void		read_info(t_filler *f)
{
	char	*buf;
	int		i;

	i = 0;
	MX = 0;
	MY = 0;
	get_next_line(0, &buf);
	PLAYER = buf[10] - 48;
	test_line(buf, 1);
	free(buf);
	get_next_line(0, &buf);
	test_line(buf, 2);
	get_dimensions(f, buf);
	free(buf);
	if (!(MAP = (int**)malloc(sizeof(int*) * MY)))
		malloc_error();
	while (i < MY)
	{
		if (!(MAP[i] = (int*)malloc(sizeof(int) * MX)))
			malloc_error();
		i = i + 1;
	}
	friend_enemy(f);
}
