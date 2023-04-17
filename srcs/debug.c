/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:52 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/17 18:35:19 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "philo.h"
#include <stdio.h>

void	dump_params(const t_params *params)
{
	printf("numbr_philo : %zu\n", params->numbr_philo);
	printf("time_to_die : %llu\n", params->time_to_die);
	printf("time_to_eat : %llu\n", params->time_to_eat);
	printf("time_to_slp : %llu\n", params->time_to_slp);
	printf("binge_party : %d\n", params->binge_party);
	if (params->binge_party)
		printf("number_eats : %zu\n", params->number_eats);
}
