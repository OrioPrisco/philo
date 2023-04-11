/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/11 18:57:48 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <pthread.h>

void	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
	t_shared_data *data, const t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		philos[i] = (t_philo){
			params,
			i,
			params->number_eats,
			mutexes + i,
			mutexes + i + 1,
			mutexes + params->numbr_philo,
			data
		};
		i++;
	}
	philos[params->numbr_philo - 1].left_fork = mutexes + 0;
}

void	*do_nothing(void *foo)
{
	(void)foo;
	while (1)
		;
}

size_t	launch_philos(t_philo *philos, pthread_t *threads,
			size_t number_philos)
{
	size_t	i;

	i = 0;
	while (i < number_philos)
	{
		if (pthread_create(threads + i, NULL, do_nothing, philos + i))
			return (i);
		i++;
	}
	return (number_philos);
}
