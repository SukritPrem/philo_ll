/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:22:22 by spipitku          #+#    #+#             */
/*   Updated: 2023/12/15 17:22:28 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	found_9_to_13(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (i);
}

int	check_plus_or_neg(int *sum, int i, const char *str)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sum = *sum * (-1);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;
	int	sum_ans;

	sum_ans = 0;
	sum = 1;
	i = found_9_to_13(str);
	i = check_plus_or_neg(&sum, i, str);
	while (str[i] >= '0' && str[i] <= '9')
		sum_ans = sum_ans * 10 + (str[i++] - '0');
	return (sum_ans * sum);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && '9' >= c)
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	num_size;

	num_size = 0;
	while (*(s + num_size) != '\0')
		num_size++;
	return (num_size);
}
