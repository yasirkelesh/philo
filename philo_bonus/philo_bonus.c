/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:59:16 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 17:55:30 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_table *table)
{
	free(table->philo_index);
	free(table);
}

void	error_manage(void *kill, char *msg, int code)
{
	if (code == FREE)
		free(kill);
	printf("%s", msg);
}

int	start(t_table *table, int argc, char **argv)
{
	if (!check_args(table, argc, argv))
		return (0);
	if (!init(table, argc, argv))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (0);
	if (!start(table, argc, argv))
		return (0);
	if (!create_philo(table))
		free_all(table);
	return (1);
}
