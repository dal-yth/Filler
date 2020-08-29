/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:31:45 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/19 18:01:54 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Main loop which calls all other functions.
** As long as there is something for GNL to read,
** we check the buf[0] position or strncmp it.
** Upon finding correct value or "Piece" we call
** appropriate functions to make map, allocate piece
** and simply strdup the buf to PIECE.
** Once all of the piece has been saved, we call
** solving functions. Heat_map assigns values to
** our 2d int array for check_fit to evaluate.
** Check fit attempts to find best position where
** we can put a piece, or if no position is found,
** frees everything and exits program. Finally we
** init values again for next cycles.
*/

int		filler_loop(t_filler *f)
{
	char *buf;

	while (get_next_line(0, &buf) > 0)
	{
		if (ft_isdigit(buf[0]))
			make_map(f, buf);
		else if (buf[1] == 'i')
			allocate_piece(f, buf);
		else if (buf[0] == '.' || buf[0] == '*')
		{
			PIECE[J] = ft_strcpy(PIECE[J], buf);
			J = J + 1;
		}
		free(buf);
		if (J != 0 && J == PY)
		{
			heat_map(f);
			if (!check_fit(f))
				return (0);
			free_piece(f);
			init_filler(f);
		}
	}
	return (0);
}

/*
** Filler main.
** Allocates our struct f, which holds all important
** values. Calls init_filler to initialize values and
** then reads input and saves it to int array.
** Int array is then modified to be a heat map, where
** values are given to each node, depending how close
** they are to the enemy. Next we attempt to put in
** the piece given and save all possible locations
** where placing the piece is valid. Lastly we compare
** values of the possible placements and print out the
** one with smallest value.
*/

int		main(void)
{
	t_filler *f;

	if (!(f = (t_filler*)malloc(sizeof(t_filler))))
		malloc_error();
	init_filler(f);
	read_info(f);
	filler_loop(f);
	write(1, "0 0\n", 4);
	return (0);
}
