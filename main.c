/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 18:25:05 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 16:22:13 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_colors4(t_mlx *mlx)
{
	int		y;
	int		x;
	int		min;
	int		max;
	int		diff;

	min = find(mlx, 0);
	max = find(mlx, 1);
	diff = min - max;
	y = 0;
	while (y < mlx->hei_dots)
	{
		x = 0;
		while (x < mlx->wid_dots)
		{
			mlx->dots[y][x].col = 0x140d1b + ((int)((1 - (double)(
				(mlx->dots[y][x].z - max) / diff)) * 0x3f) << 16) + ((int)((1 -
				(double)((mlx->dots[y][x].z - max) / diff)) * 0x27) << 8)
			+ (int)((1 - (double)((mlx->dots[y][x].z - max) / diff)) * 0x52);
			x++;
		}
		y++;
	}
}

void	image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WID, HEI);
	mlx->map = mlx_get_data_addr(mlx->img, &(mlx->trash),
		&(mlx->wid), &(mlx->trash2));
	mult(mlx);
	mult2(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	image2(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WID, HEI);
	mlx->map = mlx_get_data_addr(mlx->img, &(mlx->trash),
		&(mlx->wid), &(mlx->trash2));
	mult2(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	basic_main(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->trash = 32;
	mlx->trash2 = 0;
	mlx->wid = WID * 4;
	mlx->rot_x = 0.0;
	mlx->rot_y = 0.0;
	mlx->rot_z = 0.0;
}

int		main(int argc, const char *argv[])
{
	int			i;
	t_mlx		mlx;

	(argc == 1) ? error(NULL, 0) : 0;
	i = 0;
	while (argc - i >= 2)
	{
		if (fork() == 0)
			break ;
		i++;
	}
	basic_main(&mlx);
	fill_param(&mlx, argv[i]);
	mlx.win = mlx_new_window(mlx.mlx, WID, HEI, "FDF MADAFAKA");
	mlx.img = mlx_new_image(mlx.mlx, WID, HEI);
	mlx.map = mlx_get_data_addr(mlx.img, &(mlx.trash),
		&(mlx.wid), &(mlx.trash2));
	mult(&mlx);
	mult2(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 2, 5, keys, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
