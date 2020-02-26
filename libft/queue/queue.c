/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:37:45 by cseguier          #+#    #+#             */
/*   Updated: 2020/02/26 01:37:46 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

static t_qnode* new_node(char *data) 
{ 
    t_qnode* temp;
	
	if (!(temp = malloc(sizeof(t_qnode))))
		return (NULL);
    temp->data = data; 
    temp->next = NULL; 
    return (temp); 
} 
  
static t_queue* create_queue() 
{ 
    t_queue* q;
	
	if (!(q = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
    q->front = NULL;
	q->rear = NULL; 
    return (q); 
} 

void en_queue(t_queue* q, char *data) 
{ 
    t_qnode* temp; 
	
	temp = new_node(data); 
    if (q->rear == NULL)
	{ 
        q->front = temp;
		q->rear = temp; 
        return; 
    } 
    q->rear->next = temp; 
    q->rear = temp; 
} 

/*
** Dont forget to free q after the program
*/
void de_queue(t_queue* q) 
{ 
    t_qnode* temp = q->front; 
    
	if (q->front == NULL) 
        return; 
    q->front = q->front->next; 
    if (q->front == NULL) 
        q->rear = NULL; 
    free(temp); 
} 