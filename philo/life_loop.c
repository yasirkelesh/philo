/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukeles <mukeles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:53:52 by mukeles           #+#    #+#             */
/*   Updated: 2022/09/29 13:53:53 by mukeles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal(t_philo *philo)
{
	long	current;

	current = get_time() - philo->table->start_time;//şimdiki zamandan başalngıç zamanını çıkart
	pthread_mutex_lock(&philo->table->forks[philo->l_fork_id]);//sağdaki çatalla aktif 
	pthread_mutex_lock(&philo->table->forks[philo->r_fork_id]);//soldaki çatallar aktif
	print_status(TAKEN, philo, current);//TAKEN i yazdır
	current = get_time() - philo->table->start_time;//geçen zamanı tekrar günceller
	print_status(EAT, philo, current);//yazdır
	philo->eat_count += 1;//yiyilen yemeği artırır
	time_skip(philo->table->timetoeat);// yemek yeme süresini bekletir
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->forks[philo->r_fork_id]);//çatalları tekrar kitler
	pthread_mutex_unlock(&philo->table->forks[philo->l_fork_id]);
}

void	sleeping(t_philo *philo)//filozofları uyutur
{
	long	current;

	current = get_time() - philo->table->start_time;
	print_status(SLEEP, philo, current);
	time_skip(philo->table->timetosleep);
}

void	think(t_philo *philo)//filozoflar düşünür
{
	long	current;

	current = get_time() - philo->table->start_time;
	print_status(THINK, philo, current);
}
