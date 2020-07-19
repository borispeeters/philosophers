/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 23:39:39 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/19 23:43:08 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

void	free_philo(t_data *data, t_philo **philo, pthread_t **pt)
{
	free(*pt);
	free(data->fork_mutex);
	free(*philo);
}
