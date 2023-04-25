/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:32:44 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 15:50:28 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>

//need to unlock forks if we exit because of death
// what if i die while trying to take the lock ?
_Bool	philo_eat(t_philo_data *philo)
{
	if (philo->philo_id % 2)
		take_fork(&philo->left_fork);
	else
		take_fork(&philo->right_fork);
	if (philo_say(philo, TAKE_FORK, 1))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	if (philo->philo_id % 2)
		take_fork(&philo->right_fork);
	else
		take_fork(&philo->left_fork);
	if (philo_say(philo, TAKE_FORK, 1)
		|| philo_say(philo, EAT, 1))
		return (lay_fork(&philo->left_fork), lay_fork(&philo->right_fork), 1);
	wait_ms(philo->params->time_to_eat);
	philo->last_eat = get_ms();
	return (0);
}

_Bool	philo_sleep(t_philo_data *philo)
{
	lay_fork(&philo->left_fork);
	lay_fork(&philo->right_fork);
	if (philo_say(philo, SLEEP, 1))
		return (1);
	wait_ms(philo->params->time_to_slp);
	return (0);
}

_Bool	philo_think(t_philo_data *philo)
{
	return (philo_say(philo, THINK, 1));
}

void	*philo_main(void *data)
{
	t_philo_data	*philo;

	philo = data;
	philo->last_eat = get_ms();
	if (philo->philo_id % 2)
		wait_ms(philo->params->time_to_eat);
	while (1)
	{
		if (philo_eat(philo) || philo_sleep(philo) || philo_think(philo))
			return (NULL);
	}
	return (NULL);
}
