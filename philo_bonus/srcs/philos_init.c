/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:30:09 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/05 18:24:39 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "relay.h"
#include <stdlib.h>

void	kill_philos(t_philo *philos, size_t to_join)
{
	size_t	i;

	i = 0;
	while (i < to_join)
		kill(philos[i++], SIGKILL);
}

void	philo_startup(const t_params *params, t_relay *relays, t_philo *philos,
			size_t id)
{
	t_philo_data	philo;

	philo = (t_philo_data)
	{params, id, params->semaphores.forks, relays[id].philo_sem1,
		relays[id].philo_sem2};
	relays[id].philo_sem1 = NULL;
	relays[id].philo_sem2 = NULL;
	destroy_relays(relays, params->numbr_philo);
	free(relays);
	free(philos);
	my_sem_close(params->semaphores.queue_sem);
	my_sem_close(params->semaphores.stop_sem);
	philo_main(&philo);
	my_sem_close(params->semaphores.forks);
	exit(0);
}

_Bool	launch_philos(t_philo *philos, const t_params *params, t_relay *relays)
{
	size_t	i;
	pid_t	pid;

	i = 0;
	while (i < params->numbr_philo)
	{
		pid = fork();
		if (pid == 0)
			philo_startup(params, relays, philos, i);
		philos[i] = pid;
		i++;
	}
	return (0);
}
