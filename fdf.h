/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 18:28:21 by dkovalen          #+#    #+#             */
/*   Updated: 2017/05/09 15:37:08 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# include <string.h>
# include <pthread.h>

# include <mlx.h>
# include "libft/printf_functions/includes/header.h"

# define OR(x0, x1) (x1 > x0) ? 1 : -1

# define WID 1000
# define HEI 1000

# define K_ESC		53
# define K_UP		126
# define K_DOWN		125
# define K_LEFT		123
# define K_RIGHT	124
# define K_LL		83
# define K_RR		85
# define K_W		13
# define K_A		0
# define K_S		1
# define K_D		2
# define K_SPACE	49
# define K_NUM_1	18
# define K_NUM_2	19
# define K_NUM_3	20
# define K_NUM_4	21
# define K_PLUS		69
# define K_MINUS	78
# define K_PLUS2	24
# define K_MINUS2	27

typedef struct s_2d_dot		t_2d_dot;
typedef struct s_dot		t_dot;
typedef struct s_line		t_line;
typedef struct s_rot		t_rot;
typedef struct s_mlx		t_mlx;
typedef struct s_mult		t_mult;

struct	s_2d_dot
{
	int				x;
	int				y;
	int				pz_x;
	int				pz_y;
	int				col;
};

struct	s_dot
{
	double			x;
	double			y;
	double			z;
	double			zz;
	int				col;
	t_2d_dot		dt;
};

struct	s_line
{
	int				dt_x;
	int				dt_y;
	int				sx;
	int				sy;
	int				dt;
	int				dt1;
	int				dt2;
	int				x;
	int				y;
	int				i;
	double			grad_r;
	double			grad_g;
	double			grad_b;
	double			diff_r;
	double			diff_g;
	double			diff_b;
};

struct	s_rot
{
	int				x0;
	int				y0;
	int				z0;
	int				x1;
	int				y1;
	int				z1;
};

struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*map;
	int				hei;
	int				wid;
	int				set_col;
	int				hei_dots;
	int				wid_dots;
	float			rot_x;
	float			rot_y;
	float			rot_z;
	int				trash;
	int				trash2;
	int				flow;
	t_dot			**dots;
};

struct	s_mult
{
	int				flow;
	t_mlx			*mlx;
};

/*
**	read_map.c
*/
void	error(const char *file, int num);
void	fill_param(t_mlx *mlx, const char *file);
void	fill_struct(t_mlx *mlx, char *str, const char *file);
void	basic(t_mlx *mlx, int *i, int *y, char *str);
int		count_size(char *str, int flag);

/*
**	fill_struct.c
*/
void	srav(char *str, int *i, int flag);
void	get_coords(t_dot *dot, char *str, int wid, int hei);
void	set_col(t_dot *dot, char *str, int *i, const char *file);
void	mult(t_mlx *mlx);
void	*rotate(void *m);

/*
**	brezen.c
*/
void	get_dot(t_dot *dot, double rx, double ry, double rz);
void	mult2(t_mlx *mlx);
void	*print_all(void *m);
void	*print_all_grad(void *m);
void	print_srav(t_mult *mult, int x, int y);

/*
**	line.c
*/
void	line(t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2);
void	fill_str(char **str, int x, int y, int col);
void	line1(t_line line, t_mlx *mlx, t_2d_dot dot1);
void	line2(t_line line, t_mlx *mlx, t_2d_dot dot1);
void	print_srav_g(t_mult *mult, int x, int y);

/*
**	line_grad.c
*/
void	line_grad(t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2);
void	line_grad1(t_line line, t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2);
void	line_grad2(t_line line, t_mlx *mlx, t_2d_dot dot1, t_2d_dot dot2);
void	calc_diff(t_line *line, int col1, int col2, int del);
int		get_grad(int now, int col1, int col2, int cou);

/*
**	colors.c
*/
int		find(t_mlx *mlx, int flag);
void	fill_colors(t_mlx *mlx);
void	fill_colors2(t_mlx *mlx);
void	fill_colors3_hate_norminette(t_dot *dot, int min, int max, int snow);
void	fill_colors3(t_mlx *mlx);

/*
**	keys1.c
*/
int		keys(int key, t_mlx *mlx);
void	mult3(t_mlx *mlx, int flag);
void	*dob(void *m);
void	*del(void *m);
void	*z_pl(void *m);

/*
**	keys2.c
*/
void	*z_min(void *m);
void	*x_l(void *m);
void	*x_r(void *m);
void	*y_w(void *m);
void	*y_s(void *m);

/*
**	main.c
*/
void	fill_colors4(t_mlx *mlx);
void	image(t_mlx *mlx);
void	image2(t_mlx *mlx);

#endif
