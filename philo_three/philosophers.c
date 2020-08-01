/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 01:08:13 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 21:29:50 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "philosophers.h"

static void	*monitor(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo*)v_philo;
	data = philo->data;
	while (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		sem_wait(data->eat_lock);
		if ((get_time() - philo->last_eaten) > data->die_time)
		{
			sem_post(data->dead_lock);
			philo_write(philo, "died");
			data->state = DEAD;
		}
		sem_post(data->eat_lock);
		usleep(100);
	}
	return (NULL);
}

static void	philo_loop(t_philo *philo)
{
	t_data		*data;
	pthread_t	pid;

	data = philo->data;
	philo->last_eaten = get_time();
	if (pthread_create(&pid, NULL, monitor, philo) != 0)
		exit(1);
	while (data->state == ALIVE && philo->amount_eaten != data->amount_to_eat)
	{
		philo_write(philo, "is thinking");
		philo_eat(philo);
		philo_write(philo, "is sleeping");
		ft_usleep(data->sleep_time);
	}
	pthread_join(pid, NULL);
	exit(0);
}

void		*philo_dead(void * v_data)
{
	t_data	*data;
	int		i;

	data = (t_data*)v_data;
	i = 0;
	sem_wait(data->dead_lock);
	sem_wait(data->write_lock);
	data->state = DEAD;
	while (i < data->philo_count)
	{
		kill(data->pid[i], SIGINT);
		++i;
	}
	return (NULL);
}

void		philo_process(t_data *data, t_philo *philo)
{
	int			i;
	int			status;
	pthread_t	died;

	i = 0;
	while (i < data->philo_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			while (i > 0)
			{
				--i;
				kill(data->pid[i], SIGINT);
			}
			return ;
		}
		else if (data->pid[i] == 0)
		{
			philo_loop(&philo[i]);
		}
		++i;
	}
	if (pthread_create(&died, NULL, philo_dead, data) != 0)
		;
	pthread_detach(died);
	i = 0;
	while (i < data->philo_count)
	{
		if (data->pid[i] > 0)
		{
			waitpid(data->pid[i], &status, WUNTRACED);
			if (!WIFEXITED(status) && !WIFSIGNALED(status))
				continue ;
		}
		++i;
	}
	if (data->state != DEAD)
		unlocked_message("All philosophers have eaten enough!");
}
