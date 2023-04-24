/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:32:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 18:48:55 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include "shared_data.h"
#include <stdio.h>

void	philo_die(t_philo_data *philo)
{
	pthread_mutex_lock(philo->shared_data->lock);
	philo_say(philo, DIE, 0);
	philo->shared_data->should_stop = 1;
	pthread_mutex_unlock(philo->shared_data->lock);
}

//need to unlock forks if we exit because of death
// what if i die while trying to take the lock ?
_Bool	philo_eat(t_philo_data *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->philo_id % 2)
		take_fork(&philo->left_fork);
	else
		take_fork(&philo->right_fork);
	if (is_dead(philo) || philo_say(philo, TAKE_FORK, 1) || is_dead(philo))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	if (philo->philo_id % 2)
		take_fork(&philo->right_fork);
	else
		take_fork(&philo->left_fork);
	if (is_dead(philo) || philo_say(philo, TAKE_FORK, 1) || is_dead(philo)
		|| philo_say(philo, EAT, 1)
		|| philo_wait_ms(philo, philo->params->time_to_eat))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	philo->last_eat = get_ms();
	return (0);
}

_Bool	philo_sleep(t_philo_data *philo)
{
	lay_fork(&philo->left_fork);
	lay_fork(&philo->right_fork);
	if (is_dead(philo) || philo_say(philo, SLEEP, 1)
		|| philo_wait_ms(philo, philo->params->time_to_slp))
		return (1);
	return (0);
}

_Bool	philo_think(t_philo_data *philo)
{
	if (is_dead(philo) || philo_say(philo, THINK, 1))
		return (1);
	return (0);
}

void	*philo_main(void *data)
{
	t_philo_data	*philo;

	philo = data;
	philo->last_eat = get_ms();
	if (philo->philo_id % 2)
		philo_wait_ms(philo, philo->params->time_to_eat);
	while (1)
	{
		if (philo_eat(philo) || philo_sleep(philo) || philo_think(philo))
			return (NULL);
	}
	return (NULL);
}
