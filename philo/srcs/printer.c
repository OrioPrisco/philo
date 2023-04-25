/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 16:49:28 by OrioPrisc        ###   ########.fr       */
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

void	print_message(t_message *message)
{
	printf("%04llu %zu %s\n", message->ms, message->id,
		g_actions[message->action]);
}

_Bool	print_messages(t_params *params, t_philo_monitor *philos)
{
	t_message			message;

	usleep(500);
	queue_action(POP, &message);
	while (message.action != ERROR)
	{
		print_message(&message);
		update_philo(params, philos, &message);
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
