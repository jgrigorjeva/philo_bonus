/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:09:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/18 19:29:56 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int			i;
	t_table		*table;
	pid_t		*pids;

	if (argc < 5 || argc > 6)
		return (printf("Invalid number of arguments\n"), 1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	i = 0;
	pids = fork_children(table);
	if (!pids)
		return (1);
	use_threads(table, pids);
	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free (pids);
	clean_all(table);
	return (0);
}

pid_t	*fork_children(t_table *table)
{
	pid_t	*pids;
	pid_t	pid;
	int		i;

	pids = malloc(sizeof(pid_t) * table->input_data->philo_nbr);
	if (!pids)
		return (printf("error in pids malloc\n"), clean_all(table), NULL);
	i = 0;
	while (i < table->input_data->philo_nbr)
	{
		table->i = i + 1;
		pid = fork();
		if (pid < 0)
		{
			write(2, "Fork error\n", 11);
			break ;
		}
		run_child(table, pid, i);
		pids[i] = pid;
		i++;
	}
	return (pids);
}

void	run_child(t_table *table, pid_t pid, int i)
{
	if (!pid)
	{
		routine(i + 1, table);
		exit(EXIT_SUCCESS);
	}
}
