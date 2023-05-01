/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relay.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:45:56 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 17:03:18 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RELAY_H
# define RELAY_H

# include <semaphore.h>
# include "philo_sem.h"
# include <pthread.h>

typedef struct s_params	t_params;

typedef struct s_relay
{
	sem_t			*philo_sem1;
	sem_t			*philo_sem2;
	pthread_t		thread;
	const t_params	*params;
	size_t			id;
}	t_relay;

void	destroy_relays(t_relay *relays, size_t to_destroy);
_Bool	populate_relays(t_relay *relays, const t_params *params);
_Bool	launch_relays(t_relay *relays, const t_params *params);
void	join_relays(t_relay *relays, size_t nb_relays);
void	*relay_main(void *relay);

#endif