/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   championship.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:28:27 by tboissel          #+#    #+#             */
/*   Updated: 2019/02/11 17:09:35 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMPIONSHIP_H
# define CHAMPIONSHIP_H

# include <time.h>
# include <mlx.h>
# include <stdlib.h>

# include "libft.h"
# include "global.h"

# define ESC 53
# define CTRL 256

typedef struct		s_image
{
	void			*img_ptr;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_image;

typedef struct		s_minilibx
{
	int				w_height;
	int				w_width;
	void			*m_ptr;
	void			*w;
	t_image			img;
}					t_minilibx;

typedef struct		s_fight
{
	int				color;
	char			**names;
	t_list			*players;
	t_list			*begin;
	t_bool			visu;
	t_minilibx		*mlx;
	char			*path;
	char			*vm;
}					t_fight;

void				competition(t_list **players, t_fight *club, int game_nb);
int					ft_full_image(t_fight *club);
void				put_names(t_fight *club);
void				get_coord_champ(t_coord *deb, int i, char *name);
int					key_events(int key, t_fight *club);
void				init_mlx(t_fight *club);
void				draw_rectangle(t_fight *club, int x, int y, int color);
void				draw_vertical_line(int y1, int y2, int x, t_fight *club);
void				draw_horizontal_line(int x1, int x2, int y, t_fight *club);
void				draw_lines(t_fight *club);
void				draw_all_rect(t_fight *club);
void				write_winner_name(char *path, t_fight *club, int gn);
void				competition(t_list **players, t_fight *club, int game_nb);
int					ft_exit(void);
int					rand_a_b(int a, int b);
void				ft_swap(char **a, char **b);
void				randomize_draw(char **names);
void				get_names(t_fight *club, char **av);

#endif
