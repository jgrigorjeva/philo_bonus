/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:23:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:43:01 by jgrigorj         ###   ########.fr       */
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
	{
		printf("error sem_open in child\n");
		exit(EXIT_FAILURE);
	}
}

void	fill_input_numbers(t_input *input, char **argv)
{
	input->philo_nbr = ft_atoi(argv[1]);
	input->ttd = ft_atoi(argv[2]);
	input->tte = ft_atoi(argv[3]);
	input->tts = ft_atoi(argv[4]);
}
