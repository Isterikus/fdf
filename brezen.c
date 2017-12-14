/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 18:54:07 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 15:54:44 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_dot(t_dot *dot, double rx, double ry, double rz)
{
	t_rot	rot;

	rx = (rx * M_PI) / 180;
	ry = (ry * M_PI) / 180;
	rz = (rz * M_PI) / 180;
	rot.x0 = dot->x;
	rot.y0 = dot->y * cos(rx) + dot->z * sin(rx);
	rot.z0 = dot->z * cos(rx) - dot->y * sin(rx);
	rot.x1 = rot.x0 * cos(ry) - rot.z0 * sin(ry);
	rot.y1 = rot.y0;
	rot.z1 = rot.z0 * cos(ry) + rot.x0 * sin(ry);
	dot->dt.x = rot.x1 * cos(rz) + rot.y1 * sin(rz) + 500 + dot->dt.pz_x;
	dot->dt.y = rot.y1 * cos(rz) - rot.x1 * sin(rz) + 500 + dot->dt.pz_y;
	dot->dt.col = dot->col;
}

void	mult2(t_mlx *mlx)
{
	pthread_t	thread[12];
	t_mult		mult[12];
	int			i;

	i = -1;
	if (mlx->hei_dots == 1 && mlx->wid_dots == 1)
	{
		fill_str(&(mlx->map), mlx->dots[0][0].dt.x,
			mlx->dots[0][0].dt.y, mlx->dots[0][0].col);
		return ;
	}
	while (++i < 12)
	{
		mult[i].mlx = mlx;
		mult[i].flow = i;
	}
	while (--i >= 0)
	{
		if (mlx->wid_dots < 999)
			pthread_create(&(thread[i]), NULL, print_all_grad, &(mult[i]));
		else
			pthread_create(&(thread[i]), NULL, print_all, &(mult[i]));
	}
	while (i < 12)
		pthread_join(thread[i++], NULL);
}

void	*print_all(void *m)
{
	int		x;
	int		y;
	int		hei;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			print_srav(mult, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*print_all_grad(void *m)
{
	int		x;
	int		y;
	int		hei;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			print_srav_g(mult, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	print_srav(t_mult *mult, int x, int y)
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
			line(mult->mlx, mult->mlx->dots[y][x].dt,
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
			line(mult->mlx, mult->mlx->dots[y][x].dt,
				mult->mlx->dots[y + 1][x].dt);
	}
}
