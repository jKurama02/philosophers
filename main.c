/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/12 15:59:22 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *miller(void *philos)
{
	t_philo *philo;
	philo = philos;

	while(philo->data->dead != 1)
	{
		if((ft_time() > philo->time_to_die) && philo-> eating != 1)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->lock);
			break;
		}
	}
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %i %s\n", (ft_time() - philo->data->start_time), philo->id, "died");
	pthread_mutex_unlock(&philo->data->write);
}


void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;

	if(pthread_create(&philo->s, NULL, &miller, (void *)philo))
			printf("error\n");
	if(philo->data->argument == 6)
	{
		while((philo->eat_cont <= philo->data->meals_number) && (philo->data->dead == 0))
		{
			think(philo);
			take_fork(philo);
		}
	}
	else if(philo->data->argument == 5)
	{
		while (philo->data->dead == 0)
		{
			think(philo);
			take_fork(philo);
		}
	}
	pthread_join(philo->s, NULL);
	return((void*) 0);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc == 6)
		data.argument = 6;
	if(argc == 5)
		data.argument = 5;
	if(argc == 5 || argc == 6)
	{
		if(check_input(argv))
			err_exit("Error check_input <3");
		if (init_input1(&data, argc, argv) || init_input2(&data))
			err_exit("Error init 1/ 2 <3");
		if (init_philo(&data))
			err_exit("Error philo <3");
		if(init_thread(&data))
			err_exit("Error init_thread <3");
		all_at_home(&data);
		return (0);
	}
}

int all_at_home(t_data *data)
{
	int i;

	i = 0;
	while(i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return (0);
}
