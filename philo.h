/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:27:24 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/19 14:53:52 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1

# define FORK_LEFT 0
# define FORK_RIGHT 1

typedef struct s_philo
{
	int				philo_num;
	int				meal;
	int				meal_must_eat;
	pthread_t		thread;
	int				*status_eat;
	size_t			all_philo;
	size_t			first_eat;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			*check_philo_die;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*update_time;
	pthread_mutex_t	*update_meal;
	pthread_mutex_t	*check_die;
}	t_philo;

typedef struct s_board
{
	int				all_philo;
	int				meal_must_eat;
	int				status_eat;
	pthread_t		thread;
	t_philo			*philo;
	size_t			check_philo_die;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	update_time;
	pthread_mutex_t	update_meal;
	pthread_mutex_t	check_die;
}	t_board;

//job_moniter.c
int		check_philo_die(t_board *board);
int		check_full_eat(t_board *board);
void	*job_monitor(void *var);
//job_thread.c
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);
void	*job_thread(void *var);
void	philo_get_fork_right(t_board *board);
//job_thread_1.c
void	prin_and_lock(t_philo *philo, int option);
int		get_fork(t_philo *philo);
int		check_die(t_philo *philo);
int		check_right_fork(t_philo *philo);
//init.c
void	init(t_board *board, int argc, char *argv[]);
int		init_philo(t_board *board);
//time_utils.c
void	ft_usleep(size_t milliseconds);
size_t	timestamp(void);
//main.c
int		check_all_int(int argc, char *argv[]);
//utils.c
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

#endif
