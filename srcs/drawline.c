/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:17:35 by sako              #+#    #+#             */
/*   Updated: 2019/09/24 20:17:38 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_pixel(t_fdf *fdf, int x, int y, double u_vector)
{
	int		i;

	if ((x > 0 && y > 0) && (x < W_WIDTH && y < W_HEIGHT))
	{
		i = (x * 4) + (y * W_WIDTH * 4);
		fdf->image.data[i + 0] = fdf->color.blue + u_vector;
		fdf->image.data[i + 1] = fdf->color.green + u_vector;
		fdf->image.data[i + 2] = fdf->color.red + u_vector;
		fdf->image.data[i + 3] = 0x7F + u_vector;
	}
}

/*
**	Draw line based on two points, (x0, y0) and (x1, y1) using
*/

static void	plot_line(t_fdf *fdf)
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	double	u_vector;

	x = fdf->map.x0;
	y = fdf->map.y0;
	delta_x = fdf->map.x1 - fdf->map.x0;
	delta_y = fdf->map.y1 - fdf->map.y0;
	u_vector = sqrt((pow(delta_y, 2)) + (pow(delta_x, 2)));
	delta_x /= u_vector;
	delta_y /= u_vector;
	while (u_vector > 0)
	{
		draw_pixel(fdf, x, y, u_vector);
		x += delta_x;
		y += delta_y;
		u_vector -= 1;
	}
}

/*
**	Draw vertical line... Based on x-y coordinates, draw x lines.
*/

static void	draw_horizontal_line(t_fdf *fdf, int x, int y)
{
	int		xp;
	int		yp;

	xp = x - fdf->map.width / 2;
	yp = y - fdf->map.height / 2;
	fdf->map.x0 = fdf->map.angle_x * (xp - yp) * fdf->map.zoom;
	fdf->map.y0 = fdf->map.angle_y * (xp + yp) * fdf->map.zoom;
	fdf->map.y0 -= fdf->map.values[y][x] * fdf->map.z_value;
	fdf->map.x1 = fdf->map.angle_x * ((xp + 1) - yp) * fdf->map.zoom;
	fdf->map.y1 = fdf->map.angle_y * ((xp + 1) + yp) * fdf->map.zoom;
	fdf->map.y1 -= fdf->map.values[y][x + 1] * fdf->map.z_value;
	fdf->map.x0 += (W_WIDTH / 2) + fdf->map.coord_x;
	fdf->map.x1 += (W_WIDTH / 2) + fdf->map.coord_x;
	fdf->map.y0 += (W_HEIGHT / 2) + fdf->map.coord_y;
	fdf->map.y1 += (W_HEIGHT / 2) + fdf->map.coord_y;
	plot_line(fdf);
}

/*
**	Draw horizontal line... Based on x-y coordinates, draw y lines.
*/

static void	draw_vertical_line(t_fdf *fdf, int x, int y)
{
	int		xp;
	int		yp;

	xp = x - fdf->map.width / 2;
	yp = y - fdf->map.height / 2;
	fdf->map.x0 = fdf->map.angle_x * (xp - yp) * fdf->map.zoom;
	fdf->map.y0 = fdf->map.angle_y * (xp + yp) * fdf->map.zoom;
	fdf->map.y0 -= fdf->map.values[y][x] * fdf->map.z_value;
	fdf->map.x1 = fdf->map.angle_x * (xp - (yp + 1)) * fdf->map.zoom;
	fdf->map.y1 = fdf->map.angle_y * (xp + (yp + 1)) * fdf->map.zoom;
	fdf->map.y1 -= fdf->map.values[y + 1][x] * fdf->map.z_value;
	fdf->map.x0 += (W_WIDTH / 2) + fdf->map.coord_x;
	fdf->map.x1 += (W_WIDTH / 2) + fdf->map.coord_x;
	fdf->map.y0 += (W_HEIGHT / 2) + fdf->map.coord_y;
	fdf->map.y1 += (W_HEIGHT / 2) + fdf->map.coord_y;
	plot_line(fdf);
}

/*
**	Draw the map, based on zoom size, and average value of window size.
*/

int			draw_wireframe(t_fdf *fdf)
{
	int		x;
	int		y;

	y = -1;
	fdf->disp.img = mlx_new_image(fdf->disp.init, W_WIDTH, W_HEIGHT);
	fdf->image.data = mlx_get_data_addr(fdf->disp.img, &fdf->image.bpp, \
		&fdf->image.size_line, &fdf->image.endian);
	while (++y < fdf->map.height)
	{
		x = -1;
		while (++x < fdf->map.width)
		{
			if (x + 1 < fdf->map.width)
				draw_horizontal_line(fdf, x, y);
			if (y + 1 < fdf->map.height)
				draw_vertical_line(fdf, x, y);
		}
	}
	mlx_put_image_to_window(fdf->disp.init, fdf->disp.win, fdf->disp.img, 0, 0);
	display_instruction(fdf);
	mlx_destroy_image(fdf->disp.init, fdf->disp.img);
	return (0);
}
