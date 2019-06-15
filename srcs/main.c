/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:05:37 by wael-mos          #+#    #+#             */
/*   Updated: 2019/06/15 15:30:30 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../rtv1.h"

float	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	length(t_vec3 a)
{
	return (sqrt(dot_product(a, a)));
}

t_vec3	scale(float k, t_vec3 a)
{
	t_vec3	res;

	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

t_vec3	normalize(t_vec3 p)
{
	t_vec3 res;

	if (dot_product(p, p) == 0)
		exit(-1);
	
    float w = 1.0f / sqrtf(dot_product(p, p));
	res = scale(w, p);
	return (res);
}

t_vec2			vec2(float x, float y)
{
	t_vec2	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_ivec2	ivec2(int x, int y)
{
        t_ivec2  res;

        res.start = x;
        res.end = y;
        return (res);
}

t_vec3  mul_vec(t_vec3 a, t_vec3 b)
{
	t_vec3  res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

t_vec2  mul_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2  res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
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

t_vec2  sub_vec2(t_vec2 a, t_vec2 b)
{
        t_vec2  res;

        res.x = a.x - b.x;
        res.y = a.y - b.y;
        return (res);
}

t_vec3  add_vec(t_vec3 a, t_vec3 b)
{
        t_vec3  res;

        res.x = a.x + b.x;
        res.y = a.y + b.y;
        res.z = a.z + b.z;
        return (res);
}

t_vec3  div_vec(t_vec3 a, t_vec3 b)
{
        t_vec3  res;

        res.x = a.x / b.x;
        res.y = a.y / b.y;
        res.z = a.z / b.z;
        return (res);
}

t_vec2  div_vec2(t_vec2 a, t_vec2 b)
{
        t_vec2  res;

        res.x = a.x / b.x;
        res.y = a.y / b.y;
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

t_vec3	cmpxmul(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y, 0.0));
}

// void		put_pixel(int x, int y, int color, t_data *data)
// {
// 	int		i;

// 	i = (x * 4) + (y * data->sl);
// 	data->img_addr[i] = color;
// 	data->img_addr[++i] = color >> 8;
// 	data->img_addr[++i] = color >> 16;
// }

void	put_pixel(int x, int y, int color, t_data *data)
{
	int             i;

	i = x + (y * data->sl);
	data->img_addr[i] = color;
}

// int		create_circle(t_data *data, t_vec2 uv) // first try not that bad but i dont understand why we do that and how to use the result
// {
// 	float	v;
// 	float	d;
// 	// t_vec3	p; // intersection point
// 	// t_vec3	plane;
// 	// t_vec3	sqr; // v squared

// 	float	disc;

// 	// plane = div_vec(vec3((float)x, (float)y, (float)0.0),\
// 	// 	vec3((float)WIN_X, (float)WIN_Y, (float)0.0));
// 	// plane = sub_vec(plane, vec3(0.5, 0.5, 0.0));
// 	// plane = mul_vec(plane, vec3(4.0, 4.0, 0.0));

// 	// plane = vec3((float)x, (float)y, (float)0.0);
// 	v = dot_product(sub_vec(data->env.sph.o, data->env.cam), sub_vec(vec3(uv.x, uv.y, 0.0), data->env.cam));

// 	disc = (data->env.sph.r * data->env.sph.r) - (dot_product(sub_vec(data->env.sph.o, data->env.cam), sub_vec(data->env.sph.o, data->env.cam)) - (v * v));
// 	// printf("%f\n", disc);
	
// 	if (disc < 0)
// 		return (0);
// 	else
// 	{
// 		d = sqrt(disc);
// 		data->p = add_vec(data->env.cam, mul_vec(vec3((v - d), (v - d), (v - d)), sub_vec(vec3(uv.x, uv.y, 0.0), data->env.cam)));
// 	}
// 	return (1);
// }

// float map(t_vec3 p)
// {
//     return length(p) - 1.0;
// }

// float trace(t_vec3 o, t_vec3 r) // from shadertoy the one who seems the most logic and the good way i think
// {
//     float t = 0.0;
//     const int maxSteps = 32;
//     for (int i = 0; i < maxSteps; i++){ 
//         t_vec3 p = add_vec(o, mul_vec(r, vec3(t, t, t)));
//         float d = map(p);
// 		if (d<0.001)
// 			break;
//         t += d * 0.5;
//     }
//     return t;
// }

float	create_sphere(t_data *data, t_vec3 rd) // what i understood from formula found
{
	t_vec3 oc = sub_vec(data->env.cam, data->env.sph.o);
	float a = dot_product(rd, rd);
	// printf("%f\n", a);
	float b = 2.0 * dot_product(rd, oc);
	float c = dot_product(oc, oc) - (data->env.sph.r * data->env.sph.r);
	float d = (b * b) - (4 * a * c);
	if (d < 0.0) // no intersection
		return (-1.0);
	else // 1 or 2
		return (-b - sqrt(d)) / (2.0*a);
	// double	sqrtdiscr;
	// double	t0;
	// double	t1;
	// sqrtdiscr = sqrtf(b * b - 4 * a * c);
	// t0 = (-b + sqrtdiscr) / (2 * a);
	// t1 = (-b - sqrtdiscr) / (2 * a);
	// if (t0 > t1)
	// 	t0 = t1;
	// if (t0 > 0.001f && (*t == -1 || t0 < *t))
	// {
	// 	*t = t0;
	// 	return (1);
	// }
	return (0);
}

int				get_color(t_vec3 color)
{
	return (((int)(color.x * 255)) << 16) | (((int)(color.y * 255)) << 8) |\
	((int)(color.z * 255));
}

static int	toomuch_lineagain(int c, t_thread **thread)
{
	(*thread)->data->env.cam = vec3(500.0, 200.0, 0.0);
	(*thread)->data->env.sph.o = vec3(200.0, 150.0, 10.0);
	(*thread)->data->env.sph.r = 70.0;
	// t_vec2	uv = div_vec2(vec2((float)(*thread)->posx.start, (float)(*thread)->posy.start), vec2((float)WIN_X, (float)WIN_Y));
	// uv = mul_vec2(uv, vec2(2.0, 2.0));
	// uv = sub_vec2(uv, vec2(1.0, 1.0));
	// uv.x *= WIN_X / WIN_Y;
	// t_vec2 uv = div_vec2(sub_vec2(vec2((float)(*thread)->posx.start, (float)(*thread)->posy.start), vec2((float)WIN_X / 2, (float)WIN_Y / 2)), vec2((float)WIN_Y, (float)WIN_Y)); // the good way..
	// printf("X   %f\n", uv.x);fflush(stdout);
	t_vec3 rd = normalize(vec3((float)(*thread)->posx.start, (float)(*thread)->posy.start, 1.0)); //     ||    idk why its working
	// t_vec3 rd = normalize(vec3(uv.x, uv.y, 1.0)); // the good way..

	double t = create_sphere((*thread)->data, rd);
	if (t -= -1)
	{
		t_vec3 new = add_vec(scale(t, rd), (*thread)->data->env.cam);
		put_pixel(new.x, new.y, 0xDDDDDD, (*thread)->data);
	}
	else // just trying to understand where is my ray
		put_pixel((*thread)->posx.start, (*thread)->posy.start, 0xFFDDDD, (*thread)->data);
	// printf("%f\n", t);
	// printf("X2   %f\n", rd.x);fflush(stdout);
	// float t = dot_product(sub_vec((*thread)->data->env.sph.o, (*thread)->data->env.cam), rd);
	// t_vec3 p = add_vec((*thread)->data->env.cam, mul_vec(rd, vec3(t, t, t)));
	// float y = length(sub_vec((*thread)->data->env.sph.o, p));
	// printf("%f     ", y);
	// printf("%f     ", );
		// float x = sqrt(((*thread)->data->env.sph.r * (*thread)->data->env.sph.r) - (y * y));


	// z = NULL;
	// printf("%d\n", c);
	c = 0; //                      The easy way
	// t_vec2	uv = div_vec2(vec2((float)(*thread)->posx.start, (float)(*thread)->posy.start), vec2((float)WIN_X, (float)WIN_Y));
	// uv = mul_vec2(uv, vec2(2.0, 2.0));
	// uv = sub_vec2(uv, vec2(1.0, 1.0));
	// uv.x *= WIN_X / WIN_Y;

	// float r = sqrt(dot_product(uv, uv));
	// if (r < 0.7)
	// c = create_circle((*thread)->data,/* (*thread)->posx.start, (*thread)->posy.start, */uv);
	// if (c == 1)
	// t_vec3 r = vec3(uv.x, uv.y, 1.0);

	// float t = trace((*thread)->data->env.sph.o, r);
	// float fog = 1.0 / (1.0 + t * t * 0.1);

		// if ((*thread)->posx.start > 700 || (*thread)->posx.start < 0)
		// 	printf("1 %d\n", (*thread)->posx.start);
		// (*thread)->data->p = div_vec((*thread)->data->p, vec3(4.0, 4.0, 0.0));
		// (*thread)->data->p = add_vec((*thread)->data->p, vec3(0.5, 0.5, 0.0));
		// (*thread)->data->p = mul_vec((*thread)->data->p, vec3((float)WIN_X, (float)WIN_Y, (float)0.0));
		// printf("2 %f\n", (*thread)->data->p.y);
		// if ((*thread)->data->p.y <= 700 && (*thread)->data->p.y >= 0 && (*thread)->data->p.x <= 700 && (*thread)->data->p.x >= 0)
	return (c);
}

