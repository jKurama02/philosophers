/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:14:00 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/13 19:57:25 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void printa_cose(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write);
	if(philo->data->dead != 0)
	{
		pthread_mutex_destroy(philo->l_fork);
		pthread_mutex_destroy(philo->r_fork);
		pthread_mutex_unlock(&philo->data->write);
		return ;
	}
	printf("%ld %i %s\n", (ft_time() - philo->data->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void *think(void *singlephilo)
{
	t_philo *philo;
	
	philo = singlephilo;
	printa_cose(philo, "is thinking");
}

void *take_fork(void *singlephilo)
{
	t_philo *philo;

	philo = singlephilo;

	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->r_fork);
	printa_cose(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	printa_cose(philo, "has taken a fork");
	philo->eating = 1;
	printa_cose(philo, "is eating");
	philo->time_to_die = philo->data->death_time + ft_time();
	my_usleep(philo->data->eat_time);
	philo->last_meal = ft_time();
	philo->eating = 0;
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printa_cose(philo, "is sleeping");
	my_usleep(philo->data->sleep_time);
}

