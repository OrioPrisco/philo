/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/17 11:51:07 by OrioPrisc        ###   ########.fr       */
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
		printf("%zu\n", i);
		pthread_mutex_init(mutexes + i++, NULL);
	}
	i = 0;
	while (i < params->numbr_philo)
	{
		philos[i].data = (t_philo_data){
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
	philos[params->numbr_philo - 1].data.left_fork = mutexes + 0;
}

void	*do_nothing(void *foo)
{
	t_philo_data	*philo;

	philo = foo;
	pthread_mutex_lock(philo->shared_data_lock);
	philo->shared_data->hungry_philos -= 1;
	if (philo->shared_data->hungry_philos == 0)
	{
		philo->shared_data->should_stop = 1;
		pthread_mutex_unlock(philo->shared_data_lock);
		return (NULL);
	}
	pthread_mutex_unlock(philo->shared_data_lock);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(philo->shared_data_lock);
		if (philo->shared_data->should_stop == 1)
			return (pthread_mutex_unlock(philo->shared_data_lock), NULL);
		pthread_mutex_unlock(philo->shared_data_lock);
	}
}

void	join_philos(t_philo *philos, size_t to_join, t_shared_data *shared,
	pthread_mutex_t *shared_data_mutex)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(shared_data_mutex);
	shared->should_stop = 1;
	pthread_mutex_unlock(shared_data_mutex);
	while (i < to_join)
		pthread_join(philos[i++].thread, NULL);
	while (i < to_join)
		pthread_mutex_destroy(philos[i].data.left_fork);
	pthread_mutex_destroy(shared_data_mutex);
}

_Bool	launch_philos(t_philo *philos, size_t philo_num, t_shared_data *shared,
	pthread_mutex_t *shared_data_mutex)
{
	size_t	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&philos[i].thread, NULL, do_nothing,
				&philos[i].data))
			return (join_philos(philos, i, shared, shared_data_mutex), 1);
		i++;
	}
	return (0);
}
