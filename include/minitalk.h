/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:34:22 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 10:00:49 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef struct t_server
{
	int		num;
	int		bit_count;
	int		total_bits;
	int		msg_length;
	int		is_length_received;
	char	*msg;
	int		i;
}	t_server_state;

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"

#endif
