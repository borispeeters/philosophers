/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 01:08:13 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/20 17:20:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "philosophers.h"

static int	kill_children(t_data *data, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		kill(data->pid[i], SIGTERM);
		++i;
	}
	return (1);
}

static void	*philo_dead(void *v_data)
{
	t_data	*data;

	data = (t_data*)v_data;
	sem_wait(data->dead_lock);
	if (data->state != DEAD)
		kill_children(data, data->philo_count);
	data->state = DEAD;
	return (NULL);
}

static int	philo_fork(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (kill_children(data, i));
		else if (data->pid[i] == 0)
			philo_loop(&philo[i]);
		usleep(100);
		++i;
	}
	return (0);
}

static int	philo_wait(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->pid[i] > 0)
		{
			waitpid(data->pid[i], &status, WUNTRACED);
			if (WIFEXITED(status) || WIFSIGNALED(status))
			{
				if (WIFSIGNALED(status))
					data->state = DEAD;
				++i;
			}
		}
	}
	return (0);
}

void		philo_process(t_data *data, t_philo *philo)
{
	pthread_t	died;

	if (philo_fork(data, philo) != 0)
	{
		write(STDERR_FILENO, "Fork failed\n", 12);
		return ;
	}
	if (pthread_create(&died, NULL, philo_dead, data) != 0)
	{
		kill_children(data, data->philo_count);
		return ;
	}
	pthread_detach(died);
	philo_wait(data);
	if (data->state != DEAD)
	{
		unlocked_message("All philosophers have eaten enough!");
		data->state = DEAD;
		sem_post(data->dead_lock);
	}
}
