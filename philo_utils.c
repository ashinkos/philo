/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:46:21 by aaouni            #+#    #+#             */
/*   Updated: 2022/10/02 19:46:51 by aaouni           ###   ########.fr       */
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

void	my_sleep(unsigned int tms)
{
	unsigned long	old_time;

	old_time = get_time_ms();
	usleep(tms - 30000);
	while (get_time_ms() < old_time + tms / 1000)
		;
}
