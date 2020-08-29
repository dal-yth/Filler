/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:37:51 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/19 17:33:25 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Frees the map and the struct and exits.
** Calls free piece to free the last piece.
*/

void	free_all(t_filler *f)
{
	int i;

	i = 0;
	free_piece(f);
	while (i < MY)
	{
		free(MAP[i]);
		i = i + 1;
	}
	free(MAP);
	free(f);
}

/*
** Gives error if mallocing fails and exits program.
*/

void	malloc_error(void)
{
	write(2, "Malloc error", 12);
	exit(0);
}

/*
** Inits filler struct values.
** MAX is max int value.
*/

void	init_filler(t_filler *f)
{
	VALUE = 0;
	BEST = MAX;
	PX = 0;
	PY = 0;
	BX = 0;
	BY = 0;
	I = 0;
	J = 0;
}

/*
** Helper function to save friend and
** enemy values.
*/

void	friend_enemy(t_filler *f)
{
	if (PLAYER == 1)
	{
		ENEMY = -2;
		FRIEND = -1;
	}
	else
	{
		ENEMY = -1;
		FRIEND = -2;
	}
}

/*
** Evaluates if we should choose only the
** first best value of last best value, we
** make the choice depending on the height
** if we are at the upper portion of the map
** we want the last value because it is most
** likely to be at the lowest position. Same
** when we are below the middle, first value
** is likely to be the one closest to top.
*/

int		evaluator(t_filler *f, int my)
{
	if (my < (MY / 2))
	{
		if (VALUE <= BEST)
			return (1);
	}
	else
	{
		if (VALUE < BEST)
			return (1);
	}
	return (0);
}
