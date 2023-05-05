/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/05 17:32:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "philos.h"
#include "debug.h"
#include "parse.h"
#include "printer.h"
#include "relay.h"
#include "vector.h"

void	print_usage(void)
{
	printf("Usage : ./philo <number_philo> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep> [<number_eats>]\n");
}

int	main(int argc, char **argv)
{
	t_params		params;
	pid_t			*philos;
	t_relay			*relays;
	t_vector		queue;

	if (parse_args(&params, argc, argv))
		return (print_usage(), 1);
	relays = ft_calloc(sizeof(*relays), params.numbr_philo);
	philos = ft_calloc(sizeof(*philos), params.numbr_philo);
	vector_init(&queue);
	if (!relays || ! philos)
		return (free(relays), free(philos), printf("Malloc error !\n"), 1);
	params.program_start = get_ms() + 100;
	params.stop = 0;
	populate_relays(relays, &params, &queue);
	if (launch_philos(philos, &params, relays)
		|| (launch_relays(relays, &params)
			&& (kill_philos(philos, params.numbr_philo), 1))
		|| (printer_main(&params, &queue), 0)
		|| (join_relays(relays, params.numbr_philo), 0)
		|| (kill_philos(philos, params.numbr_philo), 0))
		printf("Error Launching threads and/or process !\n");
	(free(relays), free(philos), vector_clear(&queue));
	if (DEBUG)
		dump_params(&params);
}
