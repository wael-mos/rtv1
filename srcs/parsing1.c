/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:25:18 by wael-mos          #+#    #+#             */
/*   Updated: 2019/11/10 11:46:09 by wael-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// Source : http://www.xmlsoft.org/examples/#Parsing

// TOOLS

t_vec		deg(t_vec rot)
{
	t_vec	res;
	
	res.x = deg2rad((int)rot.x);
	res.y = deg2rad((int)rot.y);
	res.z = deg2rad((int)rot.z);
	return (res);
}

t_col		parse_col(xmlNode *cur)
{
	xmlAttr *attr;
	xmlChar *value;
	t_col	col;
	
	if (!cur || !cur->properties)
		return (color(0.0, 0.0, 0.0));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (!ft_strcmp((char *)attr->name, "r"))
			col.r = (float)ft_atoi((char *)value) / 100;
		else if (!ft_strcmp((char *)attr->name, "g"))
			col.g = (float)ft_atoi((char *)value) / 100;
		else if (!ft_strcmp((char *)attr->name, "b"))
			col.b = (float)ft_atoi((char *)value) / 100;
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (col);
}

t_vec		parse_rot(xmlNode *cur)
{
	xmlAttr *attr;
	xmlChar *value;
	t_vec	rot;
	
	if (!cur || !cur->properties)
		return (vec(0.0, 0.0, 0.0));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (!ft_strcmp((char *)attr->name, "x"))
			rot.x = ft_atoi((char *)value);
		else if (!ft_strcmp((char *)attr->name, "y"))
			rot.y = ft_atoi((char *)value);
		else if (!ft_strcmp((char *)attr->name, "z"))
			rot.z = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (rot);
}

t_vec		parse_pos(xmlNode *cur)
{
	xmlAttr *attr;
	xmlChar *value;
	t_vec	pos;
	
	if (!cur || !cur->properties)
		return (vec(0.0, 0.0, 0.0));
	attr = cur->properties;
	while (attr)
	{
		value = xmlNodeListGetString(cur->doc, attr->children, 1);
		if (!ft_strcmp((char *)attr->name, "x"))
			pos.x = ft_atoi((char *)value);
		else if (!ft_strcmp((char *)attr->name, "y"))
			pos.y = ft_atoi((char *)value);
		else if (!ft_strcmp((char *)attr->name, "z"))
			pos.z = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (pos);
}

static int	read_type(char *word)
{
	if (!ft_strcmp(word, "Plane") || !ft_strcmp(word, "plane"))
		return (0);
	if (!ft_strcmp(word, "Sphere") || !ft_strcmp(word, "sphere"))
		return (1);
	if (!ft_strcmp(word, "Cylindre") || !ft_strcmp(word, "cylindre"))
		return (2);
	if (!ft_strcmp(word, "Cone") || !ft_strcmp(word, "cone"))
		return (3);
	return (4);
}

//

void		parse_anobj(xmlNode *node, t_obj *obj)
{
	xmlNode	*cur;
	xmlAttr	*attr;
	xmlChar	*value;
	
	if (!node || !node->children)
		return ;
	cur = node->children;
	obj->type = read_type((char *)node->name);
	attr = node->properties;
	while (attr)
	{
		value = xmlNodeListGetString(node->doc, attr->children, 1);
		if (!ft_strcmp((char *)attr->name, "radius"))
			obj->rad = (obj->type == 3) ? deg2rad(ft_atoi((char *)value)) :\
				ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	while (cur)
	{
		if (!ft_strcmp((char *)cur->name, "pos"))
			obj->pos = parse_pos(cur);
		else if (!ft_strcmp((char *)cur->name, "rot"))
			obj->rot = get_axe(parse_pos(cur));
		else if (!ft_strcmp((char *)cur->name, "col"))
			obj->col = parse_col(cur);
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_alight(xmlNode *node, t_light *light)
{
	xmlNode	*cur;

	if (!node || !node->children)
		return ;
	cur = node->children;
	while (cur)
	{
		if (!ft_strcmp((char *)cur->name, "pos"))
			light->pos = parse_pos(cur);
		else if (!ft_strcmp((char *)cur->name, "col"))
			light->col = parse_col(cur);
		cur = cur->next;
	}
	xmlFree(cur);
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

void		parse_lights(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	xmlChar	*value;
	size_t	count;

	if (!node || !node->children)
		return ;
	value = NULL;
	if (node->properties)
	{
		if (!ft_strcmp((char *)node->properties->name, "ambient"))
		{
			value = xmlNodeListGetString(node->doc, node->properties->children, 1);
			env->ambient = ft_atoi((char *)value);
			env->ambient /= 100;
			xmlFree(value);
		}
	}
	env->num_light = xmlChildElementCount(node);
	env->lights = (t_light *)ft_memalloc(env->num_light * sizeof(t_light));
	if (env->lights == NULL)
		errormsg(env, 2);
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

void		parse_cam(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	if (node->properties)
	{
		if (!ft_strcmp((char *)node->properties->name, "fov"))
		{
			value = xmlNodeListGetString(node->doc, node->properties->children, 1);
			env->cam.fov = ft_atoi((char *)value);
			xmlFree(value);
		}
	}
	cur = node->children;
	while (cur)
	{
		if (!ft_strcmp((char *)cur->name, "pos"))
			env->cam.pos = parse_pos(cur);
		if (!ft_strcmp((char *)cur->name, "rot"))
			env->cam.rot = deg(parse_pos(cur));
		cur = cur->next;
	}
	xmlFree(cur);
}

void		parse_windows(xmlNode *node, t_env *env)
{
	xmlNode *cur;
	xmlAttr	*attr;
	xmlChar	*value;

	if (!node || !node->children)
		return ;
	attr = NULL;
	value = NULL;
	cur = node->children;
	while (cur)
	{
		if (!ft_strcmp((char *)cur->name, "size"))
		{
			attr = cur->properties;
			while (attr)
			{
				value = xmlNodeListGetString(cur->doc, attr->children, 1);
				if (!ft_strcmp((char *)attr->name, "x"))
					env->win_x = ft_atoi((char *)value);
				else if (!ft_strcmp((char *)attr->name, "y"))
					env->win_y = ft_atoi((char *)value);
				xmlFree(value);
				attr = attr->next;
			}
			xmlFree(attr);
		}
		cur = cur->next;
	}
	xmlFree(cur);
}

static void split_parsing(xmlNode *begin, t_env *env)
{  
	xmlNode *cur_node;

	if (!begin)
		return ;
	cur_node = begin;
	while (cur_node)
	{
		if (cur_node->type == XML_ELEMENT_NODE)
		{
			if (!ft_strcmp((char *)cur_node->name, "windows"))
				parse_windows(cur_node, env);
			else if (!ft_strcmp((char *)cur_node->name, "camera"))
				parse_cam(cur_node, env);
			else if (!ft_strcmp((char *)cur_node->name, "lights"))
				parse_lights(cur_node, env);
			else if (!ft_strcmp((char *)cur_node->name, "objects"))
				parse_objects(cur_node, env);
		}
		cur_node = cur_node->next;
	}
	xmlFree(cur_node);
}

int			parsing(char **av, t_env *env)
{
	xmlDoc         *document;
	xmlNode        *root;

	if (!(document = xmlReadFile(av[1], NULL, 0)))
		errormsg(env, 1);
	root = xmlDocGetRootElement(document);
	split_parsing(root->children, env);
	xmlFreeDoc(document);
	xmlCleanupParser();
	env->win_x = (!env->win_x) ? 1080 : env->win_x;
	env->win_y = (!env->win_y) ? 720 : env->win_y;
	return (0);
}
