/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

void	free_objects(t_object *objs)
{
	t_object	*tmp;

	while (objs)
	{
		tmp = objs;
		objs = objs->next;
		free(tmp);
	}
}

#ifdef BONUS

void	free_lights(t_light *lights)
{
	t_light		*tmp;

	while (lights)
	{
		tmp = lights;
		lights = lights->next;
		free(tmp);
	}
}

#endif

#ifndef BONUS

void	free_scene(t_scene *scene)
{
	if (scene->objects)
		free_objects(scene->objects);
	scene->objects = NULL;
	if (scene->mlx)
		destroy_window(scene);
}

#endif
