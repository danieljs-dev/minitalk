/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:02 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/24 09:47:33 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_signal_received = 0;

static void	signal_received(int signal)
{
	if (signal == SIGUSR1)
		g_signal_received = 1;
}

static void	transmit_message(int server_pid, char *message, size_t length)
{
	int		bit_index;
	size_t	char_index;

	char_index = 0;
	while (char_index < length)
	{
		bit_index = 0;
		while (bit_index < 8)
		{
			if ((message[char_index] >> (7 - bit_index)) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			bit_index++;
			usleep(10000);
			while (!g_signal_received)
				pause();
			g_signal_received = 0;
		}
		char_index++;
	}
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [SERVER_PID] [MESSAGE]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 1)
	{
		ft_printf("\nError: Invalid PID\n");
		return (1);
	}
	signal(SIGUSR1, signal_received);
	transmit_message(server_pid, argv[2], ft_strlen(argv[2]) + 1);
	return (0);
}
