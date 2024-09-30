/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:07:45 by anmedyns          #+#    #+#             */
/*   Updated: 2024/09/30 13:37:34 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>


typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_cont;
	int				status;
	pthread_t		t;
	int				eating;
	uint64_t		last_meal;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				argument;
	int				philo_num;
	int				dead;
	int				finished;
	int				meals_number;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

//int visula_checker(t_philo *philosofo);

#endif

