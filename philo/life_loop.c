/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:55:55 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/28 19:58:23 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal(t_philo *philo)
{
	long	current;

	current = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->forks[philo->l_fork_id]);
	pthread_mutex_lock(&philo->table->forks[philo->r_fork_id]);
	print_status(TAKEN, philo, current);
	current = get_time() - philo->table->start_time;
	print_status(EAT, philo, current);
	philo->eat_count += 1;
	time_skip(philo->table->timetoeat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->table->forks[philo->l_fork_id]);
}

void	sleeping(t_philo *philo)
{
	long	current;

	current = get_time() - philo->table->start_time;
	print_status(SLEEP, philo, current);
	time_skip(philo->table->timetosleep);
}

void	think(t_philo *philo)
{
	long	current;

	current = get_time() - philo->table->start_time;
	print_status(THINK, philo, current);
}
