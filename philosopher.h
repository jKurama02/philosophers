/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmedyns <anmedyns@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:07:45 by anmedyns          #+#    #+#             */
/*   Updated: 2024/10/15 18:17:55 by anmedyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		s;
	pthread_t		m;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	uint64_t		last_meal;
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

int			ft_atoi(char *str);
void		err_exit(char *err);
int			check_input(char **argv);
int			init_thread(t_data *data);
int			init_input1(t_data *data, int argc, char **argv);
int			init_input2(t_data *data);
uint64_t	ft_time(void);
int			init_philo(t_data *data);
void		*routine(void *philos);
int			my_usleep(useconds_t time);
void		*take_fork(void *singlephilo);
void		*think(void *singlephilo);
void		printa_cose(t_philo *philo, char *str);
void		*miller(void *philos);
int			all_at_home(t_data *data);
int			one_philo(t_data *data);

#endif
