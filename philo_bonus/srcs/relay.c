/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:03:29 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/10 15:16:57 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "relay.h"
#include "philo.h"
#include "libft.h"
#include "philo_sem.h"
#include "philos.h"
#include "printer.h"
#include "vector.h"
#include <unistd.h>

static const t_action	g_actions[] = {
	TAKE_FORK,
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
};

void	*relay_main(void *data)
{
	t_relay		*relay;
	size_t		step;
	_Bool		run;

	run = 1;
	step = 0;
	relay = data;
	while (get_ms() < relay->params->program_start)
		usleep(1);
	while (run)
	{
		sem_wait(relay->philo_sem1);
		sem_wait(relay->params->semaphores.queue_sem);
		vector_append(relay->queue,
			(t_message){get_ms_since(relay->params->program_start),
			relay->id, g_actions[step]});
		sem_post(relay->params->semaphores.queue_sem);
		sem_post(relay->philo_sem2);
		step++;
		step %= sizeof(g_actions) / sizeof(g_actions[0]);
		sem_wait(relay->params->semaphores.stop_sem);
		run = !relay->params->stop;
		sem_post(relay->params->semaphores.stop_sem);
	}
	return (NULL);
}

//TODO properly init sems
void	destroy_relays(t_relay *relays, size_t to_destroy)
{
	size_t	i;

	i = 0;
	while (i < to_destroy)
	{
		my_sem_close(relays[i].philo_sem1);
		my_sem_close(relays[i].philo_sem2);
		i++;
	}
}

_Bool	populate_relays(t_relay *relays, const t_params *params, t_vector *vec)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		if (my_sem_init(&relays[i].philo_sem1, 0)
			|| my_sem_init(&relays[i].philo_sem2, 0))
			return (destroy_relays(relays, i), 1);
		relays[i].params = params;
		relays[i].queue = vec;
		relays[i].id = i;
		i++;
	}
	return (0);
}

_Bool	launch_relays(t_relay *relays, t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		if (pthread_create(&relays[i].thread, NULL, relay_main,
				&relays[i]))
		{
			sem_wait(params->semaphores.stop_sem);
			params->stop = 1;
			sem_wait(params->semaphores.stop_sem);
			return (join_relays(relays, i), 1);
		}
		i++;
	}
	return (0);
}

void	join_relays(t_relay *relays, size_t nb_relays)
{
	size_t	i;

	i = 0;
	while (i < nb_relays)
	{
		sem_post(relays[i].philo_sem1);
		pthread_join(relays[i++].thread, NULL);
	}
}
