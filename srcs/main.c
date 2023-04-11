/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/11 18:57:01 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "philos.h"
#include "debug.h"
#include "parse.h"

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_data	shared;
	pthread_mutex_t	*mutexes;
	t_philo			*philos;
	pthread_t		*threads;

	if (parse_args(&params, argc, argv))
		return (1);
	shared = (t_shared_data){0, params.numbr_philo};
	mutexes = ft_calloc(sizeof(*mutexes), params.numbr_philo + 1);
	philos = ft_calloc(sizeof(*philos), params.numbr_philo);
	threads = ft_calloc(sizeof(*threads), params.numbr_philo);
	if (!mutexes || ! philos || !threads)
		return (free(mutexes), free(philos), free(threads),
			printf("Malloc error !"), 1);
	populate_philos(philos, mutexes, &shared, &params);
	launch_philos(philos, threads, params.numbr_philo);
	free(mutexes);
	free(philos);
	dump_params(&params);
}
