/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "render.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!is_valid_ext(argv[1]))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (!check_args(argc, argv))
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene.rt>\n", 2);
		return (1);
	}
	init_scene(&scene);
	parse_file(argv[1], &scene);
	init_window(&scene);
	render_scene(&scene);
	setup_hooks(&scene);
	mlx_loop(scene.mlx);
	return (0);
}
