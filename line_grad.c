/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_grad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:02:14 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 16:05:14 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_grad(t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2)
{
	t_line	line;

	line.dt_x = abs(dot2.x - dot1.x);
	line.dt_y = abs(dot2.y - dot1.y);
	line.sx = OR(dot1.x, dot2.x);
	line.sy = OR(dot1.y, dot2.y);
	line.i = 1;
	fill_str(&(mlx->map), dot1.x, dot1.y, dot1.col);
	line.grad_r = ((int)dot1.col >> 16) & 0xff;
	line.grad_g = ((int)dot1.col >> 8) & 0xff;
	line.grad_b = ((int)dot1.col & 0xff);
	if (line.dt_y <= line.dt_x)
		line_grad1(line, mlx, dot1, dot2);
	else
		line_grad2(line, mlx, dot1, dot2);
}

void	line_grad1(t_line line, t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2)
{
	line.dt = (line.dt_y << 1) - line.dt_x;
	line.dt1 = line.dt_y << 1;
	line.dt2 = (line.dt_y - line.dt_x) << 1;
	line.x = dot1.x + line.sx;
	line.y = dot1.y;
	calc_diff(&line, dot1.col, dot2.col, line.dt_x);
	while (line.i++ <= line.dt_x)
	{
		if (line.dt > 0)
		{
			line.dt += line.dt2;
			line.y += line.sy;
		}
		else
			line.dt += line.dt1;
		line.grad_r = line.grad_r + line.diff_r;
		line.grad_g = line.grad_g + line.diff_g;
		line.grad_b = line.grad_b + line.diff_b;
		fill_str(&(mlx->map), line.x, line.y, (((int)line.grad_r & 0xff) << 16)
		+ (((int)line.grad_g & 0xff) << 8) + ((int)line.grad_b & 0xff));
		line.x += line.sx;
	}
}

void	line_grad2(t_line line, t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2)
{
	line.dt = (line.dt_x << 1) - line.dt_y;
	line.dt1 = line.dt_x << 1;
	line.dt2 = (line.dt_x - line.dt_y) << 1;
	line.x = dot1.x;
	line.y = dot1.y + line.sy;
	calc_diff(&line, dot1.col, dot2.col, line.dt_y);
	while (line.i++ <= line.dt_y)
	{
		if (line.dt > 0)
		{
			line.dt += line.dt2;
			line.x += line.sx;
		}
		else
			line.dt += line.dt1;
		line.grad_r = line.grad_r + line.diff_r;
		line.grad_g = line.grad_g + line.diff_g;
		line.grad_b = line.grad_b + line.diff_b;
		fill_str(&(mlx->map), line.x, line.y, (((int)line.grad_r << 16) &
			0xff0000) + (((int)line.grad_g << 8) & 0xff00) +
			((int)line.grad_b & 0xff));
		line.y += line.sy;
	}
}

void	calc_diff(t_line *line, int col1, int col2, int del)
{
	line->diff_r = ((double)((col2 >> 16) - (col1 >> 16))) / (double)del;
	line->diff_g = ((double)((col2 >> 8) & 0xff) - ((col1 >> 8) & 0xff))
					/ (double)del;
	line->diff_b = ((double)((col2 & 0xff) - (col1 & 0xff))) / (double)del;
}

int		get_grad(int now, int col1, int col2, int cou)
{
	int		ret;
	int		r;
	int		g;
	int		b;

	r = now & 0xff0000;
	g = now & 0xff00;
	b = now & 0xff;
	if (cou == 0)
		return (col2);
	r = r + ((((((col2 & 0xff0000) - (col1 & 0xff0000)) >> 16) / cou)
		& 0xff) << 16);
	g = g + ((((((col2 & 0xff00) - (col1 & 0xff00)) >> 8) / cou) & 0xff) << 8);
	b = b + ((((col2 & 0xff) - (col1 & 0xff)) / cou) & 0xff);
	ret = r + g + b;
	return (ret);
}
