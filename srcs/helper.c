/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:08:53 by sako              #+#    #+#             */
/*   Updated: 2019/10/11 21:44:59 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**		change the map color to random color
*/

void	random_color(t_fdf *fdf)
{
	fdf->color.red = (rand() % 0x7F);
	fdf->color.green = (rand() % 0x7F);
	fdf->color.blue = (rand() % 0x7F);
}

/*
**		change the instruction string color to random color
*/

void	random_color_letter(t_fdf *fdf)
{
	fdf->map.inst_color = (rand() % 0xFFFFFF);
}

/*
**		display the instruction to use the fdf program
*/

void	display_instruction(t_fdf *fdf)
{
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 0, fdf->map.inst_color,\
	"[ESC]                        -> Exit Program.");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 20, fdf->map.inst_color,\
	"[Mouse Wheel up/down]        -> Increase/decrease Z value by 1.");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 40, fdf->map.inst_color,\
	"[Keyboard W|S]               -> move upward/downward by 10 pixel.");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 60, fdf->map.inst_color,\
	"[Keyboard A|D]               -> move left/right by 10 pixel.");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 80, fdf->map.inst_color,\
	"[Keyboard Q|E]               -> zoom in/out by 1");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 100, fdf->map.inst_color,\
	"[Keyboard C]                 -> random color map");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 120, fdf->map.inst_color,\
	"[Keyboard V]                 -> random color instruction");
	mlx_string_put(fdf->disp.init, fdf->disp.win, 0, 140, fdf->map.inst_color,\
	"[Keyboard T|P]               -> isometric / parallel projection");
}

/*
**		display the instruction to use the fdf program
*/

void	parallel_projection(t_fdf *fdf)
{
	if (fdf->map.parallel++ % 2)
	{
		fdf->map.angle_x = 1;
		fdf->map.angle_y = 1;
		fdf->map.z_value = 0;
	}
	else
	{
		fdf->map.angle_x = cos(M_PI / 3);
		fdf->map.angle_y = fdf->map.angle_x * sin(M_PI / 6);
		fdf->map.z_value = 1;
	}
}
