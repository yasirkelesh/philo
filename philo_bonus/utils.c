/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:02:13 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 17:42:28 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_kill(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->numofphilo)
	{
		waitpid(-1, &table->sem_msg, 0);
		if (table->sem_msg != 0 && table->all_eat == NO)
		{
			while (i < table->numofphilo)
			{
				kill(table->philo_index[i], SIGKILL);
				i++;
			}
			break ;
		}
	}
	sem_close(table->print_lock);
	sem_close(table->fork_lock);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (long)(time.tv_usec / 1000));
}

int	all_must_ate(t_table *table)
{
	if (table->philomusteat != EMPTY)
	{
		if (table->philo_ate >= table->philomusteat)
		{
			table->all_eat = YES;
			return (1);
		}
		return (0);
	}
	return (0);
}
