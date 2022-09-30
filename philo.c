/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/30 03:27:46 by aaouni           ###   ########.fr       */
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
	if (c == 'f')
	{
		timestamp = get_time_ms() - philo->data->time_launch;
		printf("%lu %d has taken a fork", timestamp, philo->index);
	}
	if (c == 'e')
	{
		timestamp = get_time_ms() - philo->data->time_launch;
		printf("%lu %d is eating", timestamp, philo->index);
	}
	if (c == 's')
	{
		timestamp = get_time_ms() - philo->data->time_launch;
		printf("%lu %d is sleeping", timestamp, philo->index);
	}
	if (c == 't')
	{
		timestamp = get_time_ms() - philo->data->time_launch;
		printf("%lu %d is thinking", timestamp, philo->index);
	}
	if (c == 'd')
	{
		timestamp = get_time_ms() - philo->data->time_launch;
		printf("%lu %d died", timestamp, philo->index);
	}
}

void	*routine_philo(void *p)
{
	t_philo			*philo;
	unsigned int	second_fork;

	philo = p;
	while (1)
	{	
		second_fork = philo->index % philo->data->nbr_philo + 1;
		// // usleep(2e6);
		// sleep (10);
		// printf("philo number %d : my seconde fork is %d \n", philo->index, second_fork);
		pthread_mutex_lock(&philo->fork);
		print_situation('f', philo);
		pthread_mutex_lock(&philo->data->philos[second_fork - 1].fork);
		print_situation('f', philo);
		print_situation('e', philo);
		usleep(1000 * philo->data->eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->data->philos + second_fork);
		
	}
	return (0);
}
// next fork_index  = (fork_index ) % n_philo + 1

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
		// printf(" philo %d\n", data->philos[i].index);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		error_arguments();
	data = fill_argument(ac, av);
	print_data(data);
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
}
