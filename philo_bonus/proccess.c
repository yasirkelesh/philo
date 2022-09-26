/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:00:14 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 18:16:27 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	loop(t_table *table)
{
	pthread_create(&table->die_check_t, NULL, &die_check, table);
	table->philo_last_eat = get_time();
	while (table->anyone_dead == NO && table->all_eat == NO)
	{
		sem_wait(table->fork_lock);
		sem_wait(table->fork_lock);
		sem_wait(table->print_lock);
		printf(TAKEN, get_time() - table->start_time, table->philo_id);
		printf(EAT, get_time() - table->start_time, table->philo_id);
		sem_post(table->print_lock);
		usleep(table->timetoeat * 1000);
		table->philo_last_eat = get_time();
		sem_post(table->fork_lock);
		sem_post(table->fork_lock);
		table->philo_ate++;
		sem_wait(table->print_lock);
		printf(SLEEP, get_time() - table->start_time, table->philo_id);
		sem_post(table->print_lock);
		usleep(table->timetosleep * 1000);
		sem_wait(table->print_lock);
		printf(THINK, get_time() - table->start_time, table->philo_id);
		sem_post(table->print_lock);
	}
	pthread_join(table->die_check_t, NULL);
	exit(1);
}

void	*die_check(void *t)
{
	t_table	*table;

	table = (t_table *)t;
	while (!all_must_ate(table))
	{
		if (get_time() - table->philo_last_eat > table->timetodie)
		{
			table->anyone_dead = YES;
			sem_wait(table->print_lock);
			printf(DIE, get_time() - table->start_time,
				table->philo_id);
			exit(1);
		}
		usleep(1000);
	}
	return (0);
}

int	create_philo(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->numofphilo)
	{
		table->philo_index[i] = fork();
		if (table->philo_index[i] == 0)
		{
			table->philo_id = i + 1;
			table->philo_last_eat = get_time();
			if (table->philo_id % 2 != 0)
				usleep(2500);
			loop(table);
		}
	}
	sem_kill(table);
	return (0);
}
