/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/29 03:03:08 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_string(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (is_valid_string(str))
		return (0);
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10 + (str[i++] - '0'));
	return (nb);
}

t_data	*fill_argument(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (data);
	if (ac > 4)
	{
		data->nbr_philo = ft_atoi(av[1]);
		data->die = ft_atoi(av[2]);
		data->eat = ft_atoi(av[3]);
		data->sleep = ft_atoi(av[4]);
		data->nbr_eat = -1;
	}
	if (ac == 6)
		data->nbr_eat = ft_atoi(av[5]);
	return (data);
}

void	print_data(t_data *data)
{
	printf("number of philo : %d \n", data->nbr_philo);
	printf("time to die : %d \n", data->die);
	printf("time to eat : %d \n", data->eat);
	printf("time to sleep : %d \n", data->sleep);
	printf("number of time to eat : %d \n", data->nbr_eat);
}

void	error_arguments(void)
{
	printf("arguments are invalid\n");
	exit(1);
}

int	check_arguments(t_data *data)
{
	if (data->nbr_philo == 0)
		return (1);
	if (data->nbr_eat == 0)
		return (1);
	if (data->die < 60)
		return (1);
	if (data->eat < 60)
		return (1);
	if (data->sleep < 60)
		return (1);
	return (0);
}

unsigned long get_microsec ()
{
	struct timeval	rtk;

	gettimeofday(&rtk, NULL);
	return (rtk.tv_sec * 1000 + rtk.tv_usec);
}

void	*routine(void *p)
{
	t_philo *	philo;

	philo = p;
	while (1)
	{	
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
			exit (1);
		printf(" philo %d\n", data->philos[i].index);

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
		error_arguments();
	fill_philos(data);
	while(1)
	{
		
	}
	// clea¬nup();
}
