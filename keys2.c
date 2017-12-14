/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:11:55 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/07 19:17:49 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*z_min(void *m)
{
	int		y;
	int		x;
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
			mult->mlx->dots[y][x].z -= mult->mlx->dots[y][x].zz / 10;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*x_l(void *m)
{
	int		y;
	int		x;
	int		hei;
	int		diff;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	diff = WID / 100;
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			mult->mlx->dots[y][x].dt.pz_x += diff;
			mult->mlx->dots[y][x].dt.x += diff;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*x_r(void *m)
{
	int		y;
	int		x;
	int		hei;
	int		diff;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	diff = WID / 100;
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			mult->mlx->dots[y][x].dt.pz_x -= diff;
			mult->mlx->dots[y][x].dt.x -= diff;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*y_w(void *m)
{
	int		y;
	int		x;
	int		hei;
	int		diff;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	diff = HEI / 100;
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			mult->mlx->dots[y][x].dt.pz_y += diff;
			mult->mlx->dots[y][x].dt.y += diff;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*y_s(void *m)
{
	int		y;
	int		x;
	int		hei;
	int		diff;
	t_mult	*mult;

	mult = (t_mult *)m;
	y = ((mult->mlx->hei_dots * mult->flow) / 12);
	hei = ((mult->mlx->hei_dots * (mult->flow + 1)) / 12);
	diff = HEI / 100;
	while (y < hei)
	{
		x = 0;
		while (x < mult->mlx->wid_dots)
		{
			mult->mlx->dots[y][x].dt.pz_y -= diff;
			mult->mlx->dots[y][x].dt.y -= diff;
			x++;
		}
		y++;
	}
	return (NULL);
}
