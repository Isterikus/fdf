/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:10:05 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 16:01:11 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keys(int key, t_mlx *mlx)
{
	(key == K_UP) ? mlx->rot_x += 1.0 : 0;
	(key == K_DOWN) ? mlx->rot_x -= 1.0 : 0;
	(key == K_LEFT) ? mlx->rot_z += 1.0 : 0;
	(key == K_RIGHT) ? mlx->rot_z -= 1.0 : 0;
	(key == K_LL) ? mlx->rot_y -= 1.0 : 0;
	(key == K_RR) ? mlx->rot_y += 1.0 : 0;
	(key == K_PLUS) ? mult3(mlx, 0) : 0;
	(key == K_MINUS) ? mult3(mlx, 1) : 0;
	(key == K_PLUS2) ? mult3(mlx, 2) : 0;
	(key == K_MINUS2) ? mult3(mlx, 3) : 0;
	(key == K_A) ? mult3(mlx, 4) : 0;
	(key == K_D) ? mult3(mlx, 5) : 0;
	(key == K_W) ? mult3(mlx, 6) : 0;
	(key == K_S) ? mult3(mlx, 7) : 0;
	(key == K_NUM_1) ? fill_colors(mlx) : 0;
	(key == K_NUM_2) ? fill_colors2(mlx) : 0;
	(key == K_NUM_3) ? fill_colors3(mlx) : 0;
	(key == K_NUM_4) ? fill_colors4(mlx) : 0;
	(key == K_ESC) ? exit(0) : 0;
	if (key == K_A || key == K_D || key == K_W || key == K_S)
		image2(mlx);
	else
		image(mlx);
	return (0);
}

void	mult3(t_mlx *mlx, int flag)
{
	pthread_t	thread[12];
	t_mult		mult[12];
	int			i;

	i = -1;
	while (++i < 12)
	{
		mult[i].mlx = mlx;
		mult[i].flow = i;
	}
	i = -1;
	while (++i < 12)
	{
		(flag == 0) ? pthread_create(&(thread[i]), NULL, dob, &(mult[i])) : 0;
		(flag == 1) ? pthread_create(&(thread[i]), NULL, del, &(mult[i])) : 0;
		(flag == 2) ? pthread_create(&(thread[i]), NULL, z_pl, &(mult[i])) : 0;
		(flag == 3) ? pthread_create(&(thread[i]), NULL, z_min, &(mult[i])) : 0;
		(flag == 4) ? pthread_create(&(thread[i]), NULL, x_l, &(mult[i])) : 0;
		(flag == 5) ? pthread_create(&(thread[i]), NULL, x_r, &(mult[i])) : 0;
		(flag == 6) ? pthread_create(&(thread[i]), NULL, y_w, &(mult[i])) : 0;
		(flag == 7) ? pthread_create(&(thread[i]), NULL, y_s, &(mult[i])) : 0;
	}
	i = 0;
	while (i < 12)
		pthread_join(thread[i++], NULL);
}

void	*dob(void *m)
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
			mult->mlx->dots[y][x].x *= 1.1;
			mult->mlx->dots[y][x].y *= 1.1;
			mult->mlx->dots[y][x].z *= 1.1;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*del(void *m)
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
			mult->mlx->dots[y][x].x /= 1.1;
			mult->mlx->dots[y][x].y /= 1.1;
			mult->mlx->dots[y][x].z /= 1.1;
			x++;
		}
		y++;
	}
	return (NULL);
}

void	*z_pl(void *m)
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
			mult->mlx->dots[y][x].z += mult->mlx->dots[y][x].zz / 10;
			x++;
		}
		y++;
	}
	return (NULL);
}
