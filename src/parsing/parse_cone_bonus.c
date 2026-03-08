/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_cone(char **fields, t_scene *scene)
{
	t_object	*obj;
	double		radius;
	double		height;

	obj = malloc(sizeof(t_object));
	if (!obj)
		exit_error("malloc failed", scene);
	obj->type = OBJ_CONE;
	obj->next = NULL;
	obj->checker = parse_checker_opt(fields, 6, scene);
	obj->data.cone.apex = parse_vec3(fields[1], scene);
	obj->data.cone.axis = parse_normal(fields[2], scene);
	radius = parse_double(fields[3], scene) / 2.0;
	if (radius <= 0)
		exit_error("cone: invalid diameter", scene);
	height = parse_double(fields[4], scene);
	if (height <= 0)
		exit_error("cone: invalid height", scene);
	obj->data.cone.radius = radius;
	obj->data.cone.height = height;
	obj->data.cone.cos_theta = height / sqrt(height * height
			+ radius * radius);
	obj->data.cone.color = parse_color(fields[5], scene);
	obj->local_up = init_local_up(obj->data.cone.axis);
	add_object(scene, obj);
}
