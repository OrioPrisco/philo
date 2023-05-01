/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 16:30:32 by OrioPrisc        ###   ########.fr       */
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
#include "philo_sem.h"

void	queue_action(t_queue_action action, t_message *opt)
{
	static t_vector			queue;
	static sem_t			*mutex;

	if (action == INIT)
		my_sem_init(&mutex, 1);
	sem_wait(mutex);
	if (action == POP && !queue.size)
		opt->action = ERROR;
	if (action == POP && queue.size)
		*opt = vector_pop(&queue, 0);
	if (action == PUSH)
	{
		if (vector_append_elems(&queue, opt, 1))
			opt->action = ERROR;
	}
	if (action == FREE)
	{
		vector_clear(&queue);
		my_sem_close(mutex);
		return ;
	}
	sem_post(mutex);
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

_Bool	print_messages(const t_params *params, t_philo_monitor *philos)
{
	t_message			message;

	usleep(500);
	queue_action(POP, &message);
	while (message.action != ERROR)
	{
		print_message(&message);
		update_philo(params, philos, &message);
		if (check_death(params, philos, message.ms)
			|| check_end(params, philos))
			return (1);
		queue_action(POP, &message);
		if (message.action == DIE)
			return (1);
	}
	return (0);
}

void	*end(const t_params *params, t_philo_monitor *philos)
{
	sem_post(params->semaphores.stop_sem);
	return (free(philos), NULL);
}

void	*printer_main(void *foo)
{
	const t_params		*params;
	t_philo_monitor		*philos;

	params = foo;
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
