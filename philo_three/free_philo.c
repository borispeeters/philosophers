/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 00:43:35 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/08/01 21:00:08 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

void	free_philo(t_philo **philo, t_data *data)
{
	free(data->pid);
	free(*philo);
}
