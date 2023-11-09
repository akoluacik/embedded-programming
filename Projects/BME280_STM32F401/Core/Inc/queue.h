/*
 * queue.h
 *
 *  Created on: 16 Nis 2023
 *      Author: anil
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

struct queueNode
{
	float data;
	struct queueNode *next;
};

void	enqueue( struct queueNode **headPtr, struct queueNode **tailPtr, float data);
double	dequeue(struct queueNode **headPtr, struct queueNode **tailPtr, float data);
void    array2queue( struct queueNode **headPtr, struct queueNode **tailPtr, float *arr, int size);
#endif /* INC_QUEUE_H_ */
