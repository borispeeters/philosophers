/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:42:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/21 23:12:26 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "philosophers.h"

void	ft_usleep(uint64_t wait_time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < wait_time)
		usleep(100);
}

int		first_fork(t_philo *philo)
{
	return (philo->number % 2 == 0 ? philo->lfork : philo->rfork);
}

int		second_fork(t_philo *philo)
{
	return (philo->number % 2 == 0 ? philo->rfork : philo->lfork);
}
