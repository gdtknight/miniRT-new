/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color3	color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_color3	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color3	color;
}	t_cylinder;

typedef struct s_cone
{
	t_point3	apex;
	t_vec3		axis;
	double		cos_theta;
	double		radius;
	double		height;
	t_color3	color;
}	t_cone;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}	t_obj_type;

typedef union u_obj_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
}	t_obj_data;

typedef struct s_object
{
	t_obj_type		type;
	t_obj_data		data;
	int				checker;
	t_vec3			local_up;
	struct s_object	*next;
}	t_object;

#endif
