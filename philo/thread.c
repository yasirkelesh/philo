/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukeles <mukeles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:54:09 by mukeles           #+#    #+#             */
/*   Updated: 2022/09/29 13:54:10 by mukeles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->last_eat = get_time();
	if (philo->philo_id % 2 != 0)//burda id si tek olanlar yemek yesin diye diyerleri uyuyor
		usleep(5000);
	while (philo->table->anyone_dead == NO && !all_must_ate(philo->table))//henüz kimse ölmediyse ve herkes yemek yemediyse
	{
		meal(philo);
		sleeping(philo);
		think(philo);
	}
	return (0);
}

int	die_check(t_table *table)//ölen varmı yada herkes doydumu
{
	int	i;

	while (table->anyone_dead == NO)//henüz kimse ölmediyse
	{
		i = 0;
		while (i < table->numofphilo)
		{
			if (get_time() - table->philos[i].last_eat > table->timetodie)//şu an ki zamandan yemek yemedeği zaman ölme süresinden büyükse 
			{
				table->anyone_dead = YES;//biri öldü
				printf(DIE, get_time() - table->start_time,
					table->philos[i].philo_id);//ne kadar sürdü ve kim öldü
				return (0);
			}
			if (table->all_eat == YES)//herekes yedimi
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
		pthread_create(&table->philos[i].id, NULL, &loop, &table->philos[i]);//thread oluşturur ve hepsi loop fonksiyonunun çalıştırır
	die_check(table);//biri ölene kadar burda dursun
	i = -1;
	while (++i < table->numofphilo)
		pthread_join(table->philos[i].id, NULL);//zombi thread oluşmasın diye 
	i = -1;
	while (++i < table->numofphilo)
		pthread_mutex_destroy(&table->forks[i]);//mutexleri yok eder
	pthread_mutex_destroy(&table->print_m);
	return (0);
}
