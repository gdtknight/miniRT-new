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
	t_vec3		view_dir;
	int			hit;
	int			obj_idx;
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

/* src/objects/plane.c */
t_hit		intersect_plane(t_plane *pl, t_ray ray);

/* src/objects/cylinder.c */
t_hit		intersect_cylinder(t_cylinder *cy, t_ray ray);
t_hit		intersect_cy_body(t_cylinder *cy, t_ray ray);

/* src/objects/cylinder_caps.c */
t_hit		intersect_cy_caps(t_cylinder *cy, t_ray ray);
t_hit		check_cy_cap(t_cylinder *cy, t_ray ray,
				t_point3 cap_center, t_vec3 cap_normal);

/* src/render/color.c */
t_color3	color_new(double r, double g, double b);
t_color3	color_add(t_color3 a, t_color3 b);
t_color3	color_mul(t_color3 c, double t);
t_color3	color_hadamard(t_color3 a, t_color3 b);
t_color3	color_clamp(t_color3 c);

/* src/render/light.c */
t_color3	compute_lighting(t_scene *scene, t_hit hit);
t_color3	compute_diffuse(t_light *light, t_hit hit);
int			is_in_shadow(t_scene *scene, t_hit hit);

/* src/render/specular_bonus.c */
t_color3	compute_specular(t_light *light, t_hit hit, t_vec3 view_dir);
/* src/render/checker_bonus.c */
t_color3	apply_checkerboard(t_hit hit, t_color3 base_color);
/* src/render/light_bonus.c */
t_color3	compute_lighting_bonus(t_scene *scene, t_hit hit);
/* src/objects/cone_bonus.c */
t_hit		intersect_cone(t_cone *cone, t_ray ray);

#endif
