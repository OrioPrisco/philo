/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:36:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/12 12:08:28 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "philo.h"
#include <stdio.h>

_Bool	check_death(const t_params *params, t_philo_monitor *philos, t_ms ms)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		if (philos[i].last_eat + params->time_to_die < ms)
			return (kill_philo(i, ms), 1);
		i++;
	}
	return (0);
}

_Bool	check_end(const t_params *params, t_philo_monitor *philos)
{
	size_t	i;

	if (params->binge_party)
		return (0);
	i = 0;
	while (i < params->numbr_philo)
	{
		if (philos[i].eats < params->number_eats)
			return (0);
		i++;
	}
	if (DEBUG)
		printf("Everyone ate\n");
	return (1);
}

void	update_philo(const t_params *params, t_philo_monitor *philos,
			t_message *message)
{
	if (message->action == EAT
		&& philos[message->id].last_eat + params->time_to_die
		>= message->ms)
		philos[message->id].last_eat = message->ms;
	if (!params->binge_party && message->action == SLEEP)
		philos[message->id].eats++;
}

void	kill_philo(size_t id, t_ms ms)
{
	t_message	message;

	message = (t_message){ms, id, DIE};
	print_message(&message);
}
