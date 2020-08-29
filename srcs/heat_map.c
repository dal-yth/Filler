/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:36:19 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/19 13:51:43 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** From the current position,
** checks all positions around it.
** If any fills the condition, it
** returns 1 and surround enemy
** gives the node a value.
*/

static int	check_positions(t_filler *f, int num)
{
	if ((J + 1 < MX) && MAP[I][J + 1] == num)
		return (1);
	if ((J - 1 >= 0) && MAP[I][J - 1] == num)
		return (1);
	if ((I + 1 < MY) && MAP[I + 1][J] == num)
		return (1);
	if ((I - 1 >= 0) && MAP[I - 1][J] == num)
		return (1);
	if ((J + 1 < MX) && (I + 1 < MY) && MAP[I + 1][J + 1] == num)
		return (1);
	if ((J - 1 >= 0) && (I - 1 >= 0) && MAP[I - 1][J - 1] == num)
		return (1);
	if ((J + 1 < MX) && (I - 1 >= 0) && MAP[I - 1][J + 1] == num)
		return (1);
	if ((J - 1 >= 0) && (I + 1 < MY) && MAP[I + 1][J - 1] == num)
		return (1);
	return (0);
}

/*
** While loop that goes through the int
** array and upon finding 0, calls
** check_positions to determine if value
** should be assigned to the node.
*/

static int	surround_enemy(t_filler *f, int num, int heat, int change)
{
	I = 0;
	J = 0;
	while (I < MY)
	{
		while (J < MX)
		{
			if (MAP[I][J] == MX * MY)
			{
				if (check_positions(f, num))
				{
					MAP[I][J] = heat;
					change = 1;
				}
			}
			J = J + 1;
		}
		J = 0;
		I = I + 1;
	}
	return (change);
}

/*
** Generates heat map out of the int array.
** Calls surround enemy function to give value
** to the nodes. Then keeps calling surround
** enemy, until there are no more free nodes left.
*/

void		heat_map(t_filler *f)
{
	int heat;
	int num;
	int change;

	change = 1;
	heat = 4;
	num = ENEMY;
	surround_enemy(f, num, heat, change);
	num = 4;
	heat = 1;
	surround_enemy(f, num, heat, change);
	num = 1;
	heat = 2;
	while (change)
	{
		change = 0;
		change = surround_enemy(f, num, heat, change);
		heat = heat + 1;
		num = num + 1;
	}
}

/*
** Based on the buf string, puts correct
** values on the corresponding int arr MAP.
*/

void		make_map(t_filler *f, char *buf)
{
	int i;
	int j;

	i = 4;
	j = 0;
	while (buf[i])
	{
		if (buf[i] == '.')
			MAP[I][j] = MX * MY;
		else if (buf[i] == 'o' || buf[i] == 'O')
			MAP[I][j] = -1;
		else if (buf[i] == 'x' || buf[i] == 'X')
			MAP[I][j] = -2;
		i = i + 1;
		j = j + 1;
	}
	I = I + 1;
}
