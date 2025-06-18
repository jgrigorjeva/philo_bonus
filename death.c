/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:08:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 17:57:33 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	should_die(t_table *table)
{
	t_bool	status;

	sem_wait(&table->sems.data);
	status = get_time() - table->last_fed >= table->input_data->ttd;
	sem_post(&table->sems.data);
	return (status);
}

void	philo_dies(t_table *table, int i)
{
	if (!table->is_dead)
		print_status(table, i, "died");
	sem_wait(table->sems.print);
	sem_post(table->sems.death);
	table->is_dead = TRUE;
}

t_bool	is_dead(t_table *table, int i)
{
	if (should_die(table))
	{
		philo_dies(table, i);
		return (TRUE);
	}
	else
		return (FALSE);
}