void		*loop_screen(void *tmp)
{
	int				c;
	int				ys;
	t_thread		*thread;

	thread = (t_thread *)tmp;
	ys = thread->posy.start;
	while (thread->posx.start < thread->posx.end)
	{
		thread->posy.start = ys;
		while (thread->posy.start < thread->posy.end)
		{
			c = toomuch_lineagain(c, &thread);
			++thread->posy.start;
		}
		++thread->posx.start;
	}
	return (NULL);
}

static void	init_thread(t_thread *thread, t_data *data, t_ivec2 x, t_ivec2 y)
{
	thread->data = data;
	thread->posx.start = x.start;
	thread->posx.end = x.end;
	thread->posy.start = y.start;
	thread->posy.end = y.end;
	pthread_create(&thread->thread, NULL, loop_screen, thread);
}

int			thread_init(t_data *data)
{
	t_thread	thread[4];

	init_thread(&thread[0], data, ivec2(0, WIN_X / 2), ivec2(0, WIN_Y / 2));
	init_thread(&thread[1], data, ivec2(WIN_X / 2, WIN_X),\
		ivec2(0, WIN_Y / 2));
	init_thread(&thread[2], data, ivec2(0, WIN_X / 2),\
		ivec2(WIN_Y / 2, WIN_Y));
	init_thread(&thread[3], data, ivec2(WIN_X / 2, WIN_X),\
		ivec2(WIN_Y / 2, WIN_Y));
	pthread_join(thread[0].thread, NULL);
	pthread_join(thread[1].thread, NULL);
	pthread_join(thread[2].thread, NULL);
	pthread_join(thread[3].thread, NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int			deal_key(int key, char *s)
{
	s = NULL;
	if (key == 53)
		exit(1);
	return (0);
}

int			deal_close(void)
{
	exit(1);
	return (0);
}

int	main(void)
{
	t_data	data;
	
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, "h");
	data.img = mlx_new_image(data.mlx, WIN_X, WIN_Y);
	data.img_addr = (int *)mlx_get_data_addr(data.img, &data.bpp,\
		&data.sl, &data.endian);
	data.env.cam = vec3(200.0, 0.0, 50.0);
	data.env.sph.o = vec3(40.0, -70.0, 10.0);
	data.env.sph.r = 30.0;
	mlx_loop_hook(data.mlx, thread_init, &data);
	mlx_hook(data.win, 17, (1L << 17), deal_close, NULL);
	mlx_hook(data.win, 2, 0, deal_key, NULL);
	mlx_loop(data.mlx);
	// create_circle(&data, 0, 0);
	return (0);
}
