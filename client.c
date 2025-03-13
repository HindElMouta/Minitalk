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

#include <unistd.h>
#include <signal.h>

int		ft_atoi(char *str, int *res);
void	ft_putchar(char c);
void	ft_putstr(char *str);

// Fonction qui envoie un caractère (8 bits) en utilisant des signaux SIGUSR1 et SIGUSR2
void send_char(int pid, char c)
{
	int current_bit;
	int i;

	i = 7;
	while (i >= 0)
	{
		current_bit = 1 << (i);
		if (c & current_bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		i--;
	}
}

// Fonction qui envoie un message entier (chaîne de caractères) au serveur
void send_message(int pid, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, str[i]);
}

// Fonction qui vérifie que le PID est valide et envoie le message au serveur
int send(int pid, char *str)
{
	if (kill(pid, 0) == -1)
	{
		ft_putstr("Invalid PID\n");
		return (1);
	}
	else
	{
		if (pid == 0)
		{    
			ft_putstr("Invalid PID\n");
			return (1);
		}
		send_message(pid, str);
		return (0);
	}
}

// Fonction principale (point d'entrée du programme)
int main(int ac, char **av)
{
	int pid;

	if (ac != 3)
	{
		ft_putstr("Usage: ./client <PID> <message>\n");
		return (1);
	}
	if (ft_atoi(av[1], &pid) == 0 || pid <= 0)
	{
		ft_putstr("Invalid PID\n");
		return (1);
	}
	if (send(pid, av[2]) == 1)
	{
		ft_putstr("Error sending message\n");
		return (1);
	}
	return (0);
}