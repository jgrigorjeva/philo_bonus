/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:02:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 14:57:47 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"), 0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int	ft_msleep(unsigned int time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_msleep_check(unsigned int time, t_table *table, int i)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (is_dead(table, i))
			return (0);
		usleep(1000);
	}
	return (0);
}
