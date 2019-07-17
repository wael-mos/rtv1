/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:54:10 by wael-mos          #+#    #+#             */
/*   Updated: 2019/07/08 15:06:03 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h> //
# include <fcntl.h>
# include <pthread.h>

// # define ERROR_MSG			"Usage:./RTv1 [filename]\n"

#define min(a,b) (((a) < (b)) ? (a) : (b))

/* Width and height of out image */
#define WIN_X	700
#define WIN_Y	700
// #define WIDTH	700
// #define HEIGHT	700

/* The vector structure */
typedef struct	s_vec
{
    float		x;
	float		y;
	float		z;
}				t_vec;

/* The sphere */
typedef struct	s_sph
{
    t_vec		pos;
    float		radius;
	int			material;
}				t_sph; 

/* The ray */
typedef struct	s_ray
{
    t_vec 		start;
    t_vec		dir;
}				t_ray;

/* Colour */
typedef struct	s_col
{
	float		red;
	float		green;
	float		blue;
}				t_col;

/* Material Definition */
typedef struct	s_mat
{
	t_col		diffuse;
	float		reflection;
}				t_mat;

/* Lightsource definition */
typedef struct	s_light
{
	t_vec		pos;
	t_col		intensity;
}				t_light;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			end;

}				t_mlx;

// typedef struct		s_thread
// {
// 	pthread_t		thread;
// 	t_vec			posx;
// 	t_vec			posy;
// 	t_mlx			*data;
// } 					t_thread;

#endif
