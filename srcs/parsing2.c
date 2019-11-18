/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:45:02 by evogel            #+#    #+#             */
/*   Updated: 2019/11/18 13:37:00 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			read_type(char *word)
{
	if (ft_strequ(word, "Plane") || ft_strequ(word, "plane"))
		return (0);
	if (ft_strequ(word, "Sphere") || ft_strequ(word, "sphere"))
		return (1);
	if (ft_strequ(word, "Cylindre") || ft_strequ(word, "cylindre"))
		return (2);
	if (ft_strequ(word, "Cylinder") || ft_strequ(word, "cylinder"))
		return (2);
	if (ft_strequ(word, "Cone") || ft_strequ(word, "cone"))
		return (3);
	return (4);
}

void		parse_objects(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	size_t	count;

	if (!node || !node->children)
		return ;
	env->num_obj = xmlChildElementCount(node);
	env->objs = (t_obj *)ft_memalloc(env->num_obj * sizeof(t_obj));
	if (env->objs == NULL)
		errormsg(env, 2);
	cur = node->children;
	count = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE)
			parse_anobj(cur, &env->objs[count++]);
		cur = cur->next;
	}
	xmlFree(cur);
}

static void	parse_alight(xmlNode *node, t_light *light)
{
	xmlNode	*cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			light->pos = parse_pos(cur);
		else if (ft_strequ((char *)cur->name, "col"))
			light->col = parse_col(cur);
		cur = cur->next;
	}
	xmlFree(cur);
}

static void	parse_lights_data(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	size_t	count;

	cur = node->children;
	count = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE)
			parse_alight(cur, &env->lights[count++]);
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_lights(xmlNode *node, t_env *env)
{
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	value = NULL;
	if (node->properties)
	{
		if (ft_strequ((char *)node->properties->name, "ambient"))
		{
			value = xmlNodeListGetString(node->doc,
				node->properties->children, 1);
			env->ambient = (float)ft_atoi((char *)value) / 100;
			env->ambient = env->ambient < 0 ? 0 : env->ambient;
			xmlFree(value);
		}
	}
	env->num_light = xmlChildElementCount(node);
	env->lights = (t_light *)ft_memalloc(env->num_light * sizeof(t_light));
	if (env->lights == NULL)
		errormsg(env, 2);
	parse_lights_data(node, env);
}
