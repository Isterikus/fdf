/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 18:49:45 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 16:00:19 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	srav(char *str, int *i, int flag)
{
	if (flag == 1)
		while (str[(*i)] == ' ' || str[(*i)] == '\t')
			(*i)++;
	else
		while (ft_isdigit(str[(*i)]) || str[(*i)] == '-')
			(*i)++;
}

void	get_coords(t_dot *dot, char *str, int wid, int hei)
{
	if (str[0] == '-' && !ft_isdigit(str[1]))
		error("\0", 6);
	dot->z = ft_atoi(str);
	dot->x -= wid / 2;
	dot->y -= hei / 2;
	dot->x *= (WID / (wid * 1.1));
	dot->y *= (WID / (wid * 1.1));
	dot->dt.pz_x = 0;
	dot->dt.pz_y = 0;
	if (wid > 999)
		dot->z *= -((double)(WID * 106.36) / ((double)hei * wid));
	else
		dot->z *= -((double)WID / ((double)hei));
	dot->zz = dot->z;
}

void	set_col(t_dot *dot, char *str, int *i, const char *file)
{
	if (str[(*i)] == ',')
	{
		(*i)++;
		if (ft_strncmp("0x", str + *i, 2))
			return (error(file, 5));
		dot->col = ft_atoi_base(str + (*i) + 2, 16);
		while (str[(*i)] && (str[(*i)] != ' ' && str[(*i)] != '\t' &&
		str[(*i)] != '\n'))
			(*i)++;
	}
	else
		dot->col = 0xffffff;
}

void	mult(t_mlx *mlx)
{
	pthread_t	thread[12];
	t_mult		mult[12];
	int			i;

	i = 0;
	while (i < 12)
	{
		mult[i].mlx = mlx;
		mult[i].flow = i;
		i++;
	}
	i = 0;
	while (i < 12)
	{
		pthread_create(&(thread[i]), NULL, rotate, &(mult[i]));
		i++;
	}
	i = 0;
	while (i < 12)
		pthread_join(thread[i++], NULL);
}

void	*rotate(void *m)
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
			get_dot(&(mult->mlx->dots[y][x++]), mult->mlx->rot_x,
				mult->mlx->rot_y, mult->mlx->rot_z);
		y++;
	}
	return (NULL);
}
