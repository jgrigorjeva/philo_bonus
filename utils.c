/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:23:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/17 01:50:23 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_before_start(t_table *table)
{
	while (get_time() < table->start_time)
		ft_msleep(1);
}

void	reopen_sems(t_table *table)
{
	table->sems.forks = sem_open("/forks", 0);
	table->sems.print = sem_open("/print", 0);
	table->sems.death = sem_open("/death", 0);
	table->sems.max_meals_eaten = sem_open("/max_meals", 0);
	if (table->sems.forks == SEM_FAILED || table->sems.print == SEM_FAILED \
		|| table->sems.death == SEM_FAILED \
		|| table->sems.max_meals_eaten == SEM_FAILED)
	// if (table->sems.forks == SEM_FAILED || table->sems.print == SEM_FAILED)
	{
		printf("error sem_open in child\n");
		exit(EXIT_FAILURE);
	}
}