/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:21:42 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/15 17:22:13 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds)
{
	size_t	now;
	size_t	start;

	now = timestamp();
	start = timestamp();
	while (now - start < milliseconds)
	{
		usleep(1);
		now = timestamp();
	}
}

size_t	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
