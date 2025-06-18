/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:55 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:43:56 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor_routine(void *arg);
void	*fed_monitor_routine(void *arg);

void	use_threads(t_table *table, pid_t *pids)
{
	pthread_t		death_thread;
	pthread_t		fed_thread;
	t_monitor_args	args;

	args.end_flag = FALSE;
	args.pids = pids;
	args.table = table;
	pthread_create(&death_thread, NULL, death_monitor_routine, &args);
	if (table->input_data->meal_nbr != -1)
		pthread_create(&fed_thread, NULL, fed_monitor_routine, &args);
	if (table->input_data->meal_nbr != -1)
		pthread_join(fed_thread, NULL);
	pthread_join(death_thread, NULL);
}

void	*death_monitor_routine(void *arg)
{
	t_monitor_args	*args;
	int				i;

	args = (t_monitor_args *)arg;
	sem_wait(args->table->sems.death);
	sem_wait(args->table->sems.end);
	i = 0;
	if (args->end_flag == FALSE)
	{
		args->end_flag = TRUE;
		while (i < args->table->input_data->philo_nbr)
		{
			kill(args->pids[i], SIGKILL);
			i++;
		}
	}
	sem_post(args->table->sems.end);
	i = 0;
	while (i < args->table->input_data->philo_nbr)
	{
		sem_post(args->table->sems.max_meals_eaten);
		i++;
	}
	return (NULL);
}

void	*fed_monitor_routine(void *arg)
{
	t_monitor_args	*args;
	int				i;

	args = (t_monitor_args *)arg;
	i = 0;
	while (i < args->table->input_data->philo_nbr)
	{
		sem_wait(args->table->sems.max_meals_eaten);
		i++;
	}
	sem_wait(args->table->sems.end);
	i = 0;
	if (args->end_flag == FALSE)
	{
		args->end_flag = TRUE;
		while (i < args->table->input_data->philo_nbr)
		{
			kill(args->pids[i], SIGKILL);
			i++;
		}
	}
	sem_post(args->table->sems.end);
	sem_post(args->table->sems.death);
	return (NULL);
}
