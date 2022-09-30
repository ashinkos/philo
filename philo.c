/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/30 23:49:37 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_ms(void)
{
	struct timeval	rtk;

	gettimeofday(&rtk, NULL);
	return (rtk.tv_sec * 1000 + rtk.tv_usec / 1000);
}

void	print_situation(char c, t_philo *philo)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time_ms() - philo->data->time_launch;
	if (c == 'f')
		printf("%lu %d has taken a fork\n", timestamp, philo->index);
	if (c == 'e')
		printf("%lu %d is eating\n", timestamp, philo->index);
	if (c == 's')
		printf("%lu %d is sleeping\n", timestamp, philo->index);
	if (c == 't')
		printf("%lu %d is thinking\n", timestamp, philo->index);
	// if (c == 'd')
	// 	printf("%lu %d died\n", timestamp, philo->index);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*routine_philo(void *p)
{
	t_philo			*philo;
	unsigned int	second_fork;

	philo = p;
	while (1)
	{	
		second_fork = philo->index % philo->data->nbr_philo + 1;
		pthread_mutex_lock(&philo->fork);
		print_situation('f', philo);
		pthread_mutex_lock(&philo->data->philos[second_fork - 1].fork);
		print_situation('f', philo);
		print_situation('e', philo);
		philo->last_meal = get_time_ms() - philo->data->time_launch;
		usleep(1000 * philo->data->eat);
		philo->data->nbr_eat--;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->data->philos[second_fork - 1].fork);
		print_situation('s', philo);
		usleep(1000 * philo->data->sleep);
		print_situation('t', philo);
	}
	return (0);
}

void	fill_philos(t_data *data)
{
	unsigned int	i;

	data->philos = malloc(data->nbr_philo * sizeof(t_philo));
	i = 0;
	data->time_launch = get_time_ms();
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].index = i + 1;
		data->philos[i].last_meal = get_time_ms();
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			exit(1);
		if (pthread_create(&data->philos[i].thread, NULL, routine_philo, &data->philos[i]))
			exit(1);
		i = i + 2;
	}
	usleep(100);
	i = 1;
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].index = i + 1;
		data->philos[i].last_meal = get_time_ms();
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			exit(1);
		if (pthread_create(&data->philos[i].thread, NULL, routine_philo, &data->philos[i]))
			exit(1);
		i = i + 2;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		error_arguments();
	data = fill_argument(ac, av);
	if (check_arguments(data))
	{
		free(data);
		error_arguments();
	}
	fill_philos(data);
	while (1)
	{
		//supervisor
	}
	// cleanup();
	// a ne pas oublier de remplacer exit par return, it's forbidden
}
