/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/07 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_hit	find_closest_hit(t_object *objs, t_ray ray)
{
	t_hit		closest;
	t_hit		hit;
	t_object	*current;

	closest.hit = 0;
	closest.t = 1e30;
	current = objs;
	while (current)
	{
		hit = intersect_object(current, ray);
		if (hit.hit && hit.t > EPSILON && hit.t < closest.t)
			closest = hit;
		current = current->next;
	}
	return (closest);
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color3	color;

	init_camera(&scene->camera);
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = generate_ray(&scene->camera, x, y);
			color = trace_ray(scene, ray);
			img_pixel_put(&scene->img, x, y, color_to_int(color));
			x++;
		}
		y++;
	}
	display_image(scene);
}
