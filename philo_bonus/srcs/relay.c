/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:03:29 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 18:19:48 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "relay.h"
#include "philo.h"
#include "libft.h"
#include "philo_sem.h"
#include "philos.h"
#include "printer.h"

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
	t_message	message;

	step = 0;
	relay = data;
	while (1)
	{
		sem_wait(relay->philo_sem1);
		message = (t_message){get_ms_since(relay->params->program_start),
			relay->id, g_actions[step]};
		queue_action(PUSH, &message);
		sem_post(relay->philo_sem2);
		step++;
		step %= sizeof(g_actions) / sizeof(g_actions[0]);
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

_Bool	populate_relays(t_relay *relays, const t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		if (my_sem_init(&relays[i].philo_sem1, 0)
			|| my_sem_init(&relays[i].philo_sem2, 0))
			return (destroy_relays(relays, i), 1);
		i++;
	}
	return (0);
}

_Bool	launch_relays(t_relay *relays, const t_params *params)
{
	size_t	i;

	i = 0;
	while (i < params->numbr_philo)
	{
		if (pthread_create(&relays[i].thread, NULL, relay_main,
				&relays[i]))
		{
			sem_post(params->semaphores.stop_sem);
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
		pthread_join(relays[i++].thread, NULL);
	}
}
