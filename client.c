/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:02 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/22 06:07:48 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_reply = 0;

static void	signal_reception(int signal)
{
	if (signal == SIGUSR1)
		g_reply = 1;
}

static void	send_signal(int pid, char *str, size_t len)
{
	int		bit;
	size_t	i;

	i = 0;
	while (i < len)
	{
		bit = 0;
		while (bit < 8)
		{
			if ((str[i] >> (7 - bit)) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit++;
			usleep(10000);
			while (!g_reply)
				pause();
			g_reply = 0;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("\n./client [PID_SERVER] [STRING_TO_PASS]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1)
	{
		ft_printf("\nError: Invalid PID");
		return (1);
	}
	signal(SIGUSR1, signal_reception);
	send_signal(pid, argv[2], ft_strlen(argv[2]) + 1);
	return (0);
}
