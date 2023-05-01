/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/01 16:53:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stddef.h>
# include "philo_time.h"
# include <semaphore.h>

typedef struct s_relay			t_relay;
typedef struct s_params			t_params;
typedef pid_t					t_philo;

//shared data lock also acts as a print lock
typedef struct s_philo_data
{
	const t_params	*params;
	size_t			philo_id;
	sem_t			*forks;
	sem_t			*relay_sem1;
	sem_t			*relay_sem2;
}	t_philo_data;

typedef enum e_action
{
	TAKE_FORK,
	SLEEP,
	EAT,
	THINK,
	DIE,
	ERROR,
}	t_action;

//init
_Bool	launch_philos(t_philo *philos, const t_params *params, t_relay *relays);
void	kill_philos(t_philo *philos, size_t to_join);
//utils
void	philo_say(t_philo_data *philo);
//actions
void	philo_eat(t_philo_data *philo);
void	philo_sleep(t_philo_data *philo);
void	philo_think(t_philo_data *philo);
void	philo_main(t_philo_data *philo);
#endif
