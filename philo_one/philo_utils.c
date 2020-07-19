/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 16:42:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/20 00:33:16 by bpeeters      ########   odam.nl         */
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

int		min(int lfork, int rfork)
{
	return (lfork < rfork ? lfork : rfork);
}

int		max(int lfork, int rfork)
{
	return (lfork > rfork ? lfork : rfork);
}
