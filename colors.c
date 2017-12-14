/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:05:44 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 15:59:13 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		find(t_mlx *mlx, int flag)
{
	int		ret;
	int		y;
	int		x;

	ret = mlx->dots[0][0].z;
	y = 0;
	while (y < mlx->hei_dots)
	{
		x = 0;
		while (x < mlx->wid_dots)
		{
			if (flag == 0 && mlx->dots[y][x].z > ret)
				ret = mlx->dots[y][x].z;
			else if (flag == 1 && mlx->dots[y][x].z < ret)
				ret = mlx->dots[y][x].z;
			x++;
		}
		y++;
	}
	return (ret);
}

void	fill_colors(t_mlx *mlx)
{
	int		y;
	int		x;
	int		min;
	int		max;
	int		snow;

	min = find(mlx, 0);
	max = find(mlx, 1);
	snow = max * 0.7;
	y = -1;
	while (++y < mlx->hei_dots)
	{
		x = -1;
		while (++x < mlx->wid_dots)
			if (mlx->dots[y][x].z > 0)
				mlx->dots[y][x].col = (1 - mlx->dots[y][x].z / min) * 155;
			else if (mlx->dots[y][x].z == 0)
				mlx->dots[y][x].col = 155;
			else if (mlx->dots[y][x].z > snow)
				mlx->dots[y][x].col = (int)((1 -
					mlx->dots[y][x].z / max) * 155) << 8;
			else if (mlx->dots[y][x].z < snow)
				mlx->dots[y][x].col = 0xffffff - ((1 -
					mlx->dots[y][x].z / max) * 205);
	}
}

void	fill_colors2(t_mlx *mlx)
{
	int		y;
	int		x;
	int		min;
	int		max;
	int		wh;

	min = find(mlx, 0);
	max = find(mlx, 1);
	y = -1;
	while (++y < mlx->hei_dots)
	{
		x = -1;
		while (++x < mlx->wid_dots)
			if (mlx->dots[y][x].z > 0)
				mlx->dots[y][x].col = (1 - mlx->dots[y][x].z / min) * 155;
			else if (mlx->dots[y][x].z == 0)
				mlx->dots[y][x].col = 155;
			else
			{
				wh = 204 + (mlx->dots[y][x].z / max) * 51;
				mlx->dots[y][x].col = (wh << 16) + (wh << 8) + wh;
			}
	}
}

void	fill_colors3_hate_norminette(t_dot *dot, int min, int max, int snow)
{
	if (dot->z > 0)
		dot->col = (1 - dot->z / min) * 155;
	else if (dot->z == 0)
		dot->col = 155;
	else if (dot->z > snow)
		dot->col = (int)((1 - dot->z / max) * 155) << 8;
	else if (dot->z < snow)
	{
		dot->col = 0xffffff - ((1 - dot->z / max) * 205);
		if (dot->col > 0xffffff)
			dot->col = 0xffffff;
	}
}

void	fill_colors3(t_mlx *mlx)
{
	int		y;
	int		x;
	int		min;
	int		max;
	int		snow;

	min = find(mlx, 0);
	max = find(mlx, 1);
	snow = max * 0.7;
	y = 0;
	while (y < mlx->hei_dots)
	{
		x = -1;
		while (++x < mlx->wid_dots)
			if ((y > 1000 || y < 90 || (y < 150 && x > 850 && x < 1250)) &&
			mlx->dots[y][x].z < 0)
				mlx->dots[y][x].col = ((int)(204 + (mlx->dots[y][x].z / max) *
				51) << 16) + ((int)(204 + (mlx->dots[y][x].z / max) * 51) << 8)
				+ 204 + (mlx->dots[y][x].z / max) * 51;
			else
				fill_colors3_hate_norminette(&(mlx->dots[y][x]),
				min, max, snow);
		y++;
	}
}
