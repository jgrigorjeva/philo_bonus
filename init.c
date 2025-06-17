/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:43:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/17 23:28:06 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	if (!argv)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf("Error allocating table\n"), NULL);
	table->input_data = parse_input(argc, argv);
	if (!table->input_data)
		return (free(table), NULL);
	if (init_sems(table))
		return (free(table->input_data), free(table), NULL);
	table->start_time = get_time() + 20;
	table->last_fed = table->start_time;
	table->is_dead = FALSE;
	table->meals_eaten = 0;
	return (table);
}

int	init_sems(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/max_meals");
	sem_unlink("/end");
	table->sems.forks = sem_open("/forks", O_CREAT | O_EXCL, \
		0644, table->input_data->philo_nbr);
	table->sems.print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	table->sems.death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
	table->sems.max_meals_eaten = sem_open("/max_meals", O_CREAT | O_EXCL, 0644, 0);
	table->sems.end = sem_open("/end", O_CREAT | O_EXCL, 0644, 1);
	if (table->sems.forks == SEM_FAILED || table->sems.print == SEM_FAILED \
		|| table->sems.death == SEM_FAILED \
		|| table->sems.max_meals_eaten == SEM_FAILED \
		|| table->sems.end == SEM_FAILED)
		return (printf("Error opening semaphores\n"), 1);
	return (0);
}
