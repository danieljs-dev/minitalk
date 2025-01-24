/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:29:06 by dajesus-          #+#    #+#             */
/*   Updated: 2025/01/24 09:47:28 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static t_message_state	g_message_state = {0, 0};

static void	append_character_to_message(void)
{
	char	*temp;
	char	new_char;

	temp = NULL;
	new_char = (char)g_message_state.current_char;
	if (g_message_state.message)
	{
		temp = ft_strjoin(g_message_state.message, &new_char);
		free(g_message_state.message);
	}
	else
		temp = ft_strdup(&new_char);
	if (!temp)
		exit(EXIT_FAILURE);
	g_message_state.message = temp;
}

static void	handle_complete_character(void)
{
	if (g_message_state.current_char == '\0')
	{
		if (g_message_state.message)
			ft_printf("%s\n", g_message_state.message);
		else
			ft_printf("\n");
		free(g_message_state.message);
		g_message_state.message = NULL;
	}
	else
		append_character_to_message();
	g_message_state.current_char = 0;
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	bit_count = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_message_state.current_char = (g_message_state.current_char << 1) | 1;
	else if (signal == SIGUSR2)
		g_message_state.current_char = (g_message_state.current_char << 1);
	bit_count++;
	if (bit_count == 8)
	{
		handle_complete_character();
		bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

static void	display_server_pid(void)
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

int	main(int argc, char *argv[])
{
	struct sigaction	signal_action;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Usage: ./server_bonus\n");
		return (1);
	}
	display_server_pid();
	signal_action.sa_sigaction = handle_signal;
	signal_action.sa_flags = SA_SIGINFO;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	while (1)
		pause();
	return (0);
}
