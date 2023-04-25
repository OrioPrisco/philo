/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:35:05 by orio              #+#    #+#             */
/*   Updated: 2023/04/25 15:47:45 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>
#include "printer.h"

//issue : we might die while trying to take the lock
_Bool	philo_say(t_philo_data *philo, t_action action, _Bool take_lock)
{
	_Bool		should_stop;
	t_message	message;
	t_ms		timestamp;

	timestamp = get_ms_since(philo->params->program_start);
	if (take_lock)
		pthread_mutex_lock(philo->shared_data->lock);
	should_stop = philo->shared_data->should_stop;
	if (!should_stop)
	{
		message = (t_message){timestamp, philo->philo_id, action};
		queue_action(PUSH, &message);
	}
	if (take_lock)
		pthread_mutex_unlock(philo->shared_data->lock);
	return (should_stop);
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
