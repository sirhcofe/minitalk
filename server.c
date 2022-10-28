/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:39:05 by chenlee           #+#    #+#             */
/*   Updated: 2022/10/28 18:37:12 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
#include <stdlib.h>

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

	(void)(ucontext);
	if (signal == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	c += bit;
	bit_count++;
	printf("%d\n", bit);
	if (bit_count == 8)
	{
		write(1, "\n", 1);
		// write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			// kill(sa_siginfo->si_pid, SIGUSR1);
		}
		bit_count = 0;
		c = 0;
	}
	else
		c <<= 1;
	printf("sending siguser2 to pid %d\n", sa_siginfo->si_pid);
	kill(sa_siginfo->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	control_signal;
	struct sigaction	termination;

	printf("Server PID: %d\n", getpid());
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
