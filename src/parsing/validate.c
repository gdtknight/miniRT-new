/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by yoshin            #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_range_d(double val, double min, double max)
{
	return (val >= min && val <= max);
}

int	validate_range_i(int val, int min, int max)
{
	return (val >= min && val <= max);
}

int	is_valid_number(char *str)
{
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	has_digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.' && !has_dot)
			has_dot = 1;
		else if (*str >= '0' && *str <= '9')
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
