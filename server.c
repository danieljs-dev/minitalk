/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:06 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/18 09:58:55 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_message(int signal)
{
	static int	i = 0;
	static char	c = 0;

	if (signal == SIGUSR2)
		c += (1 << i);
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
}

void	get_pid_id(void)
{
	ft_printf("\033[31m");
	ft_printf("███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗██╗\n");
	ft_printf("\033[32m");
	ft_printf("██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝\n");
	ft_printf("\033[33m");
	ft_printf("██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗\n");
	ft_printf("\033[34m");
	ft_printf("██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\n");
	ft_printf("\033[35m");
	ft_printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
	ft_printf("\033[0m");
	ft_printf("\n");
	ft_printf("\033[36m");
	ft_printf("\033[33m                PID: %d   \033[34mBy: dajesus-\033[0m\n",
		getpid());
	ft_printf("\033[37m");
	ft_printf("\033[32m⊱ ─────────────────── {.⋅ ✯ ⋅.} ──────────────────── ⊰\n");
	ft_printf("\033[0m");
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_message;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// ft_printf("SERVER PROCESS ID | %d\n", getpid());
	get_pid_id();
	while (1)
		pause();
}
