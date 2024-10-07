/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/07 16:45:10 by anmedyns         ###   ########.fr       */
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
			printf("poverodio\n");
	if(philo->data->argument == 6)
	{
		while((philo->eat_cont <= philo->data->meals_number) && (philo->data->dead == 0))
		{
			think(philo);
			take_fork(philo);
			my_usleep(philo->data->sleep_time);
		}
	}
	else if(philo->data->argument == 5)
	{
		while (philo->data->dead == 0)
		{
			think(philo);
			take_fork(philo);
			my_usleep(philo->data->sleep_time);
		}
	}
	pthread_join(philo->s, NULL);
}

// ipotesi = ogni volta che chiamo printa_cose , dentro checko' se dead != 0
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

	// 	//pthread_mutex_lock(&philo->lock);
	// 	pthread_mutex_lock(&philo->data->lock);
	// 	if((ft_time() >= philo->time_to_die ) && philo->eating != 1)
	// 	{
	// 		philo->data->dead = 1;
	// 		//pthread_mutex_unlock(&philo->lock);
	// 		pthread_mutex_unlock(&philo->data->lock);
	// 	}
	// 	if(philo->eat_cont == philo->data->meals_number)
	// 	{
	// 		philo->data->finished++;
	// 		//pthread_mutex_unlock(&philo->lock);
	// 		pthread_mutex_unlock(&philo->data->lock);
	// 	}
	// //	pthread_mutex_unlock(&philo->lock);
	// 	pthread_mutex_unlock(&philo->data->lock);
