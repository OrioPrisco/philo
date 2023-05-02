/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:35:05 by orio              #+#    #+#             */
/*   Updated: 2023/05/02 16:59:55 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>
#include "printer.h"

_Bool	philo_say(const t_philo_data *philo, t_action action)
{
	t_message	message;
	t_ms		timestamp;
	_Bool		err;

	pthread_mutex_lock(philo->params->shared->queue_lock);
	timestamp = get_ms_since(philo->params->program_start);
	message = (t_message){timestamp, philo->philo_id, action};
	err = vector_append(&philo->params->shared->queue, message);
	pthread_mutex_unlock(philo->params->shared->queue_lock);
	return (err);
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
