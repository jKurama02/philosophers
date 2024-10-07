/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:02:01 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/07 16:26:44 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int init_thread(t_data *data)
{
	int i;
	int k;

	k = -1;
	i = -1;
	data->start_time = ft_time();
	//if(data->meals_number > 0)
	//{
	//	if(pthread_create(&data->philos[0].m, NULL, &miller, &data->philos[0]))
	//		printf("dio\n");
	//}
	while(++i < data->philo_num)
	{
		//if((data->philos[i].id % 2) == 1)
		//	my_usleep(1);
		if(pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			printf("dio\n");
		my_usleep(1);
	}

	while(++k < data->philo_num)
	{
		if(pthread_join(data->tid[k], NULL))
			printf(" dio\n");
	}
	return (0);
}

int init_input1(t_data *data, int argc, char **argv)
{
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = (uint64_t) ft_atoi(argv[2]);
	data->eat_time = (uint64_t) ft_atoi(argv[3]);
	data->sleep_time = (uint64_t) ft_atoi(argv[4]);
	if(argc == 6)
		data->meals_number = ft_atoi(argv[5]);
	if(data->philo_num <= 0 || data->death_time < 0
		|| data->eat_time < 0 || data->sleep_time < 0
		|| data->philo_num > 200 || data->meals_number >= 200)
		return (1);
	data->finished = 0;
	data->dead = 0;
	return (0);
}
int init_input2(t_data *data)
{
	int i;

	i = -1;
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	while(++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].r_fork = &data->forks[data->philo_num - 1]; // se ho 4 filosofi , le forchetta saranno 4 ma partono da [0],[1],[2],[3]
	data->philos[0].l_fork = &data->forks[0];
	i = 0;
	while(++i < data->philo_num)
	{
		data->philos[i].r_fork = &data->forks[i - 1]; // co dio
		data->philos[i].l_fork = &data->forks[i];
	}
	return (0);
}
uint64_t ft_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int init_philo(t_data *data)
{
	int i;

	i = -1;
	while(++i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_cont = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].last_meal = ft_time();
		data->philos[i].time_to_die = ft_time() + data->death_time;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	return 0;
}
