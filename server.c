/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:39:05 by chenlee           #+#    #+#             */
/*   Updated: 2022/10/30 15:39:51 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	terminate_server(int signal)
{
	if (signal)
	{
		write(1, ": Server shutdown successfully.\n", 33);
		exit(0);
	}
}

void	action_is_coming(int signal, siginfo_t *sa_siginfo, void *ucontext)
{
	static int	bit_count;
	static char	c;
	int			bit;
	int			pid;

	pid = sa_siginfo->si_pid;
	(void)(ucontext);
	bit = ((signal == SIGUSR1) * 1) + 0;
	c += bit;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(pid, SIGUSR1);
		}
		bit_count = 0;
		c = 0;
	}
	else
		c <<= 1;
	usleep(300);
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	control_signal;
	struct sigaction	termination;
	int					pid;

	pid = (int)getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	control_signal.sa_sigaction = &action_is_coming;
	control_signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &control_signal, NULL);
	sigaction(SIGUSR2, &control_signal, NULL);
	termination.sa_handler = &terminate_server;
	sigaction(SIGINT, &termination, NULL);
	while (1)
		;
	return (0);
}

// sigemptyset(&control_signal.sa_mask);
// sigaddset(&control_signal.sa_mask, SIGINT);
