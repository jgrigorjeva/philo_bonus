/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:33:48 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/16 21:11:38 by jgrigorj         ###   ########.fr       */
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
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

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
} t_sem;

typedef struct s_table
{
	t_input	*input_data;
	t_sem	sems;
	long	start_time;
} t_table;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

t_table *init_table(int argc, char **argv);
t_input	*parse_input(int argc, char **argv);
int		init_sems(t_table *table);

#endif