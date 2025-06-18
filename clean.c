/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:50:46 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 18:14:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_table *table)
{
	sem_close(table->sems.forks);
	sem_unlink("/forks");
	sem_close(table->sems.print);
	sem_unlink("/print");
	sem_close(table->sems.death);
	sem_unlink("/death");
	sem_close(table->sems.max_meals_eaten);
	sem_unlink("/max_meals");
	sem_close(table->sems.end);
	sem_unlink("/end");
	sem_destroy(&table->sems.data);
	free (table->input_data);
	free(table);
}

void	clean_child(t_table *table)
{
	sem_close(table->sems.forks);
	sem_close(table->sems.print);
	sem_close(table->sems.death);
	sem_close(table->sems.max_meals_eaten);
}
