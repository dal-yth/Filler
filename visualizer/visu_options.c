/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:18 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:19 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
** Calls format error in case
** there are wrong amount of options.
*/

static void	options_error(t_visu *v)
{
	if (S && H)
		format_error();
	if (S > 1)
		format_error();
	if (H > 1)
		format_error();
}

/*
** Checks for options.
** only s and h are tolerated and
** there can be only one option.
*/

void		options(char **argv, t_visu *v)
{
	int i;

	i = 1;
	if (argv[1][0] != '-')
		format_error();
	while (argv[1][i])
	{
		if (argv[1][i] == 's')
			S = S + 1;
		if (argv[1][i] == 'h')
			H = H + 1;
		if (argv[1][i] != 'h' && argv[1][i] != 's')
			format_error();
		i = i + 1;
	}
	options_error(v);
}
