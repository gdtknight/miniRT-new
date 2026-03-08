/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*get_light_by_idx(t_light *lights, int idx)
{
	int	i;

	if (idx < 0)
		return (NULL);
	i = 0;
	while (lights && i < idx)
	{
		lights = lights->next;
		i++;
	}
	return (lights);
}

const char	*get_obj_type_str(t_object *obj)
{
	if (obj->type == OBJ_PLANE)
		return ("plane");
	else if (obj->type == OBJ_CYLINDER)
		return ("cylinder");
	else if (obj->type == OBJ_CONE)
		return ("cone");
	return ("sphere");
}

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
