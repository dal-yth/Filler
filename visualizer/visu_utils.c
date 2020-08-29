/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:34 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:34 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
** Makes sure visualizer doesn't terminate
** on whatever process it is called to visualize.
** if options or input is otherwise wrong roll_with_it
** simply reads through everything without interrupting
** processes that feed it information through pipe.
*/

void	roll_with_it(void)
{
	char *buf;

	while (get_next_line(0, &buf))
		free(buf);
}

/*
** Format error is called in case of
** wrong input. Shows usage.
*/

void	format_error(void)
{
	roll_with_it();
	ft_dprintf(2, "Incorrect format\n");
	ft_dprintf(2, "Usage is: '-hs'\n");
	ft_dprintf(2, "If no option is specified, prints basic visualization\n");
	ft_dprintf(2, "h: for heatmap, s: for nothing but saves input to a file\n");
	ft_dprintf(2, "Latest game can always be found in 'visu.txt'\n");
	exit(0);
}

/*
** In case of malloc error.
** Calls roll_with it, which keeps whatever
** wrong input we are receiving rolling and
** once there is nothing else to read, exits.
*/

void	malloc_error(void)
{
	roll_with_it();
	ft_dprintf(2, "Malloc error\n");
	exit(0);
}

/*
** Inits option values to zero.
*/

void	init_visu(t_visu *v)
{
	S = 0;
	H = 0;
}

/*
** Attempts to detect '[./filler]' from buf.
** Assigns values for friend and enemy.
*/

void	fren_enem(t_visu *v, char *buf)
{
	if (!ft_strncmp(buf + 14, "[./jmakela.filler]", 18))
	{
		FREN = -1;
		ENEM = -2;
	}
	else
	{
		ENEM = -1;
		FREN = -2;
	}
	H = H + 1;
}
