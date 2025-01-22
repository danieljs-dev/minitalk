/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:06 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/22 06:06:20 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message = {0, 0};

static void	join_message(void)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	c = (char)g_message.c;
	if (g_message.msg)
	{
		tmp = ft_strjoin(g_message.msg, &c);
		free(g_message.msg);
	}
	else
		tmp = ft_strdup(&c);
	if (!tmp)
		exit(EXIT_FAILURE);
	g_message.msg = tmp;
}

static void	process_character(void)
{
	if (g_message.c == '\0')
	{
		if (g_message.msg)
			ft_printf("%s\n", g_message.msg);
		else
			ft_printf("\n");
		free(g_message.msg);
		g_message.msg = NULL;
	}
	else
		join_message();
	g_message.c = 0;
}

static void	handle_message(int signal, siginfo_t *info, void *context)
{
	static int	bit_count = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_message.c = (g_message.c << 1) | 1;
	else if (signal == SIGUSR2)
		g_message.c = (g_message.c << 1);
	bit_count++;
	if (bit_count == 8)
	{
		process_character();
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

static void	get_pid_id(void)
{
	ft_printf("\n\033[31m");
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

	get_pid_id();
	sa.sa_sigaction = handle_message;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
