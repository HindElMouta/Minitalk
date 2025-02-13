/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:14:19 by hinel-mo          #+#    #+#             */
/*   Updated: 2025/02/11 17:14:19 by hinel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

// Fonction pour afficher un caractère à l'écran
void ft_putchar(char c)
{
	write(1, &c, 1);  // Écrit le caractère
}

// Fonction pour afficher une chaîne de caractères
void ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

// Fonction pour afficher un nombre entier (en base 10)
void ft_putnbr(int nb)
{
	long nbr;

	nbr = nb;  // Utilisation de 'long' pour gérer les grands nombres et éviter un dépassement de capacité
	if (nbr < 10) // Si le nombre est inférieur à 10 (cas de base), on l'affiche directement
	{
		ft_putchar(nbr + '0');  // Convertit le chiffre en caractère (par exemple 5 devient '5') et l'affiche
	}
	else // Si le nombre est plus grand que 9, on divise récursivement
	{
		ft_putnbr(nbr / 10);   // Affiche la partie entière du nombre (les chiffres les plus à gauche)
		ft_putnbr(nbr % 10);   // Affiche le reste (les chiffres les plus à droite)
	}
}

// Fonction pour convertir une chaîne de caractères en entier
int ft_atoi(char *str, int *res)
{
	int i = 0;

	while (str[i]) // Vérifie que tous les caractères sont des chiffres
	{
		if (str[i] < '0' || str[i] > '9')  // Si le caractère n'est pas un chiffre
			return (0);  // Retourne 0 pour signaler qu'il y a une erreur (non numérique)
		i++;
	}
	*res = 0;  // Initialise la variable de résultat à zéro
	i = 0;     // Réinitialise l'indice pour parcourir à nouveau la chaîne
	while (str[i] >= '0' && str[i] <= '9')  // Tant qu'on trouve des chiffres
	{
		*res *= 10;  // Décale le résultat d'un chiffre vers la gauche (multiplie par 10)
		*res += str[i] - '0';  // Ajoute le chiffre actuel à la fin du nombre
		i++;  // Passe au caractère suivant
	}
	return (1);  // Retourne 1 pour signaler que la conversion a réussi
}
