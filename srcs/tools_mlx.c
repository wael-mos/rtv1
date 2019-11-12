/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:31:37 by evogel            #+#    #+#             */
/*   Updated: 2019/11/09 18:10:31 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	our_exit(t_env *env, int status)
{
	if (env->mlx.mlx_ptr && env->mlx.img_ptr)
		mlx_destroy_image(env->mlx.mlx_ptr, env->mlx.img_ptr);
	if (env->mlx.mlx_ptr && env->mlx.win_ptr)
		mlx_destroy_window(env->mlx.mlx_ptr, env->mlx.win_ptr);
	free(env->lights);
	free(env->objs);
	exit(status);
}

int		deal_key(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	if (key == 53)
		our_exit(env, EXIT_SUCCESS);
	return (0);
}

int		deal_expose(t_env *env)
{
	mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr, \
		env->mlx.img_ptr, 0, 0);
	return (0);
}

int		deal_close(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	our_exit(env, EXIT_SUCCESS);
	return (0);
}

void	error_mlx(t_env *env)
{
	ft_printf("Error creating window with MLX\n");
	our_exit(env, EXIT_FAILURE);
}
