/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:32:46 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/17 21:32:05 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(int i, t_table *table)
{
	reopen_sems(table);
	wait_before_start(table);
	while (!is_dead(table, i))
	{
		think(table, i);
		if (table->input_data->philo_nbr % 2 == 1 && get_time() - table->last_fed \
			< 2 * table->input_data->tte + table->input_data->tts)
			ft_msleep(5);
		if (!is_dead(table, i))
			eat(table, i);
		if (!is_dead(table, i))
			go_sleep(table, i);
	}
	clean_child(table);
}

void	think(t_table *table, int i)
{
	print_status(table, i, "is thinking");
}

void	go_sleep(t_table *table, int i)
{
	print_status(table, i, "is sleeping");
	ft_msleep(table->input_data->tts);
}

void	eat(t_table *table, int i)
{
	sem_wait(table->sems.forks);
	print_status(table, i, "has taken a fork");
	sem_wait(table->sems.forks);
	print_status(table, i, "has taken a fork");
	print_status(table, i, "is eating");
	table->last_fed = get_time();
	ft_msleep(table->input_data->tte);
	sem_post(table->sems.forks);
	sem_post(table->sems.forks);
	table->meals_eaten++;
	if (table->meals_eaten == table->input_data->meal_nbr)
		sem_post(table->sems.max_meals_eaten);
}