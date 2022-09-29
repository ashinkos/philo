/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/29 01:29:38 by aaouni           ###   ########.fr       */
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

t_plist	*fill_argument(int ac, char **av)
{
	t_plist	*lst;

	lst = malloc(sizeof(t_plist));
	if (!lst)
		return (lst);
	if (ac > 4)
	{
		lst->nbr_philo = ft_atoi(av[1]);
		lst->die = ft_atoi(av[2]);
		lst->eat = ft_atoi(av[3]);
		lst->sleep = ft_atoi(av[4]);
		lst->nbr_eat = -1;
	}
	if (ac == 6)
		lst->nbr_eat = ft_atoi(av[5]);
	return (lst);
}

void	print_lst(t_plist *lst)
{
	printf("number of philo : %d \n", lst->nbr_philo);
	printf("time to die : %d \n", lst->die);
	printf("time to eat : %d \n", lst->eat);
	printf("time to sleep : %d \n", lst->sleep);
	printf("number of time to eat : %d \n", lst->nbr_eat);
}

void	error_arguments(void)
{
	printf("nombre of argument is invalid\n");
	exit(1);
}

int	check_arguments(t_plist *lst)
{
	if (lst->nbr_philo == 0)
		return (1);
	if (lst->nbr_eat == 0)
		return (1);
	if (lst->die < 60)
		return (1);
	if (lst->eat < 60)
		return (1);
	if (lst->sleep < 60)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_plist	*lst;

	lst = NULL;
	if (ac < 5 || ac > 6)
		error_arguments();
	lst = fill_argument(ac, av);
	print_lst(lst);
	if (check_arguments(lst))
		error_arguments();
	av[0] = av[0]++;
}
