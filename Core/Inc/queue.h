#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint32_t fifo[256];
	uint32_t head;
	uint32_t tail;
} queue_t;

void enqueue(volatile queue_t *queue, uint32_t in);
void dequeue(volatile queue_t *queue, uint32_t *out);

#ifdef __cplusplus
}
#endif

#endif /* __QUEUE_H */