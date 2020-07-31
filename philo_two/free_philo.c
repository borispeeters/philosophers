/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 15:52:58 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/31 16:14:23 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

void	free_philo(t_philo **philo, pthread_t **pt)
{
	free(*pt);
	free(*philo);
}
