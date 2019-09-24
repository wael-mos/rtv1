/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:54:31 by evogel            #+#    #+#             */
/*   Updated: 2019/09/22 17:53:21 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int        cylinder_intersect(t_ray *r, t_obj *s, float *t)
{
	float    A;
	float    B;
	float    C;
	float    discr;

	/* https://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf page 2
http://woo4.me/wootracer/cylinder-intersection/ */

	// t_vec DrxDc = cross(r->dir, s->rot);
	// t_vec OrxDc = cross(r->ori, s->rot);
	// t_vec OcxDc = cross(s->pos, s->rot);
	t_vec temp = r->dir;
	t_vec p0 = sub_vec(r->ori, s->pos);
	p0 = rotate_z(p0, M_PI * .5);
	// p0 = rotate_z(p0, M_PI * .1);
	temp = rotate_z(temp, M_PI * .5);
	// temp = rotate_z(temp, M_PI * .1);
// t_vec3  pdp = vec3_substract(cp.direction, cp.position);
	// t_vec first = cross(sub_vec(r->ori, s->pos), p0);
    // // t_vec3  eyexpdp = vec3_cross(vec3_substract(r.origin, cp.position), pdp);
	// t_vec second = cross(r->dir, p0);
    // // t_vec3  rdxpdp = vec3_cross(r.direction, pdp);
	// A = dot(second, second);
	// B = 2 * dot(second, first);
	// C = dot(first, first) - (s->rad * s->rad * \
	// dot(p0, p0));

	// A = 1;
	// B = 2.0f * (dot(DrxDc, OrxDc) - dot(DrxDc, OcxDc));
	// C = 
	// A = 1;
	// B = 2.f * dot(second, first);
	// C = dot(first, first) - (s->rad * s->rad * dot(p0, p0));

	// A = dot(r->dir, r->dir) - pow(dot(r->dir, s->rot), 2); // Its funny with 1 1 0 or 0 1 1 in normal
	// B = 2 * (dot(r->dir, p0) - dot(r->dir, s->rot) * dot(p0, s->rot));
	// C = dot(p0, p0) - pow(dot(p0, s->rot), 2) - s->rad * s->rad;


	A = (temp.x * temp.x) + (temp.z * temp.z);
	B = 2 * (temp.x * p0.x) + 2 * (temp.z * p0.z);
	C = (p0.x * p0.x) + (p0.z * p0.z) - (s->rad * s->rad);

	discr = B * B - 4 * A * C;
	if (discr >= 0)
	{
		float t0;
		float t1;

		t0 = (-B + sqrtf(discr))/(2 * A);
		t1 = (-B - sqrtf(discr))/(2 * A);

		/* We want the closest one */
		if (t0 > t1)
			t0 = t1;

		/* Verify t1 larger than 0 and less than the original t */
		if ((t0 > 0.001f) && (t0 < *t))
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int		sphere_intersect(t_ray *r, t_obj *s, float *t)
{

	/* A = d.d, the vector dot product of the direction */
	float A; 
	A = dot(r->dir, r->dir); 

	/* We need a vector representing the distance between the ori of 
	 * the ray and the position of the circle.
	 * This is the term (p0 - c) 
	 */
	t_vec dist;
	dist = sub_vec(r->ori, s->pos);

	/* 2d.(p0 - c) */  
	float B;
	B = 2 * dot(r->dir, dist);

	/* (p0 - c).(p0 - c) - r^2 */
	float C;
	C = dot(dist, dist) - (s->rad * s->rad);

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
		return (0);
	else
	{
		float t0;
		float t1;

		t0 = (-B + sqrtf(discr))/2;
		t1 = (-B - sqrtf(discr))/2;

		/* We want the closest one */
		if (t0 > t1)
			t0 = t1;

		/* Verify t1 larger than 0 and less than the original t */
		if ((t0 > 0.001f) && (t0 < *t))
		{
			*t = t0;
			return (1);
		}
	}
	return (0);
}

int        plane_intersect(t_ray *r, t_obj *s, float *t)
{
	int ret = 0;
	float    A;
	float    B;
	float    t0;
	// float    discr;
	float epsilon;

	epsilon = 0.0001f;
	t_vec p0;
	p0 = sub_vec(s->pos, r->ori);
	A = dot(p0, s->rot);
	B = dot(r->dir, s->rot);
	if (B <= epsilon)
	{
		ret = 0;
	}
	else
	{
		t0 = A / B;
		if (t0 > epsilon && t0 < *t)
		{
			*t = t0;
			ret = 1;
		}
	}
	return (ret);
}

int cone_intersect(t_ray *r, t_obj *s, float *t)
{
    float    epsilon;
    int        ret;
    ret = 0;
    epsilon = 0.00001f;

	float angle;
	angle = 1 - (s->rad / M_PI);

    /* A = d.d, the vector dot product of the direction */
    t_vec p0;
	t_vec temp;
	temp = r->dir;
    p0 = sub_vec(r->ori, s->pos);
	// p0 = rotate_z(p0, M_PI * .5);
	// temp = rotate_z(temp, M_PI * .5);
    float A;
    A = dot(temp, s->rot) * dot(temp, s->rot) - angle * angle;
    
    /* 2d.(p0 - c) */
    float B;
    B = 2 * ((dot(temp, s->rot) * dot(p0, s->rot)) - dot(temp, p0) * angle * angle);
    
    /* (p0 - c).(p0 - c) - r^2 */
    float C;
    C = dot(p0, s->rot) * dot(p0, s->rot) - dot(p0, p0) * angle * angle;
    
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
        t0 = (-B + sqrtdiscr)/(2 * A);
        t1 = (-B - sqrtdiscr)/(2 * A);
        
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
