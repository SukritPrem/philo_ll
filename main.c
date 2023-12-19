/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:17:06 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/19 15:08:38 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_int(int argc, char *argv[])
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < (int)ft_strlen(argv[i]))
		{
			if (!(ft_isdigit(argv[i][j])))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

void	create_thread_and_join(t_board *board)
{
	int	i;

	i = 0;
	while (i < board->all_philo)
	{
		pthread_create(&board->philo[i].thread, \
				NULL, &job_thread, &board->philo[i]);
		i++;
	}
	job_monitor(board);
	usleep(500);
	i = 0;
	while (i < board->all_philo)
		pthread_join(board->philo[i++].thread, NULL);
}

void	unlock_and_destroy(t_board *board)
{
	int	i;

	i = 0;
	while (i < board->all_philo)
		pthread_mutex_destroy(&board->philo[i++].left_fork);
	pthread_mutex_destroy(&board->print);
	pthread_mutex_destroy(&board->update_time);
	pthread_mutex_destroy(&board->check_die);
	pthread_mutex_destroy(&board->update_meal);
}

int	main(int argc, char *argv[])
{
	t_board	board;

	if (!(argc == 5 || argc == 6))
	{
		write(2, "The error in argc\n", 19);
		exit(1);
	}
	init(&board, argc, argv);
	if (init_philo(&board) == FALSE)
	{
		write(2, "The error init philo\n", 22);
		return (1);
	}
	philo_get_fork_right(&board);
	create_thread_and_join(&board);
	unlock_and_destroy(&board);
	free(board.philo);
	return (0);
}
