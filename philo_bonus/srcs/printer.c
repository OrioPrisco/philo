/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/05 18:05:26 by OrioPrisc        ###   ########.fr       */
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

_Bool	print_messages(const t_params *params, t_philo_monitor *philos,
			t_vector *vec)
{
	t_message			message;

	usleep(500);
	sem_wait(params->semaphores.queue_sem);
	while (vec->size)
	{
		message = vector_pop(vec, 0);
		sem_post(params->semaphores.queue_sem);
		print_message(&message);
		update_philo(params, philos, &message);
		if (check_death(params, philos, message.ms)
			|| check_end(params, philos))
			return (1);
		sem_wait(params->semaphores.queue_sem);
	}
	sem_post(params->semaphores.queue_sem);
	return (0);
}

void	end(t_params *params, t_philo_monitor *philos)
{
	sem_wait(params->semaphores.stop_sem);
	params->stop = 1;
	sem_post(params->semaphores.stop_sem);
	free(philos);
}

void	printer_main(t_params *params, t_vector *vec)
{
	t_philo_monitor		*philos;

	while (get_ms() < params->program_start)
		usleep(1);
	philos = ft_calloc(params->numbr_philo, sizeof(*philos));
	if (!philos)
		return (end(params, philos));
	while (1)
	{
		if (print_messages(params, philos, vec)
			|| check_death(params, philos, get_ms_since(params->program_start))
			|| check_end(params, philos))
			return (end(params, philos));
	}
}
