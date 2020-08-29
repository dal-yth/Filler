/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:35:53 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:35:54 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	free_stuff(t_visu *v)
{
	int i;

	i = 0;
	while (i < VY)
	{
		free(v->map[i]);
		i = i + 1;
	}
	free(v->map);
}

/*
** Visualizer main.
** Checks amount of options, allocates out struct,
** Evaluates options if there are any and calls
** save input to process data and visualize it.
*/

int		main(int argc, char **argv)
{
	t_visu *v;

	if (argc > 2)
	{
		roll_with_it();
		write(2, "Error, too many options\n", 24);
		return (0);
	}
	if (!(v = (t_visu*)malloc(sizeof(t_visu))))
		malloc_error();
	init_visu(v);
	if (argc == 2)
		options(argv, v);
	save_input(v);
	free(v);
	return (0);
}
