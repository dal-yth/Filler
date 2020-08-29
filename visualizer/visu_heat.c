/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_heat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:02 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:03 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
** Allocates correct amount of memory to the int array.
** Read the buf string and saves dimensions for allocation.
*/

void		allocate_map(t_visu *v, char *buf)
{
	int i;

	i = 8;
	VY = 0;
	VX = 0;
	H = H + 1;
	while (buf[i] != ' ')
	{
		VY = VY * 10 + (buf[i] - 48);
		i = i + 1;
	}
	(!(v->map = (int**)malloc(sizeof(int*) * VY))) ? malloc_error() : 0;
	i = i + 1;
	while (buf[i] != ':')
	{
		VX = VX * 10 + (buf[i] - 48);
		i = i + 1;
	}
	i = 0;
	while (i < VY)
	{
		(!(v->map[i] = (int*)malloc(sizeof(int) * VX))) ? malloc_error() : 0;
		i = i + 1;
	}
}

/*
** Assigns values to the int array based on buf.
** We give really high value to empty spots and
** negative values to player positions.
*/

static void	v_make_map(t_visu *v, char *buf, int r)
{
	int i;
	int j;

	i = 4;
	j = 0;
	while (buf[i])
	{
		if (buf[i] == '.')
			v->map[r][j] = VX * VY;
		else if (buf[i] == 'o' || buf[i] == 'O')
			v->map[r][j] = -1;
		else if (buf[i] == 'x' || buf[i] == 'X')
			v->map[r][j] = -2;
		i = i + 1;
		j = j + 1;
	}
}

/*
** Make_str evaluates the int value in array
** and adds correct colored 'block' to the
** final printed string.
*/

static void	make_str(t_visu *v, int i, int j)
{
	int count;

	count = 0;
	if (v->map[i][j] == -1)
		count = ft_sprintf(v->final + v->total, "%{B_BLACK}  %{EOC}");
	else if (v->map[i][j] == -2)
		count = ft_sprintf(v->final + v->total, "%{B_WHITE}  %{EOC}");
	else if (v->map[i][j] > 15)
		count = ft_sprintf(v->final + v->total, "%{B_PURPLE}  %{EOC}");
	else if (v->map[i][j] > 8)
		count = ft_sprintf(v->final + v->total, "%{B_RED}  %{EOC}");
	else if (v->map[i][j] > 3)
		count = ft_sprintf(v->final + v->total, "%{B_YELLOW}  %{EOC}");
	else if (v->map[i][j] > 0)
		count = ft_sprintf(v->final + v->total, "%{B_GREEN}  %{EOC}");
	v->total = v->total + count;
}

/*
** Print map cycles through the int array map
** and calls make_str to create correct colors.
*/

static void	print_map(t_visu *v)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	v->total = 0;
	count = 0;
	while (i < VY)
	{
		while (j < VX)
		{
			make_str(v, i, j);
			j = j + 1;
		}
		count = ft_sprintf(v->final + v->total, "\n");
		v->total = v->total + count;
		j = 0;
		i = i + 1;
	}
	write(1, v->final, v->total);
}

/*
** Gets the lines from fd which points to visu.txt.
** Calls make map function when there is a line
** starting with digit and when there is a line
** with second character being 'i', creates the
** heatmap and prints it out.
*/

void		print_heat(t_visu *v, int fd)
{
	int		i;
	char	*buf;

	i = 0;
	while (get_next_line(fd, &buf) > 0)
	{
		if (ft_isdigit(buf[0]))
		{
			v_make_map(v, buf, i);
			i = i + 1;
		}
		else if (buf[0] == 'P' && buf[1] == 'l')
		{
			make_heat(v);
			usleep(80000);
			system("clear");
			print_map(v);
			free(buf);
			break ;
		}
		free(buf);
	}
}
