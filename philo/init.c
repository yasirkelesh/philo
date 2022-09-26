/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:54:52 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 19:21:34 by ademirci         ###   ########.fr       */
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

int	init_philo(t_table *table)
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
		if (i % (table->numofphilo - 1) == 0 && i != 0)
			table->philos[i].r_fork_id = 0;
		else
			table->philos[i].r_fork_id = i + 1;
		table->philos[i].last_eat = table->start_time;
		table->philos[i].table = table;
		table->philos[i].eat_count = 0;
	}
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t *) * table->numofphilo);
	if (!table->forks)
	{
		error_manage(table->philos, "", FREE);
		error_manage(table, E_MLC, FREE);
		return (0);
	}
	while (++i < table->numofphilo)
		pthread_mutex_init(&table->forks[i], NULL);
	return (1);
}

int	init(t_table *table, int argc, char **argv)
{
	table->numofphilo = ft_atoi(argv[1]);
	table->timetodie = ft_atoi(argv[2]);
	table->timetoeat = ft_atoi(argv[3]);
	table->timetosleep = ft_atoi(argv[4]);
	table->philomusteat = EMPTY;
	table->anyone_dead = NO;
	table->all_eat = NO;
	table->start_time = get_time();
	pthread_mutex_init(&table->print_m, NULL);
	if (argc == 6)
		table->philomusteat = atoi(argv[5]);
	if (!init_philo(table))
		return (0);
	if (!init_forks(table))
		return (0);
	return (1);
}
