/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/02 18:02:05 by OrioPrisc        ###   ########.fr       */
/*   Updated: 2023/04/26 20:18:14 by orio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "vector.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "philo.h"

static const char	*g_actions[] = {
	"has taken a fork",
	"is sleeping",
	"is eating",
	"is thinking",
	"died",
};

void	print_message(t_message *message)
{
	printf("%04llu %zu %s\n", message->ms, message->id,
		g_actions[message->action]);
}

_Bool	print_messages(const t_params *params, t_philo_monitor *philos)
{
	t_message			message;

	usleep(500);
	pthread_mutex_lock(params->shared->queue_lock);
	while (params->shared->queue.size)
	{
		message = vector_pop(&params->shared->queue, 0);
		pthread_mutex_unlock(params->shared->queue_lock);
		print_message(&message);
		update_philo(params, philos, &message);
		if (check_death(params, philos, message.ms)
			|| check_end(params, philos))
		{
			pthread_mutex_unlock(params->shared->queue_lock);
			return (1);
		}
		pthread_mutex_lock(params->shared->queue_lock);
	}
	pthread_mutex_unlock(params->shared->queue_lock);
	return (0);
}

void	*end(const t_params *params, t_philo_monitor *philos)
{
	pthread_mutex_lock(params->shared->lock);
	params->shared->should_stop = 1;
	pthread_mutex_unlock(params->shared->lock);
	return (free(philos), NULL);
}

void	*printer_main(void *foo)
{
	t_params			*params;
	t_philo_monitor		*philos;

	params = foo;
	params->program_start = get_ms() + 100;
	pthread_mutex_unlock(params->shared->lock);
	while (get_ms() < params->program_start)
		usleep(1);
	philos = ft_calloc(params->numbr_philo, sizeof(*philos));
	if (!philos)
		return (end(params, philos));
	while (1)
	{
		if (print_messages(params, philos)
			|| check_death(params, philos, get_ms_since(params->program_start))
			|| check_end(params, philos))
			return (end(params, philos));
	}
}
