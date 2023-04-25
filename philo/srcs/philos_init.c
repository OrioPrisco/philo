/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 14:54:34 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
	t_shared_data *data, const t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo + 1)
	{
		pthread_mutex_init(mutexes + i++, NULL);
	}
	i = 0;
	while (i < params->numbr_philo)
	{
		philos[i].data = (t_philo_data){
			params,
			i,
			params->number_eats,
		{mutexes + i, 0},
		{mutexes + i + 1, 0},
			data,
			params->program_start,
		};
		i++;
	}
	philos[params->numbr_philo - 1].data.right_fork.mutex = mutexes + 0;
}

void	join_philos(t_philo *philos, size_t to_join,
	pthread_mutex_t *shared_data_mutex)
{
	size_t	i;

	i = 0;
	while (i < to_join)
		pthread_join(philos[i++].thread, NULL);
	while (i < to_join)
		pthread_mutex_destroy(philos[i].data.left_fork.mutex);
	pthread_mutex_destroy(shared_data_mutex);
}

_Bool	launch_philos(t_philo *philos, size_t philo_num, t_shared_data *shared,
	pthread_mutex_t *shared_data_mutex)
{
	size_t	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_main,
				&philos[i].data))
		{
			pthread_mutex_lock(shared_data_mutex);
			shared->should_stop = 1;
			pthread_mutex_unlock(shared_data_mutex);
			return (join_philos(philos, i, shared_data_mutex), 1);
		}
		i++;
	}
	return (0);
}
