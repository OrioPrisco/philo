/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:35:05 by orio              #+#    #+#             */
/*   Updated: 2023/04/21 16:04:46 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "shared_data.h"
#include "philo.h"
#include <stdio.h>

static const char	*g_actions[] = {
	"has taken a fork",
	"is sleeping",
	"is eating",
	"is thinking",
	"died",
};

//issue : we might die while trying to take the lock
_Bool	philo_say(t_philo_data *philo, t_action action, _Bool take_lock)
{
	_Bool	should_stop;

	if (take_lock)
		pthread_mutex_lock(philo->shared_data_lock);
	should_stop = philo->shared_data->should_stop;
	if (!should_stop)
		printf("%llu %zu %s\n", get_ms_since(philo->params->program_start),
			philo->philo_id, g_actions[action]);
	if (take_lock)
		pthread_mutex_unlock(philo->shared_data_lock);
	return (should_stop);
}

_Bool	is_dead(t_philo_data *philo)
{
	t_ms	ms;

	ms = get_ms_since(philo->last_eat);
	if (ms > philo->params->time_to_die)
		return (philo_die(philo), 1);
	return (0);
}

void	take_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
	fork->held = 1;
}

void	lay_fork(t_fork *fork)
{
	if (!fork->held)
		return ;
	pthread_mutex_unlock(fork->mutex);
	fork->held = 0;
}

_Bool	philo_wait_ms(t_philo_data *philo, t_ms ms)
{
	t_ms	begin;

	begin = get_ms();
	while (get_ms_since(begin) < ms)
	{
		if (is_dead(philo))
			return (1);
	}
	return (0);
}
