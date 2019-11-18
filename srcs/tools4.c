/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:03:04 by evogel            #+#    #+#             */
/*   Updated: 2019/11/18 13:25:30 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_col	color(float red, float green, float blue)
{
	t_col	res;

	res.r = red;
	res.g = green;
	res.b = blue;
	return (res);
}

void	add_color(t_col *ori, t_col *add, float amount)
{
	ori->r += add->r * amount;
	ori->g += add->g * amount;
	ori->b += add->b * amount;
}

void	errormsg(t_env *env, int msg)
{
	if (msg == 1)
		ft_printf("Error: Please provide a valid XML file.\n");
	else if (msg == 2)
		ft_printf("Error: Failed malloc.\n");
	else if (msg == 3)
		ft_printf("Usage: ./RTv1 [file.xml]\n");
	our_exit(env, EXIT_FAILURE);
}

void	freetab(char **tab)
{
	int		c;

	c = 0;
	while (tab[c])
	{
		free(tab[c]);
		tab[c] = NULL;
		++c;
	}
	free(tab);
	tab = NULL;
}

t_vec	deg(t_vec rot)
{
	t_vec	res;

	res.x = deg2rad((int)rot.x);
	res.y = deg2rad((int)rot.y);
	res.z = deg2rad((int)rot.z);
	return (res);
}
