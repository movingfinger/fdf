/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:46:41 by sako              #+#    #+#             */
/*   Updated: 2019/10/04 20:46:43 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	check the string is valid number or not.
*/

int			check_numbers(char *s)
{
	int		i;
	char	*test;

	i = 0;
	test = ft_itoa(ft_atoi(s));
	while (test[i])
	{
		if (i == 0 && test[i] == '-')
			++i;
		if (!ft_isdigit(test[i]))
			return (0);
		++i;
	}
	free(test);
	return (1);
}

/*
**	Count the single line length, for columns. We will use cols
**	to allocate the memory for single pointer integer, x values.
*/

static int	count_len(char *line)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_strsplit(line, ' ');
	while (res[i])
	{
		if (!check_numbers(res[i]))
			ft_puterror("Wrong characters!", 5);
		free(res[i]);
		++i;
	}
	free(res);
	return (i);
}

/*
**	Check the how many line in the file then store this value to rows.
**	We will use rows to allocate the memory for double pointer integer.
**	If rows value and height is not same, then we have wrong format.
*/

static int	count_rows(t_fdf *fdf, char *argv)
{
	int		fd;
	int		len;
	int		cols;
	int		rows;
	char	*line;

	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_puterror("Wrong opening file!", 1);
	cols = 0;
	rows = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (*line == '\0')
			break ;
		if ((len = count_len(line)) > cols)
			cols = len;
		(cols == len) ? rows += 1 : ft_puterror("Cols != length not same!", 4);
		free(line);
	}
	if (close(fd) < 0)
		ft_puterror("Wrong closing file :)", 2);
	if (!(fdf->map.width = cols))
		ft_puterror("Width != cols!", 4);
	return (rows);
}

/*
**	Check the z value for 2.5D representation. Use ft_split to generate
**	double integer pointer, then using ft_atoi to extract the number to store
**	as z values.
*/

static void	store_values(t_fdf *fdf, int x, int y, char *line)
{
	int		i;
	char	**split;

	if ((split = ft_strsplit(line, ' ')))
	{
		i = 0;
		while (split[i] && (x != fdf->map.width))
		{
			fdf->map.values[y][x] = ft_atoi(split[i]);
			ft_strdel(&split[i++]);
			++x;
		}
		free(split);
	}
}

/*
** Read from file name, then store width and height for fdf.
*/

void		read_fdf(char *file, t_fdf *fdf)
{
	int		x;
	int		y;
	int		fd;
	char	*line;

	x = 0;
	y = 0;
	fdf->map.height = count_rows(fdf, file);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_puterror("Wrong opening file!", 1);
	if (!(fdf->map.values = (int **)malloc(sizeof(int *) * fdf->map.height)))
		ft_puterror("Wrong double memory allocation!", 3);
	while (get_next_line(fd, &line) == 1 && y != fdf->map.height)
	{
		if (!(fdf->map.values[y] = (int *)malloc(sizeof(int) * fdf->map.width)))
			ft_puterror("Wrong single memory allocation!", 3);
		store_values(fdf, x, y, line);
		x = 0;
		++y;
		free(line);
	}
	if (close(fd) < 0)
		ft_puterror("Error closing file! WTF?! :)", 2);
}
