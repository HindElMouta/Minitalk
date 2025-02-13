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
	int shift;            // Variable pour stocker le "masque" pour le bit actuel
	static int i = 7;     // Variable statique pour suivre le bit actuel (on commence par le bit 7)
	static char c = 0;    // Variable statique pour stocker le caractère reconstruit

	if (i == -1 || pid != g_clientpid) // Si on a rencontré un nouveau PID ou si on a terminé un caractère (i == -1)
	{
		i = 7;            // On recommence avec le bit 7
		c = 0;            // On réinitialise le caractère à 0
		g_clientpid = pid; // On met à jour le PID du client
	}
	shift = 1 << (i); // On crée un "masque" pour vérifier quel bit est actuellement actif
	if (n != 0) // Si n est non nul, cela signifie qu'on a reçu un signal SIGUSR1 (bit 1)
		c = (c | shift);   // On met à 1 le bit correspondant dans le caractère
	i--;   // On passe au bit suivant (on décrémente i)
	if (i == -1) // Si on a parcouru tous les bits (i == -1), cela signifie qu'on a reconstruit un caractère complet
		write(1, &c, 1);  // On affiche le caractère reconstruit
}

// Fonction pour initialiser le serveur et afficher son PID
void server(void)
{
	int pid;

	pid = getpid(); // On récupère le PID du serveur
	ft_putnbr(pid); // On affiche le PID du serveur (fonction qui convertit le PID en nombre)
	write(1, "\n", 1); // On ajoute un saut de ligne pour plus de lisibilité
}

// Le gestionnaire de signaux
void sig_handler(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;  // On ignore ce paramètre

	if (sig == SIGUSR1) // On vérifie quel signal a été reçu : SIGUSR1 ou SIGUSR2
		rec(1, info->si_pid);  // Si SIGUSR1, on passe 1 à la fonction rec
	else
		rec(0, info->si_pid);  // Si SIGUSR2, on passe 0 à la fonction rec
}

// Fonction principale
int main(void)
{
	struct sigaction act;  // Structure pour configurer le gestionnaire de signaux

	act.sa_flags = 0;                  // On ne définit pas de flags particuliers
	act.sa_sigaction = sig_handler;    // On associe notre gestionnaire de signaux à la structure
	sigaction(SIGUSR1, &act, 0); // On enregistre le gestionnaire pour SIGUSR1 et SIGUSR2
	sigaction(SIGUSR2, &act, 0);
	server();  // Appel de la fonction server pour afficher le PID du serveur
	while (1) // Boucle infinie, le serveur attend et traite les signaux
		pause();  // Suspend l'exécution et attend des signaux
	return (0);  // Le programme ne devrait jamais arriver ici, car il est dans une boucle infinie
}