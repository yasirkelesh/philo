/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:54:52 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 17:42:14 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	init_sem(t_table *table)
{
	sem_unlink("/print_lock");
	sem_unlink("/fork_lock");
	table->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
	table->fork_lock = sem_open("/fork_lock", O_CREAT, 0644, table->numofphilo);
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
	table->philo_ate = 0;
	table->start_time = get_time();
	if (argc == 6)
		table->philomusteat = atoi(argv[5]);
	table->philo_index = malloc(sizeof(int) * table->numofphilo);
	if (!table->philo_index)
	{
		error_manage(table, E_MLC, FREE);
		return (0);
	}
	init_sem(table);
	return (1);
}
