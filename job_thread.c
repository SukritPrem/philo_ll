/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:13:24 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/19 12:51:53 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu %d is eating\n", timestamp() - philo->first_eat, \
			philo->philo_num);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->update_time);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->update_time);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->update_meal);
	philo->meal++;
	pthread_mutex_unlock(philo->update_meal);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu %d is sleeping\n", timestamp() - philo->first_eat, \
			philo->philo_num);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu %d is thinking\n", timestamp() - philo->first_eat, \
				philo->philo_num);
	pthread_mutex_unlock(philo->print);
}

void	*job_thread(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->all_philo == 1)
		ft_usleep(philo->time_to_eat * 2);
	if (philo->philo_num % 2 == 0)
		ft_usleep(2);
	while (1)
	{
		if (check_die(philo) == TRUE)
			break ;
		if (get_fork(philo) == FALSE)
		{
			break ;
		}
		eat(philo);
		if (check_die(philo) == TRUE)
			break ;
		philo_sleep(philo);
		if (check_die(philo) == TRUE)
			break ;
		think(philo);
	}
	return (0);
}

void	philo_get_fork_right(t_board *board)
{
	int	i;

	i = 0;
	if (board->all_philo == 1)
		return ;
	while (i < board->all_philo)
	{
		board->philo[i].right_fork = &board->philo[i + 1].left_fork;
		if (i == board->all_philo - 1)
		{
			board->philo[i].right_fork = &board->philo[board->all_philo
				- board->all_philo].left_fork;
			break ;
		}
		i++;
	}
}
