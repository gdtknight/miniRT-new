/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
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

#ifndef BONUS

void	parse_light(char **fields, t_scene *scene)
{
	if (count_fields(fields) != 4)
		exit_error("light: wrong number of fields", scene);
	if (scene->has_light)
		exit_error("light: duplicate declaration", scene);
	scene->light.pos = parse_vec3(fields[1], scene);
	scene->light.brightness = parse_double(fields[2], scene);
	if (!validate_range_d(scene->light.brightness, 0.0, 1.0))
		exit_error("light: brightness out of range [0,1]", scene);
	scene->light.color = parse_color(fields[3], scene);
	scene->has_light = 1;
}

#endif

void	replace_tabs(char *line)
{
	while (*line)
	{
		if (*line == '\t')
			*line = ' ';
		line++;
	}
}

#ifndef BONUS

void	dispatch_line(char *line, t_scene *scene)
{
	char	**fields;

	replace_tabs(line);
	fields = ft_split(line, ' ');
	if (!fields || !fields[0] || fields[0][0] == '#')
	{
		free_split(fields);
		return ;
	}
	if (!ft_strncmp(fields[0], "A", 2))
		parse_ambient(fields, scene);
	else if (!ft_strncmp(fields[0], "C", 2))
		parse_camera(fields, scene);
	else if (!ft_strncmp(fields[0], "L", 2))
		parse_light(fields, scene);
	else if (!ft_strncmp(fields[0], "sp", 3))
		parse_sphere(fields, scene);
	else if (!ft_strncmp(fields[0], "pl", 3))
		parse_plane(fields, scene);
	else if (!ft_strncmp(fields[0], "cy", 3))
		parse_cylinder(fields, scene);
	else
		exit_error("unknown element type", scene);
	free_split(fields);
}

#endif
