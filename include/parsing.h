/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

/* parse_error.c */
void		exit_error(char *msg, t_scene *scene);
int			is_valid_ext(char *filename);

/* parse_utils.c */
double		parse_double(char *str, t_scene *scene);
t_color3	parse_color(char *str, t_scene *scene);
t_vec3		parse_vec3(char *str, t_scene *scene);
t_vec3		parse_normal(char *str, t_scene *scene);
int			count_fields(char **fields);

/* parse_scene.c */
void		parse_ambient(char **fields, t_scene *scene);
void		parse_camera(char **fields, t_scene *scene);
void		parse_light(char **fields, t_scene *scene);
void		replace_tabs(char *line);
void		dispatch_line(char *line, t_scene *scene);

/* parse_objects.c */
void		parse_sphere(char **fields, t_scene *scene);
void		parse_plane(char **fields, t_scene *scene);
void		parse_cylinder(char **fields, t_scene *scene);
void		add_object(t_scene *scene, t_object *obj);
# ifdef BONUS

void		add_light(t_scene *scene, t_light *light);
void		parse_cone(char **fields, t_scene *scene);
# endif

/* parse_file.c */
void		parse_file(char *filename, t_scene *scene);
void		validate_scene(t_scene *scene);

/* validate.c */
int			validate_range_d(double val, double min, double max);
int			validate_range_i(int val, int min, int max);
int			is_valid_number(char *str);
void		free_split(char **split);

#endif
