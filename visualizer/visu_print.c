/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:26 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:27 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
** Opens the trace file written by filler_vm
** and prints out it's information.
*/

static void	print_trace(void)
{
	char	*buf;
	int		fd;

	fd = open("filler.trace", O_RDONLY);
	while (get_next_line(fd, &buf) > 0)
	{
		ft_printf("%s\n", buf);
		free(buf);
	}
	close(fd);
}

/*
** Basic printer.
** Reads lines from fd which points to visu.txt.
** Prints them out with ft_printf and if
** 'Plateau' buf is found, clears the screen and
** waits.
*/

static void	print_basic(int fd)
{
	char *buf;

	get_next_line(fd, &buf);
	if (ft_isdigit(buf[0]))
		ft_printf("%s\n", buf + 4);
	else if (buf[0] == 'P' && buf[1] == 'l')
	{
		usleep(80000);
		system("clear");
	}
	free(buf);
}

/*
** Allocates map and final string.
*/

void		allocate_h(t_visu *v, char *buf)
{
	allocate_map(v, buf);
	(!(v->final = (char*)malloc(sizeof(char) * (((VX * 11) * VY) + VY + 1)))) ?
	malloc_error() : 0;
}

/*
** Heart of the printer.
** Saves input to a text file "visu.txt", if it
** does not exist, creates it. If there is already
** something in the file, truncates it to 0 length.
** Opens visu.txt twice, once for writing and once
** for reading if there is a need for print.
** Calls print_basic and print_heat depenging on option.
*/

void		save_input(t_visu *v)
{
	char	*buf;
	int		fd;
	int		fd2;

	fd = open("visu.txt", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	(!S) ? fd2 = open("visu.txt", O_RDONLY) : 0;
	while (get_next_line(0, &buf) > 0)
	{
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		if (H == 1 && buf[0] == '$')
			fren_enem(v, buf);
		else if (H == 2 && !ft_strncmp(buf, "Plateau", 7))
			allocate_h(v, buf);
		else if (!S && !H)
			print_basic(fd2);
		else if (H && buf[1] == 'i')
			print_heat(v, fd2);
		free(buf);
	}
	(!S) ? close(fd2) : 0;
	close(fd);
	(H) ? free(v->final) : 0;
	(!S) ? print_trace() : 0;
}
