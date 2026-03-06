/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color3	compute_specular(t_light *light, t_hit hit, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	spec_angle;
	double	spec;

	light_dir = vec3_normalize(vec3_sub(light->pos, hit.point));
	reflect_dir = vec3_sub(vec3_mul(hit.normal,
				2.0 * vec3_dot(hit.normal, light_dir)), light_dir);
	spec_angle = vec3_dot(reflect_dir, view_dir);
	if (spec_angle < 0.0)
		spec_angle = 0.0;
	spec = pow(spec_angle, 32.0) * light->brightness;
	return (color_mul(color_new(1.0, 1.0, 1.0), spec));
}
