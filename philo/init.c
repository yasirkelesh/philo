/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukeles <mukeles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:53:46 by mukeles           #+#    #+#             */
/*   Updated: 2022/09/29 13:53:47 by mukeles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	digit_check(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strisdigit(argv[i]))
			return (0);
	}
	return (1);
}

int	check_args(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		error_manage(table, E_ARG, FREE);
		return (0);
	}
	if (!digit_check(argc, argv))
	{
		error_manage(table, E_ARG, FREE);
		return (0);
	}
	if (0 > ft_atoi(argv[1]) || 200 < ft_atoi(argv[1]) || 60 > ft_atoi(argv[2])
		|| 60 > ft_atoi(argv[3]) || 60 > ft_atoi(argv[4]))
	{
		error_manage(table, E_ARG, FREE);
		return (0);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf(DIE, (long)ft_atoi(argv[2]) + 1, 1);
		error_manage(table, "", FREE);
		return (0);
	}
	return (1);
}

int	init_philo(t_table *table)//çatal ve filo ların id lerinin atanması 
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->numofphilo);
	if (!table->philos)
	{
		error_manage(table, E_MLC, FREE);
		return (0);
	}
	while (++i < table->numofphilo)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].l_fork_id = i;
		if (i % (table->numofphilo - 1) == 0 && i != 0)// en sondaki çatal üst üste binmesin diye
			table->philos[i].r_fork_id = 0;
		else
			table->philos[i].r_fork_id = i + 1;
		table->philos[i].last_eat = table->start_time;//son yemek için
		table->philos[i].table = table;
		table->philos[i].eat_count = 0;//henüz kimse yemedi
	}
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t *) * table->numofphilo);//philozof sayısı kadar mutex
	if (!table->forks)//malloc error
	{
		error_manage(table->philos, "", FREE);
		error_manage(table, E_MLC, FREE);
		return (0);
	}
	while (++i < table->numofphilo)//mutexelri yollaaaaa
		pthread_mutex_init(&table->forks[i], NULL);
	return (1);
}

int	init(t_table *table, int argc, char **argv)
{
	table->numofphilo = ft_atoi(argv[1]);
	table->timetodie = ft_atoi(argv[2]);
	table->timetoeat = ft_atoi(argv[3]);
	table->timetosleep = ft_atoi(argv[4]);
	table->philomusteat = EMPTY;//başta boş olaki argc = 6 olursa
	table->anyone_dead = NO;//ölen kimse varmı
	table->all_eat = NO; //hepsi yedi
	table->start_time = get_time();//başlangıç zamnı
	pthread_mutex_init(&table->print_m, NULL);//Yazdırma işlemi yaparken kullanılcak !
	if (argc == 6)
		table->philomusteat = atoi(argv[5]);// zorunluluk durumu ekstara argüman alır ise
	if (!init_philo(table))
		return (0);
	if (!init_forks(table))
		return (0);
	return (1);
}
