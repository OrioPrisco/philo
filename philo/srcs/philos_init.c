/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/11 17:25:39 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	destroy_philos(t_philo *philos, size_t to_destroy)
{
	size_t	i;

	i = 0;
	while (i < to_destroy)
		pthread_mutex_destroy(philos[i++].data.left_fork.mutex);
}

void	destroy_shared_mutexes(t_shared_data *shared)
{
	pthread_mutex_destroy(shared->lock);
	pthread_mutex_destroy(shared->queue_lock);
}

_Bool	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
	const t_params *params)
{
	size_t	i;

	if (pthread_mutex_init(mutexes + params->numbr_philo, NULL)
		|| pthread_mutex_init(mutexes + params->numbr_philo, NULL))
		return (destroy_shared_mutexes(params->shared), 1);
	i = 0;
	while (i < params->numbr_philo)
	{
		philos[i].data = (t_philo_data){
			params,
			i,
		{mutexes + i, 0},
		{mutexes + i + 1, 0},
		};
		i++;
	}
	i = 0;
	while (i < params->numbr_philo + 2)
	{
		if (pthread_mutex_init(mutexes + i++, NULL))
			return (destroy_shared_mutexes(params->shared),
				destroy_philos(philos, i), 1);
	}
	philos[params->numbr_philo - 1].data.right_fork.mutex = mutexes + 0;
	return (0);
}

void	join_philos(t_philo *philos, size_t to_join, t_shared_data *shared)
{
	size_t	i;

	i = 0;
	while (i < to_join)
		pthread_join(philos[i++].thread, NULL);
	destroy_philos(philos, to_join);
	destroy_shared_mutexes(shared);
}

_Bool	launch_philos(t_philo *philos, size_t philo_num, t_shared_data *shared)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(shared->lock);
	while (i < philo_num)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_main,
				&philos[i].data))
		{
			shared->should_stop = 1;
			pthread_mutex_unlock(shared->lock);
			return (join_philos(philos, i, shared), 1);
		}
		i++;
	}
	return (0);
}
