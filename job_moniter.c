/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_moniter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:08:06 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/19 12:49:59 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_die(t_board *board)
{
	int	i;

	i = 0;
	while (i < board->all_philo)
	{
		pthread_mutex_lock(&board->update_time);
		if (timestamp() - board->philo[i].last_meal >= board->time_to_die
			&& board->philo[i].last_meal != 0)
		{
			pthread_mutex_unlock(&board->update_time);
			pthread_mutex_lock(&board->check_die);
			board->status_eat = 1;
			pthread_mutex_unlock(&board->check_die);
			pthread_mutex_lock(&board->print);
			printf("%zu %d died\n", \
			timestamp() - board->philo[i].first_eat, \
			board->philo[i].philo_num);
			pthread_mutex_unlock(&board->print);
			return (1);
		}
		else
			pthread_mutex_unlock(&board->update_time);
		i++;
	}
	return (0);
}

int	check_full_eat(t_board *board)
{
	int	i;
	int	philo_eat_finish;

	i = 0;
	philo_eat_finish = 0;
	while (i < board->all_philo)
	{
		pthread_mutex_lock(&board->update_meal);
		if (board->philo[i].meal == board->meal_must_eat)
		{
			philo_eat_finish++;
			pthread_mutex_unlock(&board->update_meal);
		}
		else
			pthread_mutex_unlock(&board->update_meal);
		i++;
	}
	if (philo_eat_finish == board->all_philo)
	{
		board->status_eat = 1;
		return (1);
	}
	return (0);
}

void	*job_monitor(void *var)
{
	t_board	*board;
	int		i;

	board = (t_board *)var;
	i = 0;
	while (1)
	{
		if (check_philo_die(board) || check_full_eat(board))
			break ;
	}
	return (0);
}
