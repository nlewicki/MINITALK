/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:57:55 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/30 14:24:12 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	poweroftwo(int num)
{
	int	i;

	i = 1;
	while (num--)
		i = i * 2;
	return (i);
}

int	bit_to_num(int num, int sig, int eight_bits)
{
	int	bit;

	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	num = num + bit * poweroftwo(eight_bits);
	return (num);
}

int	write_return_0(int num)
{
	write(1, &num, 1);
	return (0);
}

void	sighandler(int sig)
{
	static int	num;
	static int	eight_bits;
	static int	whole_bits;
	static int	len;

	num = bit_to_num(num, sig, eight_bits);
	eight_bits++;
	whole_bits++;
	if (whole_bits == 8)
	{
		if (!num)
			whole_bits = write_return_0(10);
		else
			len = num;
		num = 0;
		eight_bits = 0;
	}
	if (whole_bits > 8 && (whole_bits % 8) == 0)
	{
		eight_bits = 0;
		num = write_return_0(num);
		if (whole_bits == 8 * (len + 1))
			whole_bits = write_return_0(10);
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

