/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:30:45 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 16:32:19 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	free_philo(t_data *data, t_philo **philo, pthread_t **pt)
{
	free(*pt);
	free(data->fork_mutex);
	free(*philo);
}

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
		(*philo)[i].num = i + 1;
		(*philo)[i].lfork = i;
		(*philo)[i].rfork = (i + 1) % data->philo_count;
		(*philo)[i].eaten = 0;
		++i;
	}
	return (0);
}

void		initialize_data(t_data *data, char **argv, int eat_condition)
{
	data->start_time = get_time();
	data->isdead = 0;
	data->philo_count = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->eat_num = -1;
	if (eat_condition)
		data->eat_num = ft_atoi(argv[5]);
}
