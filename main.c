/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:04:51 by anmedyns          #+#    #+#             */
/*   Updated: 2024/09/18 23:06:59 by anmedyns         ###   ########.fr       */
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

uint64_t ft_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_usleep(uint64_t microseconds)
{
	useconds_t usec = (useconds_t)microseconds;
	usleep(usec);
}

void *ft_sleep(void *philos)
{
	t_philo *philo;

	philo = philos;
	pthread_mutex_lock(&philo->data->write);
	printf("is sleeping : %li\n", ft_time() - philo->data->start_time);
	pthread_mutex_unlock(&philo->data->write);
}

void *think(void *philos)
{
	t_philo *philo;

	philo = philos;

	pthread_mutex_lock(&philo->data->write);
	printf("PHILOSOFO :%i\n", philo->id);
	printf("thinking : %li\n", ft_time() - philo->data->start_time);
	pthread_mutex_unlock(&philo->data->write);
}

void *take_fork_eat(void *philos)
{
		t_philo *philo;

	philo = philos;
	philo->time_to_die = philo->time_to_die + ft_time();

	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	printf("is take forks : %li\n", ft_time() - philo->data->start_time);
	printf("is eating: %li\n", ft_time() - philo->data->start_time);
	philo->eating = 1;
	philo->eat_cont++;
	philo->time_to_die = ft_time() + philo->time_to_die;
	usleep(philo->data->eat_time * 1000);

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("is drop forks : %li\n", ft_time() - philo->data->start_time);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->lock);
}


void *routine(void *philos)  //void * ----indica un puntatore generico
{
	t_philo *philo;

	philo = philos;
//	printf("N ARG = %i", philo->data->argument);
	if(philo->data->argument == 6)
	{
		while (philo->eat_cont < philo->data->meals_number)
		{
			think(philos);
			take_fork_eat(philos);

			printf("MEAL_count = %i/%i\n", philo->eat_cont, philo->data->meals_number);
			ft_sleep(philos);
			printf("______________________\n");
		}
	}

	else if(philo->data->argument == 5);
	{
		while (1)
		{
			printf("N ARG = %i", philo->data->argument);

			think(philos);
			take_fork_eat(philos);
			printf("MEAL_count = %i\n", philo->eat_cont);
			ft_sleep(philos);
			printf("______________________\n");
		}
	}


}

int init_thread(t_data *data)
{
	int i;
	int k;

	k = -1;
	i = -1;
	data->start_time = ft_time();
//	if (data->philos->id % 2 == 0)
//		usleep(500);

	while(++i < data->philo_num)
	{
		if(pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			printf("dio\n");
	}
	while(++k < data->philo_num)
	{
		if(pthread_join(data->tid[k], NULL))
			printf(" dio\n");
		usleep (500000);
	}
	return (0);
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
		else
			err_exit("Error number argument <3");
	}
}

//Domande a Lollo
// gli elementi della struttura data che e' una sottostruttura di philo , gli elementi sono condivisi con tutti i filosofi sumultaneamente ?
// problemi con numero di filosofi PARI
//
