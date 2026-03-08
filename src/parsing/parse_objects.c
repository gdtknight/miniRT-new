/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/09 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_vec3	init_local_up(t_vec3 axis)
{
	t_vec3	world_up;

	world_up = vec3_new(0.0, 1.0, 0.0);
	if (fabs(vec3_dot(axis, world_up)) > 0.999)
		world_up = vec3_new(0.0, 0.0, 1.0);
	return (vec3_normalize(vec3_cross(axis,
				vec3_cross(world_up, axis))));
}

void	add_object(t_scene *scene, t_object *obj)
{
	t_object	*current;

	scene->obj_count++;
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

	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_SPHERE;
	obj->next = NULL;
	obj->checker = parse_checker_opt(fields, 4, scene);
	obj->data.sphere.center = parse_vec3(fields[1], scene);
	obj->data.sphere.radius = parse_double(fields[2], scene) / 2.0;
	if (obj->data.sphere.radius <= 0)
		exit_error("sphere: invalid diameter", scene);
	obj->data.sphere.color = parse_color(fields[3], scene);
	obj->local_up = vec3_new(0, 1, 0);
	add_object(scene, obj);
}

void	parse_plane(char **fields, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_PLANE;
	obj->next = NULL;
	obj->checker = parse_checker_opt(fields, 4, scene);
	obj->data.plane.point = parse_vec3(fields[1], scene);
	obj->data.plane.normal = parse_normal(fields[2], scene);
	obj->data.plane.color = parse_color(fields[3], scene);
	obj->local_up = init_local_up(obj->data.plane.normal);
	add_object(scene, obj);
}

void	parse_cylinder(char **fields, t_scene *scene)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_CYLINDER;
	obj->next = NULL;
	obj->checker = parse_checker_opt(fields, 6, scene);
	obj->data.cylinder.center = parse_vec3(fields[1], scene);
	obj->data.cylinder.axis = parse_normal(fields[2], scene);
	obj->data.cylinder.radius = parse_double(fields[3], scene) / 2.0;
	if (obj->data.cylinder.radius <= 0)
		exit_error("cylinder: invalid diameter", scene);
	obj->data.cylinder.height = parse_double(fields[4], scene);
	if (obj->data.cylinder.height <= 0)
		exit_error("cylinder: invalid height", scene);
	obj->data.cylinder.color = parse_color(fields[5], scene);
	obj->local_up = init_local_up(obj->data.cylinder.axis);
	add_object(scene, obj);
}
