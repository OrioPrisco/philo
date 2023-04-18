/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/17 18:35:36 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "philos.h"
#include "debug.h"
#include "parse.h"
#include "shared_data.h"

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_data	shared;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*shared_m;
	t_philo			*philos;

	if (parse_args(&params, argc, argv))
		return (1);
	shared = (t_shared_data){0, params.numbr_philo};
	mutexes = ft_calloc(sizeof(*mutexes), params.numbr_philo + 1);
	philos = ft_calloc(sizeof(*philos), params.numbr_philo);
	shared_m = mutexes + params.numbr_philo;
	if (!mutexes || ! philos)
		return (free(mutexes), free(philos), printf("Malloc error !\n"), 1);
	populate_philos(philos, mutexes, &shared, &params);
	if (launch_philos(philos, params.numbr_philo, &shared, shared_m)
		|| (join_philos(philos, params.numbr_philo, shared_m), 0))
		printf("Error Launching threads !\n");
	free(mutexes);
	free(philos);
	dump_params(&params);
}
