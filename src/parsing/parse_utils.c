/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_fields(char **fields)
{
	int	count;

	if (!fields)
		return (0);
	count = 0;
	while (fields[count])
		count++;
	return (count);
}

double	parse_double(char *str, t_scene *scene)
{
	if (!is_valid_number(str))
		exit_error("invalid number format", scene);
	return (ft_atof(str));
}

t_color3	parse_color(char *str, t_scene *scene)
{
	char	**tokens;
	int		r;
	int		g;
	int		b;

	tokens = ft_split(str, ',');
	if (!tokens || count_fields(tokens) != 3)
	{
		free_split(tokens);
		exit_error("invalid color format", scene);
	}
	r = (int)parse_double(tokens[0], scene);
	g = (int)parse_double(tokens[1], scene);
	b = (int)parse_double(tokens[2], scene);
	free_split(tokens);
	if (!validate_range_i(r, 0, 255)
		|| !validate_range_i(g, 0, 255)
		|| !validate_range_i(b, 0, 255))
		exit_error("color out of range [0,255]", scene);
	return (vec3_new(r / 255.0, g / 255.0, b / 255.0));
}

t_vec3	parse_vec3(char *str, t_scene *scene)
{
	char	**tokens;
	t_vec3	result;

	tokens = ft_split(str, ',');
	if (!tokens || count_fields(tokens) != 3)
	{
		free_split(tokens);
		exit_error("invalid vector format", scene);
	}
	result.x = parse_double(tokens[0], scene);
	result.y = parse_double(tokens[1], scene);
	result.z = parse_double(tokens[2], scene);
	free_split(tokens);
	return (result);
}

t_vec3	parse_normal(char *str, t_scene *scene)
{
	t_vec3	v;

	v = parse_vec3(str, scene);
	if (!validate_range_d(v.x, -1.0, 1.0)
		|| !validate_range_d(v.y, -1.0, 1.0)
		|| !validate_range_d(v.z, -1.0, 1.0))
		exit_error("normal vector out of range [-1,1]", scene);
	if (vec3_length(v) < EPSILON)
		exit_error("normal vector cannot be zero", scene);
	return (vec3_normalize(v));
}
