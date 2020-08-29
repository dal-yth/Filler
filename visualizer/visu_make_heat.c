/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_make_heat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:08 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:09 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
** From the current position,
** checks all positions around it.
** If any fills the condition, it
** returns 1 and surround enemy
** gives the node a value.
*/

static int	v_check_positions(t_visu *v, int num, int i, int j)
{
	if ((j + 1 < VX) && v->map[i][j + 1] == num)
		return (1);
	if ((j - 1 >= 0) && v->map[i][j - 1] == num)
		return (1);
	if ((i + 1 < VY) && v->map[i + 1][j] == num)
		return (1);
	if ((i - 1 >= 0) && v->map[i - 1][j] == num)
		return (1);
	if ((j + 1 < VX) && (i + 1 < VY) && v->map[i + 1][j + 1] == num)
		return (1);
	if ((j - 1 >= 0) && (i - 1 >= 0) && v->map[i - 1][j - 1] == num)
		return (1);
	if ((j + 1 < VX) && (i - 1 >= 0) && v->map[i - 1][j + 1] == num)
		return (1);
	if ((j - 1 >= 0) && (i + 1 < VY) && v->map[i + 1][j - 1] == num)
		return (1);
	return (0);
}

/*
** While loop that goes through the int
** array and upon finding 0, calls
** check_positions to determine if value
** should be assigned to the node.
*/

static int	v_surround_enemy(t_visu *v, int num, int heat, int change)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < VY)
	{
		while (j < VX)
		{
			if (v->map[i][j] == VX * VY)
			{
				if (v_check_positions(v, num, i, j))
				{
					v->map[i][j] = heat;
					change = 1;
				}
			}
			j = j + 1;
		}
		j = 0;
		i = i + 1;
	}
	return (change);
}

/*
** Generates heat map out of the int array.
** Calls surround enemy function to give value
** to the nodes. Then keeps calling surround
** enemy, until there are no more free nodes left.
*/

void		make_heat(t_visu *v)
{
	int heat;
	int num;
	int change;

	heat = 4;
	change = 1;
	num = ENEM;
	v_surround_enemy(v, num, heat, change);
	num = 4;
	heat = 1;
	v_surround_enemy(v, num, heat, change);
	num = 1;
	heat = 2;
	while (change)
	{
		change = 0;
		change = v_surround_enemy(v, num, heat, change);
		heat = heat + 1;
		num = num + 1;
	}
}
