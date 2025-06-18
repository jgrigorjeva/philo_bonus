/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:32:46 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:40:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(int i, t_table *table)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_monitor, table);
	pthread_detach(monitor);
	reopen_sems(table);
	wait_before_start(table);
	if (table->input_data->philo_nbr == 1)
		return (handle_one_philo(table));
	think(table, i);
	if (i % 2)
		ft_msleep(10);
	while (1)
	{
		if (table->input_data->philo_nbr % 2 \
			== 1 && get_time() - table->last_fed \
			< 2 * table->input_data->tte + table->input_data->tts)
			ft_msleep(5);
		eat(table, i);
		go_sleep(table, i);
		think(table, i);
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
	ft_msleep_check(table->input_data->tts, table, i);
}

void	eat(t_table *table, int i)
{
	sem_wait(table->sems.forks);
	print_status(table, i, "has taken a fork");
	sem_wait(table->sems.forks);
	print_status(table, i, "has taken a fork");
	print_status(table, i, "is eating");
	sem_wait(&table->sems.data);
	table->last_fed = get_time();
	sem_post(&table->sems.data);
	ft_msleep_check(table->input_data->tte, table, i);
	sem_post(table->sems.forks);
	sem_post(table->sems.forks);
	table->meals_eaten++;
	if (table->meals_eaten == table->input_data->meal_nbr)
		sem_post(table->sems.max_meals_eaten);
}

void	handle_one_philo(t_table *table)
{
	think(table, 1);
	print_status(table, 1, "has taken a fork");
	while (!is_dead(table, 1))
		ft_msleep(1);
}
