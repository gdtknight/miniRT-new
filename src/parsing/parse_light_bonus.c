/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "parsing.h"

void	parse_light(char **fields, t_scene *scene)
{
	t_light		*light;

	if (count_fields(fields) != 4)
		exit_error("light: wrong number of fields", scene);
	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("malloc failed", scene);
	light->pos = parse_vec3(fields[1], scene);
	light->brightness = parse_double(fields[2], scene);
	if (!validate_range_d(light->brightness, 0.0, 1.0))
		exit_error("light: brightness out of range [0,1]", scene);
	light->color = parse_color(fields[3], scene);
	light->next = NULL;
	add_light(scene, light);
	scene->has_light = 1;
}

static void	dispatch_object(char **fields, t_scene *scene)
{
	if (!ft_strncmp(fields[0], "sp", 3))
		parse_sphere(fields, scene);
	else if (!ft_strncmp(fields[0], "pl", 3))
		parse_plane(fields, scene);
	else if (!ft_strncmp(fields[0], "cy", 3))
		parse_cylinder(fields, scene);
	else if (!ft_strncmp(fields[0], "co", 3))
		parse_cone(fields, scene);
	else
		exit_error("unknown element type", scene);
}

void	dispatch_line(char *line, t_scene *scene)
{
	char	**fields;

	replace_tabs(line);
	fields = ft_split(line, ' ');
	if (!fields || !fields[0])
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
	else
		dispatch_object(fields, scene);
	free_split(fields);
}

#endif
