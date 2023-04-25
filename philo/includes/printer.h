/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:21 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/25 20:01:12 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include <stddef.h>
# include "philo_time.h"
# include "philos.h"

typedef struct s_message
{
	t_ms		ms;
	size_t		id;
	t_action	action;
}	t_message;

typedef enum e_queue_action
{
	POP,
	PUSH,
	FREE,
	INIT,
}	t_queue_action;

void	queue_action(t_queue_action action, t_message *opt);
void	*printer_main(void *foo);

//internals

typedef struct s_philo_monitor
{
	t_ms	last_eat;
	size_t	eats;
}	t_philo_monitor;

void	print_message(t_message *message);

//monitor functions
_Bool	check_death(const t_params *params, t_philo_monitor *philos);
void	update_philo(const t_params *params, t_philo_monitor *philos,
			t_message *message);
void	kill_philo(size_t id, t_ms ms, const t_params *params);
_Bool	check_end(const t_params *params, t_philo_monitor *philos);
#endif
