/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:02:13 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/28 20:03:57 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (long)(time.tv_usec / 1000));
}

void	time_skip(long time)
{
	long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(200);
	}
}

void	print_status(char *msg, t_philo *philo, long current)
{
	pthread_mutex_lock(&philo->table->print_m);
	if (philo->table->all_eat == NO && philo->table->anyone_dead == NO)
		printf(msg, current, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_m);
}

int	all_must_ate(t_table *table)
{
	int	i;
	int	ate;

	i = -1;
	ate = 0;
	if (table->philomusteat != EMPTY)
	{
		while (++i < table->numofphilo)
		{
			if (table->philos[i].eat_count >= table->philomusteat)
				ate++;
		}
		if (ate == table->numofphilo)
		{
			table->all_eat = YES;
			return (1);
		}
		return (0);
	}
	return (0);
}
