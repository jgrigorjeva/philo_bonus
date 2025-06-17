/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:09:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/17 20:10:39 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int			i;
	pid_t		pid;
	t_table		*table;
	pid_t		*pids;

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), 1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	i = 0;
	pids = malloc(sizeof(pid_t) * table->input_data->philo_nbr);
	if (!pids)
		return (printf("error in pids malloc\n"), clean_all(table), 1);
	while (i < table->input_data->philo_nbr)
	{
		pid = fork();
		if (pid < 0)
		{
			write(2, "Fork error\n", 11);
			break ;
		}
		else if (!pid)
		{
			routine(i + 1, table);
			exit(EXIT_SUCCESS);
		}
		pids[i] = pid;
		i++;
	}
	use_threads(table, pids);
	// wait_for_death(table, pids);
	// if (table->input_data->meal_nbr != -1)
	// 	wait_for_everyone_fed(table, pids);
	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free (pids);
	clean_all(table);
	return (0);
}

void	wait_for_everyone_fed(t_table *table, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		sem_wait(table->sems.max_meals_eaten);
		i++;
	}
	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

void	wait_for_death(t_table *table, pid_t *pids)
{
	int	i;

	sem_wait(table->sems.death);
	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}
