/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/08 19:45:20 by anmedyns         ###   ########.fr       */
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
}


void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;

	if(pthread_create(&philo->s, NULL, &miller, (void *)philo))
			printf("poverodio\n");
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
		at_home(&data);
		return (0);
	}
}

int at_come(t_data *data)
{
	while(
		
	)
}
/*
	sistemare :

		input 1 filosofo = morte diretta;
		se mangiano quanto devono , finire il programma senza farli morire


*/
