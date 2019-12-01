/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:50:50 by sako              #+#    #+#             */
/*   Updated: 2019/06/21 21:49:25 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
**	Call headers
*/

# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "keys.h"
# include <sys/types.h>
# include <sys/stat.h>

/*
**	Define variables
*/

# define MAX_Z			(30)
# define W_WIDTH 		1280
# define W_HEIGHT		960

# define SMALL(x, y) ((x) > (y) ? (y) : (x))
# define BIG(x, y) ((x) > (y) ? (x) : (y))

/*
**	Define structures
*/

/*
**	strucutre for display
*/

typedef struct	s_display
{
	void		*init;
	void		*win;
	void		*img;
}				t_display;

/*
**	structure for image data
*/

typedef struct	s_image
{
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_map
{
	int			**values;
	int			width;
	int			height;
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	int			coord_x;
	int			coord_y;
	int			zoom;
	int			isometric;
	int			parallel;
	int			inst_color;
	double		z_value;
	double		angle_x;
	double		angle_y;

}				t_map;

typedef struct	s_fdf
{
	t_display	disp;
	t_map		map;
	t_image		image;
	t_color		color;
}				t_fdf;

/*
**	functions from other c files
*/

int				draw_wireframe(t_fdf *fdf);
void			read_fdf(char *file, t_fdf *fdf);
void			random_color(t_fdf *fdf);
void			random_color_letter(t_fdf *fdf);
void			display_instruction(t_fdf *fdf);
void			parallel_projection(t_fdf *fdf);

#endif
