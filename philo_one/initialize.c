/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:30:45 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/20 00:28:56 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int			initialize_philo(t_data *data, t_philo **philo, pthread_t **pt)
{
	int	i;

	*pt = malloc(sizeof(**pt) * data->philo_count);
	data->fork_mutex = malloc(sizeof(*data->fork_mutex) * data->philo_count);
	*philo = malloc(sizeof(**philo) * data->philo_count);
	if (*pt == NULL || data->fork_mutex == NULL || *philo == NULL)
	{
		free_philo(data, philo, pt);
		return (-1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		(*philo)[i].data = data;
		(*philo)[i].number = i + 1;
		(*philo)[i].lfork = i;
		(*philo)[i].rfork = (i + 1) % data->philo_count;
		(*philo)[i].amount_eaten = 0;
		++i;
	}
	return (0);
}

static int	verify_data(t_data *data, int eat_condition)
{
	if (data->philo_count < 2)
	{
		unlocked_message("At least 2 philosophers are required.");
		return (-1);
	}
	if (data->die_time <= 0 || data->eat_time <= 0 || data->sleep_time <= 0)
	{
		unlocked_message("Please enter a positive timestamp.");
		return (-1);
	}
	if (eat_condition && data->amount_to_eat < 0)
	{
		unlocked_message("A philosopher needs to eat a positive amount.");
		return (-1);
	}
	return (0);
}

int			initialize_data(t_data *data, char **argv, int eat_condition)
{
	data->start_time = get_time();
	data->state = ALIVE;
	data->philo_count = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->amount_to_eat = -1;
	if (eat_condition)
		data->amount_to_eat = ft_atoi(argv[5]);
	return (verify_data(data, eat_condition));
}
