/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 01:08:13 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 01:16:00 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "philosophers.h"

void		philo_process(t_data *data, t_philo *philo, pid_t *pt)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pt[i] = fork();
		if (pt[i] < 0)
		{
			ERROR;
		}
		else if (pt[i] == 0)
		{
			philo_loop(philo);
			exit(0);
		}
		else if (pt[i] > 0)
		{
			waitpid(pt[i], NULL, 0);
		}
	}
}
