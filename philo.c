/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/29 05:34:43 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_microsec(void)
{
	struct timeval	rtk;

	gettimeofday(&rtk, NULL);
	return (rtk.tv_sec * 1000 + rtk.tv_usec);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = p;
	while (1)
	{	printf("--------------------------\n");
		usleep(2e6);
		printf("hello from philo numbre %d\n", philo->index);
	}
	return (0);
}
// next fork_index  = (fork_index + 1) % n_philo

void	fill_philos(t_data *data)
{
	unsigned int	i;

	data->philos = malloc(data->nbr_philo * sizeof(t_philo));
	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].index = i;
		data->philos[i].last_meal = get_microsec();
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]))
			exit(1);
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
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
