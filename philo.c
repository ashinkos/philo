/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/02 20:57:33 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_lock(&philo->l_meal_mutex);
		philo->last_meal = get_time_ms() - philo->data->time_launch;
		pthread_mutex_unlock(&philo->l_meal_mutex);
		// usleep(1000 * philo->data->eat);
		my_sleep(1000 * philo->data->eat);
		// pthread_mutex_lock(&philo->l_meal_mutex);
		pthread_mutex_lock(&philo->l_meal_mutex);
		philo->nbr_eat--;
		pthread_mutex_unlock(&philo->l_meal_mutex);
		// pthread_mutex_unlock(&philo->l_meal_mutex);
		// printf("last meal of %d is : %lu || number of eats needed is : %d\n", philo->index, philo->last_meal, philo->nbr_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->data->philos[second_fork - 1].fork);
		print_situation('s', philo);
		// usleep(1000 * philo->data->sleep);
		my_sleep(1000 * philo->data->sleep);
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
		data->philos[i].nbr_eat = data->nbr_eat;
		data->philos[i].last_meal = get_time_ms() - data->time_launch;
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			exit(1);
		if (pthread_mutex_init(&data->philos[i].l_meal_mutex, NULL))
			exit(1);
		if (pthread_create(&data->philos[i].thread, NULL, routine_philo, &data->philos[i]))
			exit(1);
		if (pthread_detach(data->philos[i].thread))
			exit(1);
		i = i + 2;
	}
	usleep(500);
	i = 1;
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].index = i + 1;
		data->philos[i].nbr_eat = data->nbr_eat / data->nbr_philo;
		data->philos[i].last_meal = get_time_ms();
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			exit(1);
		if (pthread_mutex_init(&data->philos[i].l_meal_mutex, NULL))
			exit(1);
		if (pthread_create(&data->philos[i].thread, NULL, routine_philo, &data->philos[i]))
			exit(1);
		if (pthread_detach(data->philos[i].thread))
			exit(1);
		i = i + 2;
	}
}

int	stop_nbr_eat(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->philos[i].l_meal_mutex);
		if (data->philos[i].nbr_eat > 0)
			return (0);
		pthread_mutex_unlock(&data->philos[i].l_meal_mutex);
		i++;
	}
	usleep (500);
	return (1);
}

int	stop_philo_died(t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	unsigned long	timestamp;

	i = 0;
	j = data->nbr_philo - 1;
	while (i < data->nbr_philo / 2 && j > data->nbr_philo / 2)
	{
		pthread_mutex_lock(&data->philos[i].l_meal_mutex);
		if (get_time_ms() - data->time_launch > data->die + data->philos[i].last_meal)
		{
			pthread_mutex_lock(&data->print_mutex);
			timestamp = get_time_ms() - data->time_launch;
			printf("%lu %lu died\n", timestamp, data->philos[i].last_meal);
			// printf("%lu %lu died\n", timestamp, get_time_ms());
			printf("%lu %d died\n", timestamp, data->philos[i].index);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].l_meal_mutex);
		pthread_mutex_lock(&data->philos[j].l_meal_mutex);
		if (get_time_ms() - data->time_launch > data->die + data->philos[j].last_meal)
		{	
			pthread_mutex_lock(&data->print_mutex);
			timestamp = get_time_ms() - data->time_launch;
			printf("%lu %lu died\n", timestamp, data->philos[j].last_meal);
			// printf("%lu %lu died\n", timestamp, get_time_ms());
			printf("%lu %d died\n", timestamp, data->philos[j].index);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[j].l_meal_mutex);
		i++;
		j--;
	}
	printf("herre\n");
	return (0);
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
		if (error_arguments())
			return (1);
	}
	print_data(data);
	fill_philos(data);
	while (1)
	{
		if (stop_philo_died(data))
			return (0);
		if (data->nbr_eat > 0 && stop_nbr_eat(data))
			return (0);
	}
	// cleanup();
	// a ne pas oublier de remplacer exit par return, it's forbidden
}
