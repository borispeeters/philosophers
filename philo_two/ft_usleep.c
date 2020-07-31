/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_usleep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 16:20:39 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/31 16:29:23 by bpeeters      ########   odam.nl         */
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
