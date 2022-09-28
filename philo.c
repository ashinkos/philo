/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:46:47 by aaouni            #+#    #+#             */
/*   Updated: 2022/09/28 21:49:29 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		nb;
	int		sign;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10 + (str[i++] - '0'));
	return (sign * nb);
}

t_plist *fill_argument(int ac, char **av)
{
    t_plist *lst;
    
    lst = malloc(sizeof(t_plist));
    if (!lst)
        return (lst);
    if (ac > 4)
    {
        lst->nbr_philo = ft_atoi(av[1]);
        lst->die = ft_atoi(av[2]);
        lst->eat = ft_atoi(av[3]);
        lst->sleep = ft_atoi(av[4]);
        lst->nbr_eat = 0;
    }
    if (ac == 6)
        lst->nbr_eat = ft_atoi(av[5]);
    return (lst);
}

void    print_lst(t_plist *lst)
{
    printf("number of philo : %d \n", lst->nbr_philo);
    printf("time to die : %d \n", lst->die);
    printf("time to eat : %d \n", lst->eat);
    printf("time to sleep : %d \n", lst->sleep);
    printf("number of time to eat : %d \n", lst->nbr_eat);
}

int main(int ac, char **av)
{
    t_plist *lst;
    
    lst = NULL;
    
    if (ac < 5 || ac > 6)
    {
        printf("nombre of argument is invalid\n");
        exit(1);
    }
    lst = fill_argument(ac, av);
    print_lst(lst);
    av[0] = av[0]++;
}