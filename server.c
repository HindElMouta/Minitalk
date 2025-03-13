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

#include <signal.h>
#include <unistd.h>

pid_t	getpid(void);
void	ft_putchar(char c);
void	ft_putnbr(int nb);

pid_t g_clientpid = -1;  // Variable globale pour stocker le PID du client

// Fonction pour reconstruire un caractère à partir des signaux reçus
void rec(int n, int pid)
{
	int current_bit;
	static int	i;
	static char	c;

	i = 7;
	c = 0;
	if (i == -1 || pid != g_clientpid)
	{
		i = 7;
		c = 0;
		g_clientpid = pid;
	}
	current_bit = 1 << (i);
	if (n != 0)
		c = (c | current_bit);
	i--;
	if (i == -1)
		write(1, &c, 1);
}

// Fonction pour initialiser le serveur et afficher son PID
void server(void)
{
	int pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
}

// Le gestionnaire de signaux
void sig_handler(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;

	if (sig == SIGUSR1)
		rec(1, info->si_pid);
	else
		rec(0, info->si_pid);
}

// Fonction principale
int main(void)
{
	struct sigaction act;

	act.sa_flags = 0;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	server();
	while (1)
		pause();
	return (0);
}