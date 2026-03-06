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

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nusage: ./miniRT <scene.rt>\n", 2);
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
