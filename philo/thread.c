/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:00:14 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/28 20:01:28 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->last_eat = get_time();
	if (philo->philo_id % 2 != 0)
		usleep(2500);
	while (philo->table->anyone_dead == NO && !all_must_ate(philo->table))
	{
		meal(philo);
		sleeping(philo);
		think(philo);
	}
	return (0);
}

int	die_check(t_table *table)
{
	int	i;

	while (table->anyone_dead == NO)
	{
		i = 0;
		while (i < table->numofphilo)
		{
			if (get_time() - table->philos[i].last_eat > table->timetodie)
			{
				table->anyone_dead = YES;
				printf(DIE, get_time() - table->start_time,
					table->philos[i].philo_id);
				return (0);
			}
			if (table->all_eat == YES)
				return (0);
			i++;
		}
	}
	return (1);
}

int	create_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->numofphilo)
		pthread_create(&table->philos[i].id, NULL, &loop, &table->philos[i]);
	die_check(table);
	i = -1;
	while (++i < table->numofphilo)
		pthread_join(table->philos[i].id, NULL);
	i = -1;
	while (++i < table->numofphilo)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print_m);
	return (0);
}
