/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:53 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/03 02:16:07 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_philo;
typedef struct s_data
{
	unsigned int	nbr_philo;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	int				nbr_eat;
	int				philos_eat;
	pthread_mutex_t	print_mutex;
	unsigned long	time_launch;
	struct s_philo	*philos;
}		t_data;

typedef struct s_philo
{
	t_data			*data;
	unsigned int	index;
	unsigned long	last_meal;
	int				nbr_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	l_meal_mutex;
	pthread_mutex_t	n_eat_mutex;
}		t_philo;

int				ft_atoi(const char *str);
t_data			*fill_argument(int ac, char **av);
int				is_valid_string(const char *str);
t_data			*fill_argument(int ac, char **av);
void			print_data(t_data *data);
int				check_arguments(t_data *data);
int				error_arguments(void);

unsigned long	get_time_ms(void);
void			print_situation(char c, t_philo *philo);
void			my_sleep(unsigned int tms);

void			*routine_philo(void *p);
int				fill_philos(t_data *data);
int				fill_philos_part1(t_data *data, int i);
int				fill_philos_part2(t_data *data, int i);
int				stop_nbr_eat(t_data *data);
int				stop_philo_died(t_data *data);

#endif
