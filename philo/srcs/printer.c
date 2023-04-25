/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 14:06:57 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "vector.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "philo.h"

//TODO check vector_append return
void	queue_action(t_queue_action action, t_message *opt)
{
	static t_vector			queue;
	static pthread_mutex_t	mutex;

	if (action == INIT)
		pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	if (action == POP && !queue.size)
		opt->action = ERROR;
	if (action == POP && queue.size)
		*opt = vector_pop(&queue, 0);
	if (action == PUSH)
		vector_append_elems(&queue, opt, 1);
	if (action == FREE)
	{
		vector_clear(&queue);
		pthread_mutex_destroy(&mutex);
		return ;
	}
	pthread_mutex_unlock(&mutex);
}

static const char	*g_actions[] = {
	"has taken a fork",
	"is sleeping",
	"is eating",
	"is thinking",
	"died",
};

void	kill_philo(size_t id, t_ms ms, t_params *params)
{
	printf("%04llu %zu %s\n", ms,
		id, g_actions[DIE]);
	pthread_mutex_lock(params->shared->lock);
	params->shared->should_stop = 1;
	pthread_mutex_unlock(params->shared->lock);
}

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

_Bool	print_messages(t_params *params, t_philo_monitor *philos)
{
	t_message			message;

	usleep(500);
	queue_action(POP, &message);
	while (message.action != ERROR)
	{
		printf("%04llu %zu %s\n", message.ms,
			message.id, g_actions[message.action]);
		if (message.action == EAT)
		{
			philos[message.id].last_eat = message.ms + params->time_to_eat;
			philos[message.id].eats++;
		}
		queue_action(POP, &message);
		if (message.action == DIE)
			return (1);
	}
	return (0);
}

//TODO : check should_stop
void	*printer_main(void *foo)
{
	t_params			*params;
	t_philo_monitor		*philos;

	params = foo;
	philos = ft_calloc(params->numbr_philo, sizeof(*philos));
	if (!philos)
		return (NULL);
	while (1)
	{
		if (print_messages(params, philos) || check_death(params, philos))
			return (free(philos), NULL);
	}
}
