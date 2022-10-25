/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:38:50 by chenlee           #+#    #+#             */
/*   Updated: 2022/10/25 15:22:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>

void	msg_recv(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Message received!\n", 18);
}

void	send_bit(int pid, char c)
{
	int	bit_count;

	bit_count = 7;
	while (bit_count >= 0)
	{
		if ((c & (1 << bit_count)) > 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit_count--;
		usleep(690);
	}
}

void	send_msg(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		send_bit(pid, str[i]);
	send_bit(pid, str[i]);
}

int	main(int argc, char **argv)
{
	struct sigaction	*sig_act;
	pid_t				pid;

	if (argc != 3)
		write(1, "Usage: ./client <server-pid> <message>\n", 39);
	else
	{
		sig_act = malloc(sizeof(sigaction));
		sig_act->sa_handler = msg_recv;
		sigaction(SIGUSR1, sig_act, NULL);
		pid = (pid_t)ft_atoi(argv[1]);
		if (kill(pid, 0) == -1)
			write(1, "Wrong PID\n", 10);
		send_msg(pid, argv[2]);
		free(sig_act);
	}
}
