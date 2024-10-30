/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:57:55 by nlewicki          #+#    #+#             */
/*   Updated: 2024/05/27 13:04:35 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	procces_bits(int sig, t_server_state *info)
{
	if (sig == SIGUSR1)
		info->num |= (0 << info->bit_count);
	if (sig == SIGUSR2)
		info->num |= (1 << info->bit_count);
	info->bit_count++;
	info->total_bits++;
}

void	process_msg(t_server_state *info)
{
	info->msg[info->i] = info->num;
	info->i++;
	info->msg_length--;
	if (info->msg_length <= 0)
	{
		info->msg[info->i] = '\0';
		ft_printf("%s\n", info->msg);
		info->is_length_received = 0;
		info->total_bits = 0;
		info->msg_length = 0;
		info->i = 0;
		free(info->msg);
	}
}

void	sighandler(int sig)
{
	static t_server_state	info = {0, 0, 0, 0, 0, NULL, 0};

	procces_bits(sig, &info);
	if (info.bit_count == 8)
	{
		if (!info.is_length_received)
		{
			info.msg_length = info.msg_length * 10 + (info.num - '0');
			if (info.total_bits == 80)
			{
				info.is_length_received = 1;
				info.msg = (char *)malloc(sizeof(char) * info.msg_length + 1);
				if (!info.msg)
					exit(1);
			}
		}
		else
		{
			process_msg(&info);
		}
		info.num = 0;
		info.bit_count = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf(GREEN "Server PID: %d\n" RESET, pid);
	while (1)
	{
		signal(SIGUSR2, sighandler);
		signal(SIGUSR1, sighandler);
		pause();
	}
	return (0);
}
