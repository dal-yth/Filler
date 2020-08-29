/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:32:31 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 16:10:56 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Incrementer function.
** Choice dictates which values should be increased.
*/

static int	incrementer(t_filler *f, int my, int mx, int choice)
{
	if (choice == 1)
	{
		PX = PX + 1;
		return (mx + 1);
	}
	else if (choice == 2)
	{
		PY = PY + 1;
		return (my + 1);
	}
	else if (choice == 3)
	{
		mx = mx - PX;
		PX = 0;
		return (mx);
	}
	return (0);
}

/*
** Loops through the piece.
** If we find * in the piece array, we
** check the position in the map array,
** based on the value found in map array
** we increment the value of the piece.
** The piece with lowest value is considered
** the best. In case we find enemy, the position
** is invalid or if we find more than one friendly
** position.
*/

static int	conditions(t_filler *f, int my, int mx, int friends)
{
	while (PIECE[PY])
	{
		while (PIECE[PY][PX])
		{
			if (PIECE[PY][PX] == '*' && mx >= 0 &&
				mx < MX && my >= 0 && my < MY)
			{
				if (MAP[my][mx] == ENEMY)
					return (0);
				else if (MAP[my][mx] == FRIEND)
					friends = friends + 1;
				else
					VALUE = VALUE + MAP[my][mx];
				if (friends > 1)
					return (0);
			}
			else if (PIECE[PY][PX] == '*' &&
					(mx >= MX || my >= MY || mx < 0 || my < 0))
				return (0);
			mx = incrementer(f, my, mx, 1);
		}
		my = incrementer(f, my, mx, 2);
		mx = incrementer(f, my, mx, 3);
	}
	return (friends);
}

/*
** Initializes values for fitting piece.
** Calls conditions loop to check if piece
** can be put into the my mx position.
*/

static int	fit_piece(t_filler *f, int my, int mx)
{
	int friends;

	friends = 0;
	VALUE = 0;
	PX = 0;
	PY = 0;
	friends = conditions(f, my, mx, friends);
	if (friends != 1)
		return (0);
	return (1);
}

/*
** Evaluates results of check_fit.
** If value of BEST is still MAX
** it means no position was found
** and we need to exit out. Else
** we print out the coordinates of
** best position.
*/

static int	eval_results(t_filler *f)
{
	if (BEST == MAX)
	{
		free_all(f);
		return (0);
	}
	else
	{
		ft_putnbr(BY);
		write(1, " ", 1);
		ft_putnbr(BX);
		write(1, "\n", 1);
	}
	return (1);
}

/*
** Check_fit cycles through the MAP.
** Each position is sent to fit_piece
** to determine if piece fits in the
** position, if it does fit, it's value
** is evaluated and best value and position
** is kept.
*/

int			check_fit(t_filler *f)
{
	int my;
	int mx;

	my = (PY * -1) + 1;
	mx = (PX * -1) + 1;
	while (my < MY)
	{
		while (mx < MX)
		{
			if (fit_piece(f, my, mx))
			{
				if (evaluator(f, my))
				{
					BEST = VALUE;
					BY = my;
					BX = mx;
				}
			}
			mx = mx + 1;
		}
		mx = ((PX * -1) + 1);
		my = my + 1;
	}
	return (eval_results(f));
}
