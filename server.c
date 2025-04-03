/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:43:18 by hinel-mo          #+#    #+#             */
/*   Updated: 2025/02/11 14:43:18 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	getpid(void);
void	ft_putchar(char c);
void	ft_putnbr(int nb);

pid_t g_clientpid = -1;

void	rec(int n, int pid)
{
	static int		i = 7;
	static char		c = 0;
	static int		last_pid = -1;
	int				current_bit;

	if (last_pid != pid)
	{
		i = 7;
		c = 0;
		last_pid = pid;
	}
	current_bit = 1 << i;
	if (n != 0)
		c |= current_bit;
	i--;
	if (i < 0)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		i = 7;
		c = 0;
	}
}

void	server(void)
{
	int pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
}

void	sig_handler(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;
	if (sig == SIGUSR1)
		rec(1, info->si_pid);
	else
		rec(0, info->si_pid);
}

int	main(void)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	server();
	while (1)
		pause();
	return (0);
}