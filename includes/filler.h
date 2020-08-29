/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:39:56 by jmakela           #+#    #+#             */
/*   Updated: 2020/02/18 09:18:09 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "../libft/includes/libft.h"

# define MAX 2147483647
# define MAP f->map
# define PIECE f->piece
# define VALUE f->value
# define BEST f->best_value
# define MX f->mx
# define MY f->my
# define PX f->px
# define PY f->py
# define BY f->best_y
# define BX f->best_x
# define PLAYER f->player
# define I f->index
# define J f->jindex
# define ENEMY f->enemy
# define FRIEND f->friend

/*
** Filler struct.
** Holds our map, current piece, piece value,
** best piece value, player number, map x, map y,
** piece x, piece y, best piece x, best piece y,
** two index values and values for friend and enemy.
*/

typedef struct		s_filler
{
	int				**map;
	char			**piece;
	int				value;
	int				best_value;
	int				player;
	int				mx;
	int				my;
	int				px;
	int				py;
	int				best_x;
	int				best_y;
	int				index;
	int				jindex;
	int				enemy;
	int				friend;
}					t_filler;

/*
** Map and piece functions.
*/

void				read_info(t_filler *f);
void				make_map(t_filler *f, char *buf);
void				allocate_piece(t_filler *f, char *buf);
void				heat_map(t_filler *f);
int					check_fit(t_filler *f);
void				free_piece(t_filler *f);

/*
** Utilities.
*/

void				free_all(t_filler *f);
void				malloc_error(void);
void				init_filler(t_filler *f);
void				friend_enemy(t_filler *f);
int					evaluator(t_filler *f, int my);

#endif
