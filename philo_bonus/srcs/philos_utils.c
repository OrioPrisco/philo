/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:35:05 by orio              #+#    #+#             */
/*   Updated: 2023/05/01 16:51:13 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include "philo.h"
#include <stdio.h>
#include "printer.h"

void	philo_say(t_philo_data *philo)
{
	sem_post(philo->relay_sem1);
	sem_wait(philo->relay_sem2);
}
