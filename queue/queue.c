/*
 * Copyright (c) 2008 Sebastian Nowicki <sebnow@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include "queue.h"
#include <stdlib.h>
#include <assert.h>

/*! \brief Node of a queue, storing the data and a link to the next node */
struct _QueueNode {
	/*! \brief The data stored in the node */
	void *data;
	/*! \brief Next node in the queue */
	struct _QueueNode *next;
	/*! \brief Callback used for freeing \a data */
	QueueNodeFreeFunction freeFunction;
};
typedef struct _QueueNode QueueNode;

struct _Queue {
	/* Amount of references held for this node */
	unsigned int refcount;
	/*! \brief Head (oldest) node of the queue */
	QueueNode *head;
	/*! \brief Tail (newest) node of the queue */
	QueueNode *tail;
	/*! \brief Amount of nodes in the queue */
	size_t count;
};

static QueueNode *QueueNode_newWithData_freeFunction_(void *data, QueueNodeFreeFunction freefunction)
{
	QueueNode *self;
	self = malloc(sizeof(*self));
	if(self != NULL) {
		self->next = NULL;
		self->data = data;
		self->freeFunction = freefunction;
	}
	return self;
}

static QueueNode *QueueNode_newWithData_(void *data)
{
	return QueueNode_newWithData_freeFunction_(data, free);
}

Queue *Queue_new()
{
	Queue *self;
	self = malloc(sizeof(*self));
	if(self != NULL) {
		self->head = NULL;
		self->tail = NULL;
		self->count = 0;
	}
	return self;
}

int Queue_insert_(Queue *self, void *data)
{
	return Queue_insert_withFreeFunction_(self, data, free);
}

int Queue_insert_withFreeFunction_(Queue *self, void *data, QueueNodeFreeFunction freeFunction)
{
	QueueNode *node;
	assert(self != NULL);
	node = QueueNode_newWithData_freeFunction_(data, freeFunction);

	/* First node in queue */
	if(self->tail == NULL) {
		self->tail = node;
		self->head = node;
	} else {
		self->tail->next = node;
		self->tail = node;
	}
	self->count++;
	return 1;
}

int Queue_remove_(Queue *self, void **data)
{
	*data = NULL;
	QueueNode *node;
	if(self->head == NULL) {
		return 0;
	}
	*data = self->head->data;
	node = self->head->next;
	free(self->head);
	self->head = node;
	self->count--;
	if(self->head == NULL) {
		self->tail = NULL;
	}
	return 1;
}

unsigned int Queue_count(Queue *self)
{
	return self->count;
}

void Queue_release(Queue *self)
{
	void *data = NULL;
	QueueNodeFreeFunction freeFunction;

	self->refcount--;
	/* Free queue if there are no references to it */
	if(self->refcount == 0) {
		if(self->head != NULL) {
			/* Reference the free function before the node gets freed */
			freeFunction = self->head->freeFunction;
			while(Queue_remove_(self, &data)) {
				if(freeFunction != NULL && data != NULL) {
					freeFunction(data);
				}
				if(self->head != NULL) {
					freeFunction = self->head->freeFunction;
				}
			}
		}
		free(self);
	}
}

Queue *Queue_retain(Queue *self)
{
	self->refcount++;
	return self;
}
