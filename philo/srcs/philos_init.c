/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/02 16:50:04 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
	const t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo + 2)
	{
		pthread_mutex_init(mutexes + i++, NULL);
	}
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
	philos[params->numbr_philo - 1].data.right_fork.mutex = mutexes + 0;
}

void	join_philos(t_philo *philos, size_t to_join, t_shared_data *shared)
{
	size_t	i;

	i = 0;
	while (i < to_join)
		pthread_join(philos[i++].thread, NULL);
	while (i < to_join)
		pthread_mutex_destroy(philos[i].data.left_fork.mutex);
	pthread_mutex_destroy(shared->lock);
}

_Bool	launch_philos(t_philo *philos, size_t philo_num, t_shared_data *shared)
{
	size_t	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_main,
				&philos[i].data))
		{
			pthread_mutex_lock(shared->lock);
			shared->should_stop = 1;
			pthread_mutex_unlock(shared->lock);
			return (join_philos(philos, i, shared), 1);
		}
		i++;
	}
	return (0);
}
