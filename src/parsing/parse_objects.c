/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_object(t_scene *scene, t_object *obj)
{
	t_object	*current;

	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	current = scene->objects;
	while (current->next)
		current = current->next;
	current->next = obj;
}

void	parse_sphere(char **fields, t_scene *scene)
{
	t_object	*obj;

	if (count_fields(fields) != 4)
		exit_error("sphere: wrong number of fields", scene);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_SPHERE;
	obj->data.sphere.center = parse_vec3(fields[1], scene);
	obj->data.sphere.radius = parse_double(fields[2], scene) / 2.0;
	if (obj->data.sphere.radius <= 0)
		exit_error("sphere: invalid diameter", scene);
	obj->data.sphere.color = parse_color(fields[3], scene);
	obj->next = NULL;
	add_object(scene, obj);
}

void	parse_plane(char **fields, t_scene *scene)
{
	t_object	*obj;

	if (count_fields(fields) != 4)
		exit_error("plane: wrong number of fields", scene);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_PLANE;
	obj->data.plane.point = parse_vec3(fields[1], scene);
	obj->data.plane.normal = parse_normal(fields[2], scene);
	obj->data.plane.color = parse_color(fields[3], scene);
	obj->next = NULL;
	add_object(scene, obj);
}

void	parse_cylinder(char **fields, t_scene *scene)
{
	t_object	*obj;

	if (count_fields(fields) != 6)
		exit_error("cylinder: wrong number of fields", scene);
	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_CYLINDER;
	obj->data.cylinder.center = parse_vec3(fields[1], scene);
	obj->data.cylinder.axis = parse_normal(fields[2], scene);
	obj->data.cylinder.radius = parse_double(fields[3], scene) / 2.0;
	if (obj->data.cylinder.radius <= 0)
		exit_error("cylinder: invalid diameter", scene);
	obj->data.cylinder.height = parse_double(fields[4], scene);
	if (obj->data.cylinder.height <= 0)
		exit_error("cylinder: invalid height", scene);
	obj->data.cylinder.color = parse_color(fields[5], scene);
	obj->next = NULL;
	add_object(scene, obj);
}
