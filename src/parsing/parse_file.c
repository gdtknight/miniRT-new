/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	strip_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t'
			&& *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

void	validate_scene(t_scene *scene)
{
	if (!scene->has_ambient)
		exit_error("missing ambient light (A)", scene);
	if (!scene->has_camera)
		exit_error("missing camera (C)", scene);
	if (!scene->has_light)
		exit_error("missing light (L)", scene);
}

void	parse_file(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!is_valid_ext(filename))
		exit_error("invalid file extension (expected .rt)", scene);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("cannot open file", scene);
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		if (!is_empty_line(line))
			dispatch_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	validate_scene(scene);
}
