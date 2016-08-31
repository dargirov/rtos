#include "queue.h"

static uint32_t queue_high_array[4], high_front = 0, high_rear = 0;
static uint32_t queue_normal_array[4], normal_front = 0, normal_rear = 0;
static uint32_t queue_low_array[4], low_front = 0, low_rear = 0;

static void queue_push(uint32_t *a, uint32_t elem, uint32_t *rear)
{
	*(a + *rear) = elem;
	(*rear)++;
	*rear = *rear % 4;
}

static uint32_t queue_pop(uint32_t *a, uint32_t *front)
{
	uint32_t elem = *(a + *front);
	*(a + *front) = 0;
	(*front)++;
	*front = *front % 4;
	return elem;
}

static uint32_t queue_peek(uint32_t *a, uint32_t *front)
{
	uint32_t elem = *(a + *front);
	return elem;
}


void init_queues()
{
	for (int i = 0; i < 4; i++)
	{
		queue_high_array[i] = 0;
		queue_normal_array[i] = 0;
		queue_low_array[i] = 0;
	}
}

void queue_high_push(uint32_t elem)
{
	queue_push(queue_high_array, elem, &high_rear);
}

uint32_t queue_high_pop()
{
	return queue_pop(queue_high_array, &high_front);
}

uint32_t queue_high_peek()
{
	return queue_peek(queue_high_array, &high_front);
}


void queue_normal_push(uint32_t elem)
{
	queue_push(queue_normal_array, elem, &normal_rear);
}

uint32_t queue_normal_pop()
{
	return queue_pop(queue_normal_array, &normal_front);
}

uint32_t queue_normal_peek()
{
	return queue_peek(queue_normal_array, &normal_front);
}


void queue_low_push(uint32_t elem)
{
	queue_push(queue_low_array, elem, &low_rear);
}

uint32_t queue_low_pop()
{
	return queue_pop(queue_low_array, &low_front);
}

uint32_t queue_low_peek()
{
	return queue_peek(queue_low_array, &low_front);
}
