/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:09:52 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:39:00 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_table *table, int i, const char *msg)
{
	long	now;
	long	timestamp;

	sem_wait(table->sems.print);
	now = get_time();
	timestamp = now - table->start_time;
	printf("%ld %d %s\n", timestamp, i, msg);
	sem_post(table->sems.print);
}
