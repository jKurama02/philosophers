/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/06 13:08:53 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *miller(void *philos)
{
	t_philo *philo;

	philo = philos;
	int i = 0;
	while(philo->data->dead != 1)
	{
		if(philo->data->finished == philo->data->philo_num)
		{
			pthread_mutex_lock(&philo->data->lock);
		}
	}
}


void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;


	if(philo->data->argument == 6)
	{
		while ((philo->eat_cont <= philo->data->meals_number) && (philo->data->dead == 0))
		{
			think(philos);
			take_fork(philos);
			my_usleep(philo->data->sleep_time);
		}
	}
	else if(philo->data->argument == 5)
	{
		while (philo->data->dead == 0)
		{
			think(philos);
			take_fork(philo);
			my_usleep(philo->data->sleep_time);
		}
	}
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
	}
		else
			err_exit("Error number argument <3");

}

