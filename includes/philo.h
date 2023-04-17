/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/14 11:56:43 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_params
{
	size_t	numbr_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_slp;
	_Bool	binge_party;
	size_t	number_eats;
}	t_params;

// reasons for should stop can be :
// someone died
// error in initialization
// all philos ate
typedef struct s_shared_data
{
	_Bool	should_stop;
	size_t	hungry_philos;
}	t_shared_data;

#endif
