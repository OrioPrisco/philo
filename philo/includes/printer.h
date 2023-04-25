/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:57:21 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 18:37:10 by OrioPrisc        ###   ########.fr       */
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

#endif
