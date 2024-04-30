/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:57:48 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/30 14:19:38 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*fill_len(int len)
{
	char	*leng_para;
	int	i;

	i = 9;
	leng_para = strdup("0000000000");
	while (i >= 0)
	{
		leng_para[i] = (len % 10) + '0';
		len /= 10;
		i--;
	}
	printf("leng_para: %s\n", leng_para);
	return (leng_para);
}

int	send_length(int pid, char *len)
{
	int	i;
	int	j;

	i = 0;
	while (len[i] != '\0')
	{
		j = 0;
		while (j < 8)
		{
			if ((len[i] >> j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			j++;
		}
		i++;
	}
	return (0);
}

int	send_message (int pid, char *message)
{
	int		i;
	int		j;
	int		length;
	char	*leng_para;

	length = ft_strlen(message);
	leng_para = fill_len(length);
	send_length(pid, leng_para);
	free(leng_para);
	i = 0;
	while (message[i] != '\0')
	{
		j = 0;
		while (j < 8)
		{
			if ((message[i] >> j) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_printf(RED "Usage: ./client [PID] [message]\n" RESET);
		return (1);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	// system("leaks client");
	return (0);
}
