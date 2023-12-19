/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_thread_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:15:11 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/19 12:55:52 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (check_die(philo) == TRUE)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->print);
		return (FALSE);
	}
	prin_and_lock(philo, FORK_LEFT);
	if (check_right_fork(philo) == TRUE)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->right_fork);
	if (check_die(philo) == TRUE)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	prin_and_lock(philo, FORK_RIGHT);
	return (TRUE);
}

int	check_die(t_philo *philo)
{
	pthread_mutex_lock(philo->update_meal);
	if (philo->meal == philo->meal_must_eat)
	{
		pthread_mutex_unlock(philo->update_meal);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->update_meal);
	pthread_mutex_lock(philo->check_die);
	if (*(philo->status_eat))
	{
		pthread_mutex_unlock(philo->check_die);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->check_die);
	return (FALSE);
}

int	check_right_fork(t_philo *philo)
{
	if (philo->right_fork == NULL)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (TRUE);
	}
	return (FALSE);
}

void	prin_and_lock(t_philo *philo, int option)
{
	if (option == FORK_LEFT)
	{
		pthread_mutex_lock(philo->print);
		if (philo->all_philo != 1)
		{
			printf("%zu %d has taken a fork\n", \
						timestamp() - philo->first_eat, philo->philo_num);
		}
		pthread_mutex_unlock(philo->print);
	}
	else if (option == FORK_RIGHT)
	{
		pthread_mutex_lock(philo->print);
		printf("%zu %d has taken a fork\n", \
				timestamp() - philo->first_eat, philo->philo_num);
		pthread_mutex_unlock(philo->print);
	}
}
