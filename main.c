/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/01 15:12:15 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;


	if(philo->data->argument == 6)
	{
		while (0)
		{
			//think(philos);
			//take_fork_eat(philos);
			//printf("MEAL_count = %i/%i\n", philo->eat_cont, philo->data->meals_number);
			printf("_________________________\n\n");
		}
	}
	else if(philo->data->argument == 5)
	{
		while (0)
		{
			//think(philos);
			//take_fork_eat(philos);
			//printf("MEAL_count = %i\n", philo->eat_cont);
			printf("___________________________\n\n");
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

//		printf("death_time :%li\n", data.death_time);
//		printf("eat_time :%li\n", data.eat_time);
//		printf("sleep_time :%li\n", data.sleep_time);
//		printf("start_time : %li\n", data.start_time);
