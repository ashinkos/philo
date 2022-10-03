/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:46:21 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/03 20:28:25 by aaouni           ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	my_sleep(unsigned int tms)
{
	unsigned long	old_time;

	old_time = get_time_ms();
	usleep(tms - 30000);
	while (get_time_ms() < old_time + tms / 1000)
		;
}

int	one_philo(t_data *data)
{
	if (data->nbr_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		my_sleep(1000 * (data->die));
		printf("%d 1 died\n", data->die);
		return (1);
	}
	return (0);
}

void	print_fork_eat(t_philo *philo)
{
	print_situation('f', philo);
	print_situation('e', philo);
}
