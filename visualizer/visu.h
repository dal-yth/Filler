/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:36:43 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/21 18:36:44 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# include "../includes/filler.h"
# include "../libft/includes/libft.h"

# define S v->save
# define H v->heat
# define VY v->vy
# define VX v->vx
# define ENEM v->v_enemy
# define FREN v->v_friend

typedef struct	s_visu
{
	int			**map;
	char		*final;
	int			total;
	int			save;
	int			heat;
	int			vx;
	int			vy;
	int			v_friend;
	int			v_enemy;
}				t_visu;

void			save_input(t_visu *v);
void			options(char **argv, t_visu *v);

void			init_visu(t_visu *v);
void			format_error(void);
void			roll_with_it(void);
void			malloc_error(void);
void			allocate_map(t_visu *v, char *buf);

void			print_heat(t_visu *v, int fd);
void			fren_enem(t_visu *v, char *buf);
void			allocate_map(t_visu *v, char *buf);
void			make_heat(t_visu *v);
void			error(void);

#endif
