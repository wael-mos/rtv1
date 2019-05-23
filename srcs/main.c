/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:05:37 by wael-mos          #+#    #+#             */
/*   Updated: 2019/05/23 16:42:33 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3  mul_vec(t_vec3 a, t_vec3 b)
{
	t_vec3  res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

t_vec3  sub_vec(t_vec3 a, t_vec3 b)
{
        t_vec3  res;

        res.x = a.x - b.x;
        res.y = a.y - b.y;
        res.z = a.z - b.z;
        return (res);
}

t_vec3	vec3(float x, float y, float z)
{
        t_vec3  res;

        res.x = x;
        res.y = y;
        res.z = z;
        return (res);
}

void	put_pixel(int x, int y, int color, t_data *data)
{
	int             i;

	i = x + (y * data->sl);
	data->img_addr[i] = color;
}

float	dot_product(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res = mul_vec(a, b);
	return (res.x + res.y + res.z);
}

void	create_circle(t_data *data)
{
	float	v;

	v = dot_product(sub_vec(data->env.sph.o, data->env.cam), );
}

int	main(int ac, char **av)
{
	t_data	data;
	
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, av[1]);
	data.img = mlx_new_image(data.mlx, WIN_X, WIN_Y);
	data.img_addr = (int *)mlx_get_data_addr(data.img, &data.bpp,\
		&data.sl, &data.endian);
	data.env.cam = vec3(0.0, 0.0, 0.0);
	data.env.sph.o = vec3(1.0, 1.0, 0.0);
	data.env.sph.r = 2.0;
	create_circle(&data);
}
