/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/09/10 22:45:02 by anmedyns         ###   ########.fr       */
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

void err_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}

int	check_input(char **argv)
{
	int	i;
	int	k;

	i = 0;
	while(argv[++i])
	{
		k = 0;
		while(argv[i][k])
		{
			if(argv[i][k] == ' ' || argv[i][k] == '+')
				k++;
			else if (!(argv[i][k] >= 48 && argv[i][k] <= 57))
				return (1);
			k++;
		}
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
		|| data->philo_num > 200)
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
		data->philos[i].r_fork = &data->forks[data->philo_num - i];
		data->philos[i].l_fork = &data->forks[i];
	}
	return (0);
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
		data->philos[i].time_to_die = data->death_time;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	return 0;
}
int routine(t_data *data)
{
			//3.4 guida Nikoter 
}
int main(int argc, char **argv)
{
	t_data data;

	if(argc == 5 || argc == 6)
	{
		if(check_input(argv))
			err_exit("Error check_input <3");
		if (init_input1(&data, argc, argv) || init_input2(&data))
			err_exit("Error init 1/ 2 <3");
		if (init_philo(&data))
			err_exit("Error philo <3");
		if(routine(&data));
		return 0;
	}
	else
		err_exit("Error number argument <3");
}
