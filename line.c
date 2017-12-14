/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 18:59:37 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 16:02:48 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line(t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2)
{
	t_line	line;

	line.dt_x = abs(dot2.x - dot1.x);
	line.dt_y = abs(dot2.y - dot1.y);
	line.sx = OR(dot1.x, dot2.x);
	line.sy = OR(dot1.y, dot2.y);
	line.i = 1;
	fill_str(&(mlx->map), dot1.x, dot1.y, dot1.col);
	if (line.dt_y <= line.dt_x)
		line1(line, mlx, dot1);
	else
		line2(line, mlx, dot1);
}

void	fill_str(char **str, int x, int y, int col)
{
	if (y * WID * 4 + x * 4 >= 0 && x < WID && x > 0
		&& y * WID * 4 + x * 4 < WID * HEI * 4)
	{
		(*str)[y * WID * 4 + x * 4] = (col & 0xff);
		(*str)[y * WID * 4 + x * 4 + 1] = (col & 0xff00) >> 8;
		(*str)[y * WID * 4 + x * 4 + 2] = (col & 0xff0000) >> 16;
	}
}

void	line1(t_line line, t_mlx *mlx, t_2d_dot dot1)
{
	line.dt = (line.dt_y << 1) - line.dt_x;
	line.dt1 = line.dt_y << 1;
	line.dt2 = (line.dt_y - line.dt_x) << 1;
	line.x = dot1.x + line.sx;
	line.y = dot1.y;
	while (line.i++ <= line.dt_x)
	{
		if (line.dt > 0)
		{
			line.dt += line.dt2;
			line.y += line.sy;
		}
		else
			line.dt += line.dt1;
		fill_str(&(mlx->map), line.x, line.y, dot1.col);
		line.x += line.sx;
	}
}

void	line2(t_line line, t_mlx *mlx, t_2d_dot dot1)
{
	line.dt = (line.dt_x << 1) - line.dt_y;
	line.dt1 = line.dt_x << 1;
	line.dt2 = (line.dt_x - line.dt_y) << 1;
	line.x = dot1.x;
	line.y = dot1.y + line.sy;
	while (line.i++ <= line.dt_y)
	{
		if (line.dt > 0)
		{
			line.dt += line.dt2;
			line.x += line.sx;
		}
		else
			line.dt += line.dt1;
		fill_str(&(mlx->map), line.x, line.y, dot1.col);
		line.y += line.sy;
	}
}

void	print_srav_g(t_mult *mult, int x, int y)
{
	if (x + 1 != mult->mlx->wid_dots)
	{
		if (!(mult->mlx->dots[y][x].dt.x < 0 &&
		mult->mlx->dots[y][x].dt.y < 0 && mult->mlx->dots[y][x + 1].dt.x < 0
		&& mult->mlx->dots[y][x + 1].dt.y < 0) &&
		!(mult->mlx->dots[y][x].dt.x > WID &&
		mult->mlx->dots[y][x].dt.y > WID &&
		mult->mlx->dots[y][x + 1].dt.x > WID &&
		mult->mlx->dots[y][x + 1].dt.y > WID))
			line_grad(mult->mlx, mult->mlx->dots[y][x].dt,
				mult->mlx->dots[y][x + 1].dt);
	}
	if (y + 1 != mult->mlx->hei_dots)
	{
		if (!(mult->mlx->dots[y][x].dt.x < 0 &&
		mult->mlx->dots[y][x].dt.y < 0 && mult->mlx->dots[y + 1][x].dt.x < 0
		&& mult->mlx->dots[y + 1][x].dt.y < 0) &&
		!(mult->mlx->dots[y][x].dt.x > WID &&
		mult->mlx->dots[y][x].dt.y > WID &&
		mult->mlx->dots[y + 1][x].dt.x > WID &&
		mult->mlx->dots[y + 1][x].dt.y > WID))
			line_grad(mult->mlx, mult->mlx->dots[y][x].dt,
				mult->mlx->dots[y + 1][x].dt);
	}
}
