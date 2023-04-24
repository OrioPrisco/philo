/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 14:12:34 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printer.h"
#include "vector.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

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

void	*printer_main(void *_)
{
	t_message	message;

	(void)_;
	while (1)
	{
		usleep(1000);
		queue_action(POP, &message);
		if (message.action != ERROR)
			printf("%04llu %zu %s\n", message.ms,
				message.id, g_actions[message.action]);
		if (message.action == DIE)
			return (NULL);
	}
}
