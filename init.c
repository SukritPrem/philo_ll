/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:11:29 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/15 17:39:09 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_board *board, int argc, char *argv[])
{
	if (check_all_int(argc, argv) == FALSE)
	{
		write(2, "Error input need number.\n", 25);
		exit(1);
	}
	board->time_to_die = ft_atoi(argv[2]);
	board->time_to_eat = ft_atoi(argv[3]);
	board->time_to_sleep = ft_atoi(argv[4]);
	board->all_philo = ft_atoi(argv[1]);
	board->status_eat = 0;
	if (board->all_philo > 1000)
	{
		write(2, "There are many threads.\n", 25);
		exit(1);
	}
	board->check_philo_die = 0;
	if (argc == 6)
		board->meal_must_eat = ft_atoi(argv[5]);
	else
		board->meal_must_eat = -1;
	pthread_mutex_init(&board->print, NULL);
	pthread_mutex_init(&board->update_time, NULL);
	pthread_mutex_init(&board->check_die, NULL);
	pthread_mutex_init(&board->update_meal, NULL);
}

void	setting_struct_philo(t_board *board, int i)
{
	board->philo[i].meal_must_eat = board->meal_must_eat;
	board->philo[i].philo_num = i + 1;
	board->philo[i].time_to_die = board->time_to_die;
	board->philo[i].time_to_eat = board->time_to_eat;
	board->philo[i].time_to_sleep = board->time_to_sleep;
	board->philo[i].check_philo_die = &board->check_philo_die;
	board->philo[i].update_time = &board->update_time;
	board->philo[i].print = &board->print;
	board->philo[i].update_meal = &board->update_meal;
	board->philo[i].check_die = &board->check_die;
	board->philo[i].meal = 0;
}

int	init_philo(t_board *board)
{
	int	i;

	i = 0;
	board->philo = malloc(sizeof(t_philo) * board->all_philo);
	if (!board->philo)
		return (FALSE);
	while (i < board->all_philo)
	{
		board->philo[i].all_philo = board->all_philo;
		board->philo[i].status_eat = &board->status_eat;
		board->philo[i].first_eat = timestamp();
		board->philo[i].last_meal = 0;
		if (board->all_philo == 1)
			board->philo[i].last_meal = timestamp();
		setting_struct_philo(board, i);
		pthread_mutex_init(&board->philo[i].left_fork, NULL);
		i++;
	}
	return (TRUE);
}
