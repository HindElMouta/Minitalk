/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:42:39 by hinel-mo          #+#    #+#             */
/*   Updated: 2025/02/11 14:42:39 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		ft_atoi(char *str, int *res);
void	ft_putchar(char c);
void	ft_putstr(char *str);

void	send_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit--;
	}
}

void	send_message(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		send_char(pid, str[i++]);
	send_char(pid, '\0');
}

int	send(int pid, char *str)
{
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr("Invalid PID\n");
		return (1);
	}
	send_message(pid, str);
	return (0);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_putstr("Usage: ./client <PID> <message>\n");
		return (1);
	}
	if (!ft_atoi(av[1], &pid))
	{
		ft_putstr("Invalid PID\n");
		return (1);
	}
	if (send(pid, av[2]) != 0)
	{
		ft_putstr("Error sending message\n");
		return (1);
	}
	return (0);
}