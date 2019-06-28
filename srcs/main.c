/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:05:37 by wael-mos          #+#    #+#             */
/*   Updated: 2019/06/28 10:46:48 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "rtv1.h"

t_vec	vec(float x, float y, float z)
{
        t_vec  res;

        res.x = x;
        res.y = y;
        res.z = z;
        return (res);
}

/* Subtract two vectors and return the resulting vector */
t_vec sub_vec(t_vec *v1, t_vec *v2)
{
	t_vec res;
	
	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float dot_product(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/* Calculate Vector x Scalar and return resulting Vector*/ 
t_vec scale(float c, t_vec *v)
{
    t_vec res;
	
	res.x = v->x * c;
	res.y = v->y * c;
	res.z = v->z * c;
	return (res);
}

/* Add two vectors and return the resulting vector */
t_vec add_vec(t_vec *v1, t_vec *v2)
{
    t_vec res;
	
	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

/* Check if the ray and sphere intersect */
int intersectRaySphere(t_ray *r, t_sph *s, float *t)
{
	
	int ret;
	ret = 0;

	/* A = d.d, the vector dot product of the direction */
	float A; 
	A = dot_product(&r->dir, &r->dir); 
	
	/* We need a vector representing the distance between the start of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	t_vec dist;
	dist = sub_vec(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B;
	B = 2 * dot_product(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C;
	C = dot_product(&dist, &dist) - (s->radius * s->radius);
	
	/* Solving the discriminant */
	float discr;
	discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 * t represents the distance between the start of the ray and
	 * the point on the sphere where it intersects.
	 */
	if (discr < 0)
		ret = 0;
	else
	{
		float sqrtdiscr;
		float t0;
		float t1;
		
		sqrtdiscr = sqrtf(discr);
		t0 = (-B + sqrtdiscr)/(2);
		t1 = (-B - sqrtdiscr)/(2);
		
		/* We want the closest one */
		if (t0 > t1)
			t0 = t1;

		/* Verify t1 larger than 0 and less than the original t */
		if ((t0 > 0.001f) && (t0 < *t))
		{
			*t = t0;
			ret = 1;
		}
		else
			ret = 0;
	}
return (ret);
}

/* I'm using it for the shadow */

int intersectRayCylinder(t_ray *r, t_sph *s, float *t)
{
	
	float	k;
	int		ret;
	t_vec	rot;

	ret = 0;
	rot = vec(0, 1, 0);
	k = s->radius;

	/* A = d.d, the vector dot product of the direction */
	float A;
	A = dot_product(&r->dir, &r->dir) - pow(dot_product(&r->dir, &rot), 2) *(1 + k * k);
	t_vec dist;
	dist = sub_vec(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B;
	B = 2 * (dot_product(&r->dir, &dist) - (1 + k * k) * dot_product(&r->dir, &rot));
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C;
	C = dot_product(&dist, &dist) - (1 + k * k) * pow(dot_product(&dist, &rot), 2);
	
	/* Solving the discriminant */
	float discr;
	discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 * t represents the distance between the start of the ray and
	 * the point on the sphere where it intersects.
	 */
	if (discr < 0)
		ret = 0;
	else
	{
		float sqrtdiscr;
		float t0;
		float t1;

		sqrtdiscr = sqrtf(discr);
		t0 = (-B + sqrtdiscr)/(2);
		t1 = (-B - sqrtdiscr)/(2);
		
		/* We want the closest one */
		if (t0 > t1)
			t0 = t1;

		/* Verify t1 larger than 0 and less than the original t */
		if ((t0 > 0.001f) && (t0 < *t))
		{
			*t = t0;
			ret = 1;
		}
		else
			ret = 0;
	}
return (ret);
}

// void	put_pixel(int x, int y, int color, t_mlx *data)
// {
// 	int             i;

// 	i = x + (y * data->size_line);
// 	data->data[i] = color;
// }

int		toomuch_lineagain(t_mlx *data)
{
	t_ray r;
	unsigned int number_mat;

	number_mat = 4;

	t_mat materials[number_mat];
	materials[0].diffuse.red = 1;
	materials[0].diffuse.green = 1;
	materials[0].diffuse.blue = 0;
	materials[0].reflection = 0.2;
	
	materials[1].diffuse.red = 0;
	materials[1].diffuse.green = 1;
	materials[1].diffuse.blue = 1;
	materials[1].reflection = 0.5;
	
	materials[2].diffuse.red = 1;
	materials[2].diffuse.green = 1;
	materials[2].diffuse.blue = 1;
	materials[2].reflection = 0.9;

	materials[3].diffuse.red = 1;
	materials[3].diffuse.green = 0;
	materials[3].diffuse.blue = 1;
	materials[3].reflection = 0.2;
	
	t_sph spheres[number_mat];
	spheres[0].pos.x = 150;
	spheres[0].pos.y = 200;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;
	
	spheres[1].pos.x = 400;
	spheres[1].pos.y = 400;
	spheres[1].pos.z = 0;
	spheres[1].radius = 100;
	spheres[1].material = 1;
	
	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 100;
	spheres[2].material = 2;
	
	spheres[3].pos.x = 0;
	spheres[3].pos.y = 0;
	spheres[3].pos.z = 0;
	spheres[3].radius = 100;
	spheres[3].material = 3;
	
	t_light lights[number_mat];
	lights[0].pos.x = 0;
	lights[0].pos.y = 0;
	lights[0].pos.z = -100;
	lights[0].intensity.red = 1;
	lights[0].intensity.green = 1;
	lights[0].intensity.blue = 1;
	
	lights[1].pos.x = 400;
	lights[1].pos.y = -700;
	lights[1].pos.z = -700;
	lights[1].intensity.red = 0.6;
	lights[1].intensity.green = 0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 1000;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.red = 0.3;
	lights[2].intensity.green = 0.5;
	lights[2].intensity.blue = 1;

	lights[3].pos.x = 0;
	lights[3].pos.y = 0;
	lights[3].pos.z = -100;
	lights[3].intensity.red = 0.3;
	lights[3].intensity.green = 0.5;
	lights[3].intensity.blue = 1;
	
	/* Will contain the raw image */

	
	int x;
	int y;
	// y = (*thread)->posy.x;
	y = 0;
	while (y < WIN_Y)
	{
		// x = (*thread)->posx.x;
		x = 0;
		while (x < WIN_X)
		{
			
			float red;
			float green;
			float blue;
			
			red = 0;
			green = 0;
			blue = 0;
			
			int level;
			float coef;
			
			level = 0;
			coef = 1.0;
			
			r.start.x = x;
			r.start.y = y;
			r.start.z = -2000;
			
			r.dir.x = 0;
			r.dir.y = 0;
			r.dir.z = 1;
			
			while ((coef > 0.0f) && (level < 15))
			{
				/* Find closest intersection */
				float t;
				int currentSphere;
				
				t = 20000.0f;
				currentSphere = -1;
				
				unsigned int i;
				i = 0;

				while (i < number_mat)
				{
					if (intersectRaySphere(&r, &spheres[i], &t))
						currentSphere = i;
					i++;
				}
				if (currentSphere == -1)
					break;
				
				t_vec scaled;
				t_vec newStart;
				
				scaled = scale(t, &r.dir);
				newStart = add_vec(&r.start, &scaled);
				
				/* Find the normal for this new vector at the point of intersection */
				t_vec n;
				float temp;

				n = sub_vec(&newStart, &spheres[currentSphere].pos);
				temp = dot_product(&n, &n);
				if (temp == 0)
					break;
				
				temp = 1.0f / sqrtf(temp);
				n = scale(temp, &n);

				/* Find the material to determine the colour */
				t_mat currentMat;
				currentMat = materials[spheres[currentSphere].material];
				
				/* Find the value of the light at this point */
				unsigned int j;
				j = 0;

				while (j++ < 3)
				{
					t_light currentLight;
					t_vec dist;
					
					currentLight = lights[j];
					dist = sub_vec(&currentLight.pos, &newStart);
					if (dot_product(&n, &dist) <= 0.0f)
						continue;
					float t;
					t = sqrtf(dot_product(&dist,&dist));
					if (t <= 0.0f)
						continue;
					
					t_ray lightRay;
					lightRay.start = newStart;
					lightRay.dir = scale((1/t), &dist);
					
					/* Calculate shadows */
					int inShadow;
					unsigned int k;
					
					inShadow = 0;
					k = 0;
					while (++k < number_mat)
					{
						if (intersectRayCylinder(&lightRay, &spheres[k], &t))
						{
							inShadow = 1;
							break;
						}
					}
					if (!inShadow)
					{
						/* Lambert diffusion */
						float lambert;
						lambert = dot_product(&lightRay.dir, &n) * coef; 
						red += lambert * currentLight.intensity.red * currentMat.diffuse.red;
						green += lambert * currentLight.intensity.green * currentMat.diffuse.green;
						blue += lambert * currentLight.intensity.blue * currentMat.diffuse.blue;
					}
				}
				/* Iterate over the reflection */
				coef *= currentMat.reflection;
				
				/* The reflected ray start and direction */
				float reflect;
				t_vec tmp;
				
				r.start = newStart;
				reflect = 2.0f * dot_product(&r.dir, &n);
				tmp = scale(reflect, &n);
				r.dir = sub_vec(&r.dir, &tmp);

				level++;

			}
			int color;
            color = pow(256,2) * (unsigned char)min(red * 255.0f, 255.0f) + 256 * (unsigned char)min(green * 255.0f, 255.0f) + (unsigned char)min(blue * 255.0f, 255.0f);
			data->data[(x + y * WIN_X) + 0] = color;
			// put_pixel(x, y, color, (*thread)->data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image_ptr, 0, 0);
	return (0);
}

/* Not working */

// void		*loop_screen(void *tmp)
// {
// 	int				ys;
// 	t_thread		*thread;

// 	thread = (t_thread *)tmp;
// 	ys = thread->posy.x;
// 	while (thread->posx.x < thread->posx.y)
// 	{
// 		thread->posy.x = ys;
// 		while (thread->posy.x < thread->posy.y)
// 		{
// 			toomuch_lineagain(&thread);
// 			++thread->posy.x;
// 		}
// 		++thread->posx.x;
// 	}
// 	return (NULL);
// }

// static void	init_thread(t_thread *thread, t_mlx *data, t_vec x, t_vec y)
// {
// 	thread->data = data;
// 	thread->posx.x = x.x;
// 	thread->posx.y = x.y;
// 	thread->posy.x = y.x;
// 	thread->posy.y = y.y;
// 	pthread_create(&thread->thread, NULL, loop_screen, thread);
// }

// int			thread_init(t_mlx *data)
// {
// 	t_thread	thread[4];

// 	init_thread(&thread[0], data, vec(0, WIN_X / 2, 0), vec(0, WIN_Y / 2, 0));
// 	init_thread(&thread[1], data, vec(WIN_X / 2, WIN_X, 0),\
// 		vec(0, WIN_Y / 2, 0));
// 	init_thread(&thread[2], data, vec(0, WIN_X / 2, 0),\
// 		vec(WIN_Y / 2, WIN_Y, 0));
// 	init_thread(&thread[3], data, vec(WIN_X / 2, WIN_X, 0),\
// 		vec(WIN_Y / 2, WIN_Y, 0));
// 	pthread_join(thread[0].thread, NULL);
// 	pthread_join(thread[1].thread, NULL);
// 	pthread_join(thread[2].thread, NULL);
// 	pthread_join(thread[3].thread, NULL);
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image_ptr, 0, 0);
// 	return (0);
// }

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
	t_mlx	data;
	
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "RTv1");
	data.image_ptr = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y);
	data.data = (int *)mlx_get_data_addr(data.image_ptr, &data.bpp,\
		&data.size_line, &data.end);
	mlx_loop_hook(data.mlx_ptr, toomuch_lineagain, &data);
	mlx_hook(data.win_ptr, 17, (1L << 17), deal_close, NULL);
	mlx_hook(data.win_ptr, 2, 0, deal_key, NULL);
	mlx_loop(data.mlx_ptr);
	// create_circle(&data, 0, 0);
	return (0);
}
