/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/02 17:01:31 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "philos.h"
#include "debug.h"
#include "parse.h"
#include "printer.h"

void	print_usage(void)
{
	printf("Usage : ./philo <number_philo> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep> [<number_eats>]\n");
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_data	shared;
	pthread_mutex_t	*mutexes;
	t_philo			*philos;

	if (parse_args(&params, argc, argv))
		return (print_usage(), 1);
	params.shared = &shared;
	mutexes = ft_calloc(sizeof(*mutexes), params.numbr_philo + 2);
	shared = (t_shared_data)
	{0, mutexes + params.numbr_philo,
	{0, 0, 0}, mutexes + params.numbr_philo + 1};
	philos = ft_calloc(sizeof(*philos), params.numbr_philo);
	if (!mutexes || ! philos)
		return (free(mutexes), free(philos), printf("Malloc error !\n"), 1);
	params.program_start = get_ms();
	populate_philos(philos, mutexes, &params);
	if (launch_philos(philos, params.numbr_philo, &shared)
		|| (printer_main(&params))
		|| (join_philos(philos, params.numbr_philo, &shared), 0))
		printf("Error Launching threads !\n");
	(free(mutexes), free(philos));
	vector_clear(&shared.queue);
	if (DEBUG)
		dump_params(&params);
}
