/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:33:48 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:38:39 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <pthread.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <sys/time.h> // gettimeofday
# include <stdint.h> // uint64_t type
# include <unistd.h> // usleep
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
# include <semaphore.h>
# include <sys/types.h> // for waitpid
# include <sys/wait.h>
# include <sys/types.h> // for kill
# include <signal.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_input
{
	int	philo_nbr;
	int	ttd;
	int	tte;
	int	tts;
	int	meal_nbr;
}	t_input;

typedef struct s_sem
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*death;
	sem_t	*max_meals_eaten;
	sem_t	*end;
	sem_t	data;
}	t_sem;

typedef struct s_table
{
	t_input	*input_data;
	t_sem	sems;
	long	start_time;
	long	last_fed;
	t_bool	is_dead;
	int		meals_eaten;
	int		i;
}	t_table;

typedef struct s_monitor_args
{
	t_table	*table;
	pid_t	*pids;
	t_bool	end_flag;
}	t_monitor_args;

// init
t_table	*init_table(int argc, char **argv);
t_input	*parse_input(int argc, char **argv);
void	fill_input_numbers(t_input *input, char **argv);
int		ft_atoi(const char *nptr);
int		init_sems(t_table *table);

// routine
void	routine(int i, t_table *table);
pid_t	*fork_children(t_table *table);
void	run_child(t_table *table, pid_t pid, int i);
void	print_status(t_table *table, int i, const char *msg);
void	reopen_sems(t_table *table);
void	think(t_table *table, int i);
void	go_sleep(t_table *table, int i);
void	eat(t_table *table, int i);
t_bool	is_dead(t_table *table, int i);
void	handle_one_philo(t_table *table);
t_bool	should_die(t_table *table);

// threads
void	use_threads(t_table *table, pid_t *pids);
void	*death_monitor(void *arg);

// time
long	get_time(void);
int		ft_msleep(unsigned int time);
int		ft_msleep_check(unsigned int time, t_table *table, int i);
void	wait_before_start(t_table *table);

// end
void	clean_all(t_table *table);
void	clean_child(t_table *table);

#endif