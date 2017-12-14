/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 18:41:15 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 17:33:44 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(const char *file, int num)
{
	(num == 0) ? ft_printf("No arguments!\n") : 0;
	(num == 1) ? ft_printf("No such file {bold}%s{eoc}\n", file) : 0;
	(num == 2) ? ft_printf("Empty file {bold}%s{eoc}\n", file) : 0;
	(num == 3) ? ft_printf("Invalid number in file {bold}%s{eoc}\n", file) : 0;
	(num == 4) ? ft_printf("Invalid separator in file {bold}%s{eoc}\n",
		file) : 0;
	(num == 5) ? ft_printf("Invalid color in file {bold}%s{eoc}\n", file) : 0;
	(num == 6) ? ft_printf("Invalid file {bold}%s{eoc}\n", file) : 0;
	exit(0);
}

void	fill_param(t_mlx *mlx, const char *file)
{
	int		rd;
	int		fd;
	char	*buff;
	char	*str;

	str = NULL;
	(ft_strcmp(file, "./fdf") == 0) ? exit(0) : 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error(file, 1));
	buff = (char *)malloc(sizeof(char) * (10000001));
	while ((rd = read(fd, buff, 10000000)) > 0)
	{
		buff[rd] = '\0';
		str = ft_strjoin2(str, buff);
	}
	free(buff);
	close(fd);
	(str == NULL) ? error(file, 2) : 0;
	fill_struct(mlx, str, file);
	ft_bzero(str, ft_strlen(str));
	free(str);
}

void	fill_struct(t_mlx *mlx, char *str, const char *file)
{
	int		i;
	int		x;
	int		y;

	basic(mlx, &i, &y, str);
	while (str[i])
	{
		x = 0;
		mlx->dots[++y] = (t_dot *)malloc(sizeof(t_dot ) * (mlx->wid_dots));
		while (str[i] && str[i] != '\n')
		{
			srav(str, &i, 1);
			(!ft_isdigit(str[i]) && str[i] != '-') ? (error(file, 3)) : 0;
			mlx->dots[y][x].x = x;
			mlx->dots[y][x].y = y;
			get_coords(&(mlx->dots[y][x]), str + i, mlx->wid_dots,
				mlx->hei_dots);
			srav(str, &i, 2);
			set_col(&(mlx->dots[y][x++]), str, &i, file);
			srav(str, &i, 1);
		}
		(str[i]) ? i++ : 0;
	}
	(y + 1 != mlx->hei_dots || x != mlx->wid_dots) ? error(file, 6) : 0;
}

void	basic(t_mlx *mlx, int *i, int *y, char *str)
{
	*i = 0;
	*y = -1;
	mlx->hei_dots = count_size(str, 0);
	mlx->wid_dots = count_size(str, 1);
	mlx->wid = WID;
	mlx->hei = HEI;
	mlx->dots = (t_dot **)malloc(sizeof(t_dot *) * (mlx->hei_dots));
}

int		count_size(char *str, int flag)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	(flag == 0) ? ret++ : 0;
	if (flag == 0)
	{
		while (str[i])
			(str[i++] == '\n') ? ret++ : 0;
	}
	else
		while (str[i] && str[i] != '\n')
		{
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			while (ft_isdigit(str[i]) || str[i] == '-')
				i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			ret++;
		}
	return (ret);
}
