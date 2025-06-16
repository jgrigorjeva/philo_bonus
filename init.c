/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:43:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/16 21:11:18 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table *init_table(int argc, char **argv)
{
    t_table	*table;

	if (!argv)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return(printf("Error allocating table\n"), NULL);
	table->input_data = parse_input(argc, argv);
	if (!table->input_data)
		return (NULL);
	if (init_sems(table))
		return (NULL);
		
	table->start_time = get_time() + 10;
}

int	init_sems(t_table *table)
{
		
	table->sems.forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->input_data->philo_nbr);
	table->sems.print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (table->sems.forks == SEM_FAILED || table->sems.print == SEM_FAILED)
		return (printf("Error opening semaphores\n"), 1);
	return (0);
}