/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:36:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 17:06:37 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "philo.h"
#include <stdio.h>

_Bool	check_death(t_params *params, t_philo_monitor *philos)
{
	size_t	i;
	t_ms	ms;

	ms = get_ms_since(params->program_start);
	i = 0;
	while (i < params->numbr_philo)
	{
		if (philos[i].last_eat + params->time_to_die < ms)
			return (kill_philo(i, ms, params), 1);
		i++;
	}
	return (0);
}

void	update_philo(t_params *params, t_philo_monitor *philos,
			t_message *message)
{
	if (message->action != EAT)
		return ;
	if (philos[message->id].last_eat + params->time_to_die
		< message->ms + params->time_to_eat)
		return ;
	philos[message->id].last_eat = message->ms + params->time_to_eat;
	philos[message->id].eats++;
}

void	kill_philo(size_t id, t_ms ms, t_params *params)
{
	t_message	message;

	message = (t_message){ms, id, DIE};
	print_message(&message);
	pthread_mutex_lock(params->shared->lock);
	params->shared->should_stop = 1;
	pthread_mutex_unlock(params->shared->lock);
}
