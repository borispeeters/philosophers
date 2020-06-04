/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 00:26:26 by anonymous      #+#    #+#                */
/*   Updated: 2020/03/20 00:26:26 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
	int			i;
	long long	ans;
	int			ncheck;

	i = 0;
	ans = 0;
	ncheck = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		ncheck = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ans * 10 + str[i] - '0' < ans)
		{
			ans = (-1 * ncheck - 1) / 2;
			return (ans * ncheck);
		}
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (ans * ncheck);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putlong_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n > 9)
		ft_putlong_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}