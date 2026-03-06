/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_ambient(char **fields, t_scene *scene)
{
	if (count_fields(fields) != 3)
		exit_error("ambient: wrong number of fields", scene);
	if (scene->has_ambient)
		exit_error("ambient: duplicate declaration", scene);
	scene->ambient.ratio = parse_double(fields[1], scene);
	if (!validate_range_d(scene->ambient.ratio, 0.0, 1.0))
		exit_error("ambient: ratio out of range [0,1]", scene);
	scene->ambient.color = parse_color(fields[2], scene);
	scene->has_ambient = 1;
}

void	parse_camera(char **fields, t_scene *scene)
{
	if (count_fields(fields) != 4)
		exit_error("camera: wrong number of fields", scene);
	if (scene->has_camera)
		exit_error("camera: duplicate declaration", scene);
	scene->camera.pos = parse_vec3(fields[1], scene);
	scene->camera.dir = parse_normal(fields[2], scene);
	scene->camera.fov = parse_double(fields[3], scene);
	if (!validate_range_d(scene->camera.fov, 0.0, 180.0))
		exit_error("camera: fov out of range [0,180]", scene);
	scene->has_camera = 1;
}

void	replace_tabs(char *line)
{
	while (*line)
	{
		if (*line == '\t')
			*line = ' ';
		line++;
	}
}
