/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:05:24 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/15 14:38:42 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	err_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}

int	check_input(char **argv)
{
	int	i;
	int	k;

	i = 0;
	while (argv[++i])
	{
		k = 0;
		while (argv[i][k])
		{
			if (argv[i][k] == ' ' || argv[i][k] == '+')
				k++;
			else if (!(argv[i][k] >= 48 && argv[i][k] <= 57))
				return (1);
			k++;
		}
	}
	return (0);
}

int	my_usleep(useconds_t time)
{
	u_int64_t	start;

	start = ft_time();
	while ((ft_time() - start) < time)
		usleep(time / 10);
	return (0);
}
