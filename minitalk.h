/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:16:54 by marvin            #+#    #+#             */
/*   Updated: 2025/04/03 16:16:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// minitalk.h
#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>

extern pid_t g_clientpid;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_atoi(char *str, int *res);

#endif
