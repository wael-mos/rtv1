/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:06:11 by wael-mos          #+#    #+#             */
/*   Updated: 2019/05/23 16:30:21 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WIN_X 700
# define WIN_Y 700
# include "math.h"

typedef struct	s_vec3
{
	float		x;	
	float		y;	
	float		z;	
}				t_vec3;

typedef struct	s_sph
{
	float		r;
	t_vec3		o;
}				t_sph;

typedef struct s_env
{
	t_vec3		cam;
	t_vec3		light;
	t_sph		sph;
}				t_env;

typedef struct	s_data
{
	void                    *mlx;
	void                    *win;
	void                    *img;
    int                    	endian;
    int                     sl;
    int						bpp;
    int                    *img_addr;
	t_env					env;
}				t_data;


#endif