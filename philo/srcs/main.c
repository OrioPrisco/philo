/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/26 20:00:55 by orio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "philos.h"
#include "debug.h"
#include "parse.h"
#include "printer.h"

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_data	shared;
	pthread_mutex_t	*mutexes;
	t_philo			*philos;

	if (parse_args(&params, argc, argv))
		return (1);
	params.shared = &shared;
	mutexes = ft_calloc(sizeof(*mutexes), params.numbr_philo + 1);
	shared = (t_shared_data)
	{0, params.numbr_philo, mutexes + params.numbr_philo};
	philos = ft_calloc(sizeof(*philos), params.numbr_philo);
	queue_action(INIT, NULL);
	if (!mutexes || ! philos)
		return (free(mutexes), free(philos), printf("Malloc error !\n"), 1);
	params.program_start = get_ms();
	populate_philos(philos, mutexes, &shared, &params);
	if (launch_philos(philos, params.numbr_philo, &shared)
		|| (printer_main(&params))
		|| (join_philos(philos, params.numbr_philo, &shared), 0))
		printf("Error Launching threads !\n");
	(free(mutexes), free(philos));
	queue_action(FREE, NULL);
	dump_params(&params);
}
