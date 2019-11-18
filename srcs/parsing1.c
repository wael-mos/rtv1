/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:25:18 by wael-mos          #+#    #+#             */
/*   Updated: 2019/11/18 12:03:59 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_cam(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	if (node->properties)
	{
		if (ft_strequ((char *)node->properties->name, "fov"))
		{
			value = xmlNodeListGetString(node->doc,
				node->properties->children, 1);
			env->cam.fov = ft_atoi((char *)value);
			xmlFree(value);
		}
	}
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			env->cam.pos = parse_pos(cur);
		if (ft_strequ((char *)cur->name, "rot"))
			env->cam.rot = deg(parse_pos(cur));
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_windows_attr(xmlNode *cur, t_env *env)
{
	xmlAttr	*attr;
	xmlChar	*value;

	attr = NULL;
	value = NULL;
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (ft_strequ((char *)attr->name, "x"))
			env->win_x = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "y"))
			env->win_y = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
}

void		parse_windows(xmlNode *node, t_env *env)
{
	xmlNode *cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "size"))
			parse_windows_attr(cur, env);
		cur = cur->next;
	}
	xmlFree(cur);
}

static void	split_parsing(xmlNode *begin, t_env *env)
{
	xmlNode *cur_node;

	if (!begin)
		return ;
	cur_node = begin;
	while (cur_node)
	{
		if (cur_node->type == XML_ELEMENT_NODE)
		{
			if (ft_strequ((char *)cur_node->name, "windows"))
				parse_windows(cur_node, env);
			else if (ft_strequ((char *)cur_node->name, "camera"))
				parse_cam(cur_node, env);
			else if (ft_strequ((char *)cur_node->name, "lights"))
				parse_lights(cur_node, env);
			else if (ft_strequ((char *)cur_node->name, "objects"))
				parse_objects(cur_node, env);
		}
		cur_node = cur_node->next;
	}
	xmlFree(cur_node);
}

int			parsing(char **av, t_env *env)
{
	xmlDoc	*document;
	xmlNode	*root;

	if (!(document = xmlReadFile(av[1], NULL, 0)))
		errormsg(env, 1);
	root = xmlDocGetRootElement(document);
	split_parsing(root->children, env);
	xmlFreeDoc(document);
	xmlCleanupParser();
	env->win_x = env->win_x < 0 ? -1 * env->win_x : env->win_x;
	env->win_y = env->win_y < 0 ? -1 * env->win_y : env->win_y;
	env->win_x = env->win_x == 0 ? 1080 : env->win_x;
	env->win_y = env->win_y == 0 ? 720 : env->win_y;
	return (0);
}
