/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:12:50 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 17:58:34 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;

	while (1)
	{
		if (should_die(table))
		{
			print_status(table, table->i, "died");
			sem_post(table->sems.death);
			sem_destroy(&table->sems.data);
			sem_wait(table->sems.print);
			exit (1);
		}
		ft_msleep(1);
	}
	return (NULL);
}