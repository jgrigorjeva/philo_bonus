/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:09:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/16 20:47:59 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{

	int			i;
	pid_t		pid;
	t_table		*table;

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), 1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	input = parse_input(argc, argv);
	if (!input)
		return (1);
	forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, input->philo_nbr);
	i = 0;
	while (i < input->philo_nbr)
	{
		pid = fork();
		if (pid < 0)
		{
			write(2, "Fork error\n", 11);
			break ;
		}
		else if (!pid)
		{
			routine();
			exit(EXIT_FAILURE);
		}
	}
	sem_close(forks);
	return (0);
}
