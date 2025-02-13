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
	int shift;  // Variable pour stocker le bit courant
	int i;      // Variable pour parcourir les 8 bits du caractère

	i = 7;  // On commence à partir du bit le plus significatif
	while (i >= 0)  // On parcourt chaque bit (de 7 à 0)
	{
		shift = 1 << (i);  // Décale 1 à gauche pour créer un "masque" qui teste le i-ème bit
		if (c & shift)  // Si le bit est 1
			kill(pid, SIGUSR1);  // Envoie le signal SIGUSR1
		else  // Si le bit est 0
			kill(pid, SIGUSR2);  // Envoie le signal SIGUSR2
		usleep(500);  // On attend un peu pour éviter un envoi trop rapide (500 microsecondes)
		i--;  // On passe au bit suivant
	}
}

// Fonction qui envoie un message entier (chaîne de caractères) au serveur
void send_message(int pid, char *str)
{
	int i;

	i = 0;
	while (str[i])  // Tant qu'on n'a pas atteint la fin de la chaîne
	{
		send_char(pid, str[i]);  // Envoie chaque caractère du message un par un
		i++;  // On passe au caractère suivant
	}
	send_char(pid, str[i]);  // On envoie aussi le caractère nul '\0' pour marquer la fin de la chaîne
}

// Fonction qui vérifie que le PID est valide et envoie le message au serveur
int send(int pid, char *str)
{
	if (kill(pid, 0) == -1)  // Vérifie si le processus avec ce PID existe
	{
		ft_putstr("Invalid PID\n");  // Si le PID est invalide, affiche un message d'erreur
		return (1);  // Retourne 1 pour indiquer une erreur
	}
	else
	{
		if (pid == 0)  // Si le PID est 0, ce n'est pas un PID valide
		{    
			ft_putstr("Invalid PID\n");  // Affiche un message d'erreur
			return (1);  // Retourne 1 pour indiquer une erreur
		}
		send_message(pid, str);  // Si tout va bien, envoie le message
		return (0);  // Retourne 0 pour indiquer que l'envoi a réussi
	}
}

// Fonction principale (point d'entrée du programme)
int main(int ac, char **av)
{
	int pid;

	if (ac != 3)  // Vérifie si le nombre d'arguments est correct
	{
		ft_putstr("Usage: ./client <PID> <message>\n");  // Si pas 3 arguments, affiche l'usage
		return (1);  // Retourne 1 pour indiquer une erreur
	}
	if (ft_atoi(av[1], &pid) == 0 || pid <= 0)  // Convertit l'argument PID en entier et vérifie sa validité
	{
		ft_putstr("Invalid PID\n");  // Si la conversion échoue ou si le PID est invalide, affiche une erreur
		return (1);  // Retourne 1 pour indiquer une erreur
	}
	if (send(pid, av[2]) == 1)  // Envoie le message au serveur et vérifie si l'envoi a échoué
	{
		ft_putstr("Error sending message\n");  // Si l'envoi échoue, affiche une erreur
		return (1);  // Retourne 1 pour indiquer une erreur
	}
	return (0);  // Si tout s'est bien passé, retourne 0 pour indiquer que tout est ok
}