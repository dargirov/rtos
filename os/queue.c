#include "queue.h"

queue_t QueueCreate(uint32_t size)
{
	queue_t queue;
	queue.size = size;
	queue.elements = (uint32_t*) malloc(size * sizeof(uint32_t));
	queue.front = queue.rear = 0;
	for (int i = 0; i < size; i++)
	{
		*(queue.elements + i) = 0;
	}
	
	return queue;
}

void QueuePush(queue_t *queue, uint32_t elem)
{
	*(queue->elements + queue->rear) = elem;
	queue->rear++;
	queue->rear = queue->rear % queue->size;
}

uint32_t QueuePop(queue_t *queue)
{
	uint32_t elem = *(queue->elements + queue->front);
	queue->front++;
	queue->front = queue->front % queue->size;
	return elem;
}

uint32_t QueueCount(queue_t *queue)
{
	return queue->rear - queue->front;
}

void QueueDelete(queue_t *queue)
{
	free(queue->elements);
}