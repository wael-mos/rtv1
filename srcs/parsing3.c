/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evogel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:02:09 by evogel            #+#    #+#             */
/*   Updated: 2019/11/18 13:38:50 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
		if (ft_strequ((char *)attr->name, "r"))
			col.r = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "g"))
			col.g = (float)ft_atoi((char *)value) / 100;
		else if (ft_strequ((char *)attr->name, "b"))
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
		if (ft_strequ((char *)attr->name, "x"))
			rot.x = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "y"))
			rot.y = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "z"))
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
		if (ft_strequ((char *)attr->name, "x"))
			pos.x = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "y"))
			pos.y = ft_atoi((char *)value);
		else if (ft_strequ((char *)attr->name, "z"))
			pos.z = ft_atoi((char *)value);
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	return (pos);
}

static void	parse_anobj_data(xmlNode *cur, t_obj *obj)
{
	while (cur)
	{
		if (ft_strequ((char *)cur->name, "pos"))
			obj->pos = parse_pos(cur);
		else if (ft_strequ((char *)cur->name, "rot"))
			obj->rot = get_axe(parse_pos(cur));
		else if (ft_strequ((char *)cur->name, "col"))
			obj->col = parse_col(cur);
		cur = cur->next;
	}
	xmlFree(cur);
}

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
		if (ft_strequ((char *)attr->name, "radius"))
			obj->rad = ft_atoi((char *)value);
		if (ft_strequ((char *)attr->name, "angle"))
			obj->rad = deg2rad(ft_atoi((char *)value));
		xmlFree(value);
		attr = attr->next;
	}
	xmlFree(attr);
	parse_anobj_data(cur, obj);
}
