/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:32:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 16:53:18 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>

void	philo_eat(t_philo_data *philo)
{
	sem_wait(philo->forks);
	philo_say(philo);
	sem_wait(philo->forks);
	philo_say(philo);
	philo_say(philo);
	wait_ms(philo->params->time_to_eat);
}

void	philo_sleep(t_philo_data *philo)
{
	philo_say(philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
	wait_ms(philo->params->time_to_slp);
}

void	philo_think(t_philo_data *philo)
{
	philo_say(philo);
	if (philo->params->time_to_eat > philo->params->time_to_slp)
		wait_ms(philo->params->time_to_eat - philo->params->time_to_slp);
	if (philo->params->numbr_philo % 2)
		wait_ms(philo->params->time_to_eat);
}

void	philo_main(t_philo_data *philo)
{
	if (philo->params->numbr_philo == 1)
		return ;
	if (philo->philo_id % 2)
		wait_ms(philo->params->time_to_eat);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
