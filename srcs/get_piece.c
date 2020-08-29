/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:35:31 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/19 17:55:17 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Frees the piece and initializes values.
*/

void		free_piece(t_filler *f)
{
	int i;

	i = 0;
	while (PIECE[i])
	{
		free(PIECE[i]);
		i = i + 1;
	}
	free(PIECE);
}

/*
** Gets the dimensions of the piece.
*/

static void	get_piecedims(t_filler *f, char *buf)
{
	int i;

	i = 6;
	while (buf[i] != ' ')
	{
		PY = PY * 10 + (buf[i] - 48);
		i = i + 1;
	}
	i = i + 1;
	while (buf[i] != ':')
	{
		PX = PX * 10 + (buf[i] - 48);
		i = i + 1;
	}
}

/*
** Finds the dimensions of the piece and
** allocates correct amount of space.
*/

void		allocate_piece(t_filler *f, char *buf)
{
	int i;

	i = 0;
	get_piecedims(f, buf);
	if (!(PIECE = (char**)malloc(sizeof(char*) * PY + 1)))
		malloc_error();
	while (i < PY)
	{
		if (!(PIECE[i] = (char*)malloc(sizeof(char) * PX + 1)))
			malloc_error();
		i = i + 1;
	}
	PIECE[PY] = NULL;
}
