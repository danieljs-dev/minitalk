/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:02 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/18 09:18:44 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, char *str)
{
	int	i;
	int	c;

	while (*str)
	{
		i = 0;
		c = *str;
		while (i < 8)
		{
			if (1 & (c >> i))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			i++;
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		ft_printf("\nClient must receive 2 parameters: <PID> & <STRING>.\n");
	else
		send_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
