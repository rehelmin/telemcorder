#include "queue.h"

void enqueue(volatilve queue_t *queue, uint32_t in)
{
	queue->fifo[queue->tail++] = in;
}

void dequeue(volatile queue_t *queue, uint32_t *out){
    while(queue->head == queue->tail){
        STANDBY();
    }

    *out = queue->fifo[queue->head++];
}