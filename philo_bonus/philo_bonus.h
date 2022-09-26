/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 20:04:57 by alperdemirc       #+#    #+#             */
/*   Updated: 2022/08/29 18:06:05 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

//include
# include "./libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

//define

//selection
# define YES 1
# define NO 0
//error message
# define E_MLC "Malloc Error!\n"
# define E_ARG "Arg Error!\n"
//error manage
# define FREE 1
# define NFREE 0
//extra
# define EMPTY -1
//life loop
# define EAT "\033[0;36m%ld %d is eating\033[0;37m\n"
# define SLEEP "\033[0;33m%ld %d is sleeping\033[0;37m\n"
# define THINK "\033[0;35m%ld %d is thinking\033[0;37m\n"
# define DIE "\033[0;37m%ld %d is died\033[0;37m\n"
# define TAKEN "\033[0;32m%ld %d has taken a fork\033[0;37m\n"

//struct
typedef struct s_table
{
	int				numofphilo;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				philomusteat;
	int				anyone_dead;
	int				all_eat;
	int				sem_msg;
	int				philo_id;
	int				*philo_index;
	int				philo_ate;
	long			philo_last_eat;
	long			start_time;
	sem_t			*print_lock;
	sem_t			*fork_lock;
	pthread_t		die_check_t;
}					t_table;

//function

//utils.c
int					all_must_ate(t_table *table);
void				sem_kill(t_table *table);
long				get_time(void);

//proccess.c
int					create_philo(t_table *table);
void				loop(t_table *table);
void				*die_check(void *t);

//philo_bonus.c
int					start(t_table *table, int argc, char **argv);
void				free_all(t_table *table);
void				error_manage(void *kill, char *msg, int code);

//init.c
int					digit_check(int argc, char **argv);
int					check_args(t_table *table, int argc, char **argv);
int					init(t_table *table, int argc, char **argv);
void				init_sem(t_table *table);

#endif