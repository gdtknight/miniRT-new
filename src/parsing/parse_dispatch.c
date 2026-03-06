/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
