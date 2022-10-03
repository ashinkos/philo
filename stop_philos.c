/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:05:54 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/03 20:51:22 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_nbr_eat(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&data->philos[i].n_eat_mutex);
		if (data->philos[i].nbr_eat > 0)
		{
			pthread_mutex_unlock(&data->philos[i].n_eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].n_eat_mutex);
		i++;
	}
	usleep (500);
	return (1);
}

int	check_philo_died(t_data *data, int i)
{
	unsigned long	timestamp;

	if (get_time_ms() - data->time_launch
		> data->die + data->philos[i].last_meal)
	{
		pthread_mutex_lock(&data->print_mutex);
		timestamp = get_time_ms() - data->time_launch;
		printf("%lu %d died\n", timestamp, data->philos[i].index);
		return (1);
	}
	return (0);
}

int	stop_philo_died(t_data *data)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = data->nbr_philo - 1;
	while (i < data->nbr_philo / 2 && j >= data->nbr_philo / 2)
	{
		pthread_mutex_lock(&data->philos[i].l_meal_mutex);
		if (check_philo_died(data, i))
			return (1);
		pthread_mutex_unlock(&data->philos[i].l_meal_mutex);
		pthread_mutex_lock(&data->philos[j].l_meal_mutex);
		if (check_philo_died(data, j))
			return (1);
		pthread_mutex_unlock(&data->philos[j].l_meal_mutex);
		i++;
		j--;
	}
	return (0);
}

int	init_mutex_fork(t_data *data)
{
	unsigned int	j;

	j = 0;
	while (j < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->philos[j].fork, NULL))
			return (1);
		j++;
	}
	return (0);
}
