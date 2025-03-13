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
	write(1, &c, 1);
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

	nbr = nb;
	if (nbr < 10)
	{
		ft_putchar(nbr + '0');
	}
	else 
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

// Fonction pour convertir une chaîne de caractères en entier
int ft_atoi(char *str, int *res)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	*res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*res *= 10;
		*res += str[i] - '0';
		i++;
	}
	return (1);
}
