/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->mode = MODE_CAMERA;
	scene->selected_idx = 0;
	scene->obj_count = 0;
	scene->selected_light_idx = 0;
	scene->light_count = 0;
}

t_object	*get_object_by_idx(t_object *objs, int idx)
{
	int	i;

	if (idx < 0)
		return (NULL);
	i = 0;
	while (objs && i < idx)
	{
		objs = objs->next;
		i++;
	}
	return (objs);
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
