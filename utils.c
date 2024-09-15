/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:14:29 by anmedyns          #+#    #+#             */
/*   Updated: 2024/09/15 20:25:59 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void take_fork(t_philo *philosofo)
{
	pthread_mutex_lock(philosofo->r_fork);
	pthread_mutex_lock(philosofo->l_fork);
	printf("Take forks : %u", ft_time());
	pthread_mutex_unlock(philosofo->r_fork);
	pthread_mutex_unlock(philosofo->l_fork);
}
int visula_checker(t_philo *philosofo)
{
	t_philo *philo;

	philo = philosofo;
	take_fork(philo);
	return 0;
}

