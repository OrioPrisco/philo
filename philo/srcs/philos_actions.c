/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:32:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/28 12:41:57 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>

_Bool	philo_eat(t_philo_data *philo)
{
	if (philo->philo_id % 2)
		take_fork(&philo->left_fork);
	else
		take_fork(&philo->right_fork);
	if (philo_say(philo, TAKE_FORK))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	if (philo->philo_id % 2)
		take_fork(&philo->right_fork);
	else
		take_fork(&philo->left_fork);
	if (philo_say(philo, TAKE_FORK)
		|| philo_say(philo, EAT))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	wait_ms(philo->params->time_to_eat);
	return (0);
}

_Bool	philo_sleep(t_philo_data *philo)
{
	if (philo_say(philo, SLEEP))
	{
		lay_fork(&philo->left_fork);
		lay_fork(&philo->right_fork);
		return (1);
	}
	lay_fork(&philo->left_fork);
	lay_fork(&philo->right_fork);
	wait_ms(philo->params->time_to_slp);
	return (0);
}

_Bool	philo_think(t_philo_data *philo)
{
	if (philo_say(philo, THINK))
		return (1);
	if (philo->params->time_to_eat > philo->params->time_to_slp)
		wait_ms(philo->params->time_to_eat - philo->params->time_to_slp);
	if (philo->params->numbr_philo % 2)
		wait_ms(philo->params->time_to_eat);
	return (0);
}

void	*philo_main(void *data)
{
	t_philo_data	*philo;
	_Bool			run;

	philo = data;
	if (philo->params->numbr_philo == 1)
		return (NULL);
	if (philo->philo_id % 2)
		wait_ms(philo->params->time_to_eat);
	run = 1;
	while (run)
	{
		if (philo_eat(philo) || philo_sleep(philo) || philo_think(philo))
			return (NULL);
		pthread_mutex_lock(philo->params->shared->lock);
		run = !philo->params->shared->should_stop;
		pthread_mutex_unlock(philo->params->shared->lock);
	}
	return (NULL);
}
