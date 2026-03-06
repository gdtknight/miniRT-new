/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "minirt.h"

void	free_scene(t_scene *scene)
{
	if (scene->objects)
		free_objects(scene->objects);
	scene->objects = NULL;
	if (scene->lights)
		free_lights(scene->lights);
	scene->lights = NULL;
	if (scene->mlx)
		destroy_window(scene);
}

#endif
