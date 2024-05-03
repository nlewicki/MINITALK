/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:57:55 by nlewicki          #+#    #+#             */
/*   Updated: 2024/05/03 12:49:41 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// void	get_bits(int *num, int sig, int *bit_count)
// {
// 	if (sig == SIGUSR1)
// 		*num |= (0 << *bit_count);
// 	if (sig == SIGUSR2)
// 		*num |= (1 << *bit_count);
// 	(*bit_count)++;
// }

// void	sighandler(int sig)
// {
// 	static int	num = 0;
// 	static int	bit_count = 0;
// 	static int	total_bits = 0;
// 	static int	message_length = 0;
// 	static char	*msg = NULL;
// 	static int	i = 0;

// 	get_bits(&num, sig, &bit_count);
// 	total_bits++;
// 	if (bit_count == 8)
// 	{
// 		if (total_bits <= 80)
// 		{
// 			message_length = message_length * 10 + (num - '0');
// 			if (total_bits == 80)
// 			{
// 				msg = (char *)malloc(sizeof(char) * message_length + 1);
// 				if (!msg)
// 					exit(1);
// 			}
// 		}
// 		else
// 		{
// 			msg[i] = num;
// 			i++;
// 			message_length--;
// 			if (message_length <= 0)
// 			{
// 				msg[i] = '\0';
// 				ft_printf("%s\n", msg);
// 				total_bits = 0;
// 				message_length = 0;
// 				free(msg);
// 			}
// 		}
// 		num = 0;
// 		bit_count = 0;
// 	}
// }

void	sighandler(int sig)
{
	static int	num = 0;
	static int	bit_count = 0;
	static int	total_bits = 0;
	static int	message_length = 0;
	static int	is_length_received = 0;
	static char	*msg = NULL;
	static int	i = 0;

	if (sig == SIGUSR1)
		num |= (0 << bit_count);
	if (sig == SIGUSR2)
		num |= (1 << bit_count);
	bit_count++;
	total_bits++;
	if (bit_count == 8)
	{
		if (!is_length_received)
		{
			message_length = message_length * 10 + (num - '0');
			if (total_bits == 80)
			{
				is_length_received = 1;
				msg = (char *)malloc(sizeof(char) * message_length + 1);
				if (!msg)
					exit(1);
			}
		}
		else
		{
			msg[i] = num;
			i++;
			message_length--;
			if (message_length <= 0)
			{
				msg[i] = '\0';
				ft_printf("%s\n", msg);
				is_length_received = 0;
				total_bits = 0;
				message_length = 0;
				i = 0;
				free(msg);
			}
		}
		num = 0;
		bit_count = 0;
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
