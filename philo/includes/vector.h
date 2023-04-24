/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:50 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 12:00:16 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# include <stdbool.h>
# include "printer.h"

# define DEFAULT_VECTOR_SIZE 10
//for now only grows, and never shrinks
typedef t_message	t_vector_data;

typedef struct s_vector {
	size_t			size;
	size_t			capacity;
	t_vector_data	*data;
}	t_vector;

//All Functions returning bool will return 1 on allocation error
//    or 0 on success. They will leave the vector in a state that can be
//    cleared with vector_clear

t_vector		*vector_init(t_vector *vector);
bool			vector_allocate(t_vector *vector, size_t size);
bool			vector_append(t_vector *vector, t_vector_data data);
//appends an element n times
bool			vector_append_n(t_vector *vector, t_vector_data data, size_t n);
//appends n elems from data
bool			vector_append_elems(t_vector *vector, t_vector_data *data,
					size_t n);
//Frees all the memory inside the vector and resets the vector back to all 0s
//Does not free the t_vector *
t_vector		*vector_clear(t_vector *vector);
//ensures that there are size free spaces to insert elements in
bool			vector_ensure_capacity(t_vector *vector, size_t size);
t_vector_data	vector_pop(t_vector *vector, size_t index);
//Maybe rename to delete_n ?
t_vector		*vector_pop_n(t_vector *vector, size_t index, size_t n);
bool			vector_insert(t_vector *vector, size_t index,
					t_vector_data data);
//Does not clear the vector, But Initializes it
bool			vector_copy(t_vector *des, const t_vector *src);
//Does not clear the vector, But Initializes it
bool			vector_copy_n(t_vector *dest, const t_vector_data *src,
					size_t n);
t_vector		*vector_sort(t_vector *vector);
//returns ptr to src so you can free it if needed
t_vector		*vector_move(t_vector *dest, t_vector *src);
size_t			vector_count_elems(t_vector *vector, t_vector_data data,
					size_t index);
bool			vector_is_sorted(t_vector *vector, bool ascending);
#endif
