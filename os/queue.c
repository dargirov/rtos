#include "queue.h"

queue_t QueueCreate()
{
	queue_t queue;
	//queue.len = len;
	queue.size = 0;
	//queue.elements = (uint32_t*) malloc(len * sizeof(uint32_t));
	return queue;
}

void QueueSend(queue_t *queue, uint32_t elem)
{
	//uint32_t *addr = queue->elements + (queue->index * sizeof(uint32_t));
	//*addr = elem;
	//queue->index = queue->index + 1;
	queue_elem_t qelem;
	qelem.value = elem;
		
	if (queue->size == 0)
	{
		queue->elements = (uint32_t*) malloc(sizeof(queue_elem_t));
		*(queue->elements) = queue_elem_t;
		queue->front = queue->back = queue->elements;
		queue->size = queue->size + 1;
	}
}
