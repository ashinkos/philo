/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 05:04:19 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/02 19:49:54 by aaouni           ###   ########.fr       */
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
		if (pthread_mutex_init(&data->print_mutex, NULL))
			exit(1);
		data->nbr_eat = -1;
		data->philos_eat = -1;
	}
	if (ac == 6)
	{
		data->nbr_eat = ft_atoi(av[5]);
		data->philos_eat = ft_atoi(av[1]);
	}
	return (data);
}

int	error_arguments(void)
{
	printf("arguments are invalid\n");
	return (1);
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

void	print_data(t_data *data)
{
	printf("number of philo : %d \n", data->nbr_philo);
	printf("time to die : %d \n", data->die);
	printf("time to eat : %d \n", data->eat);
	printf("time to sleep : %d \n", data->sleep);
	printf("number of time to eat : %d \n", data->nbr_eat);
}
