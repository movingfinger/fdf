/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:22:26 by sako              #+#    #+#             */
/*   Updated: 2019/06/21 22:47:14 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	reset(t_fdf *fdf)
{
	fdf->image.bpp = 4;
	fdf->image.endian = 0;
	fdf->map.coord_x = 0;
	fdf->map.coord_y = 0;
	fdf->map.zoom = SMALL(W_WIDTH, W_HEIGHT)\
	/ BIG(fdf->map.width, fdf->map.height);
	fdf->image.size_line = fdf->image.bpp * fdf->map.width;
	fdf->map.angle_x = cos(M_PI / 3);
	fdf->map.angle_y = fdf->map.angle_x * sin(M_PI / 6);
	fdf->map.z_value = 1.00;
	fdf->map.isometric = 1;
	fdf->map.parallel = 1;
	fdf->color.red = 0x4F;
	fdf->color.green = 0x4F;
	fdf->color.blue = 0x4F;
	fdf->map.inst_color = 0xFFFFFF;
}

static int		deal_key(int key, t_fdf *fdf)
{
	if (key == KEY_ESCAPE)
		exit(0);
	else if (key == KEY_ANSI_R)
		reset(fdf);
	else if (key == KEY_ANSI_D)
		fdf->map.coord_x += 10;
	else if (key == KEY_ANSI_A)
		fdf->map.coord_x -= 10;
	else if (key == KEY_ANSI_W)
		fdf->map.coord_y -= 10;
	else if (key == KEY_ANSI_S)
		fdf->map.coord_y += 10;
	else if (key == KEY_ANSI_Q)
		fdf->map.zoom += 1;
	else if (key == KEY_ANSI_E)
		fdf->map.zoom -= 1;
	else if (key == KEY_ANSI_C)
		random_color(fdf);
	else if (key == KEY_ANSI_V)
		random_color_letter(fdf);
	else if (key == KEY_ANSI_T)
		fdf->map.angle_y *= (fdf->map.isometric++ % 2) ? 0.2 : 5;
	else if (key == KEY_ANSI_P)
		parallel_projection(fdf);
	return (0);
}

static int		fdf_mouses(int button, int x, int y, t_fdf *fdf)
{
	int		prev_x;
	int		prev_y;

	prev_x = x;
	prev_y = y;
	if ((button == 4) && (fdf->map.z_value < MAX_Z))
		fdf->map.z_value += 1;
	else if ((button == 5) && (fdf->map.z_value > -MAX_Z))
		fdf->map.z_value -= 1;
	return (0);
}

int				main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac == 2)
	{
		if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
			ft_puterror("ERROR: Memory Allocation failed", 1);
		read_fdf(av[1], fdf);
		reset(fdf);
		fdf->disp.init = mlx_init();
		if (!(fdf->disp.win = mlx_new_window(fdf->disp.init, W_WIDTH,\
		W_HEIGHT, av[1])))
			ft_puterror("Creating new window failed!", 1);
		mlx_hook(fdf->disp.win, 2, 3, deal_key, fdf);
		mlx_hook(fdf->disp.win, 4, 3, fdf_mouses, fdf);
		mlx_loop_hook(fdf->disp.init, draw_wireframe, fdf);
		mlx_loop(fdf->disp.init);
	}
	return (0);
}
