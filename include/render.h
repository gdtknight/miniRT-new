/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		dir;
}	t_ray;

typedef struct s_hit
{
	double		t;
	t_point3	point;
	t_vec3		normal;
	t_color3	color;
	int			hit;
}	t_hit;

/* src/scene/camera.c */
void		init_camera(t_camera *cam);

/* src/render/ray.c */
t_ray		ray_new(t_point3 origin, t_vec3 dir);
t_point3	ray_at(t_ray ray, double t);
t_ray		generate_ray(t_camera *cam, int px, int py);

/* src/render/render.c */
void		render_scene(t_scene *scene);
t_color3	trace_ray(t_scene *scene, t_ray ray);
t_hit		find_closest_hit(t_object *objs, t_ray ray);
t_hit		intersect_object(t_object *obj, t_ray ray);

/* src/objects/sphere.c */
t_hit		intersect_sphere(t_sphere *sp, t_ray ray);

#endif
