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

#ifndef QUEUE_H
#define QUEUE_H

/*!
 \addtogroup queue
 \{
 */

/*! \brief Prototype for the function callback used to free queue node data */
typedef void (*QueueNodeFreeFunction)(void *);

/*!
 \brief FIFO queue structure
 */
typedef struct _Queue Queue;

/*!
 \brief Initialize a new, empty, \c Queue object
 \return initialized queue
 */
Queue *Queue_new();

/*!
 \brief Insert \a data at the end of the \a queue

 This is the same as Queue_insert_withFreeFunction_(), except the
 freeFunction is assumed to be free().

 \param self queue to insert data into
 \param data data to be inserted
 \return \c 1 (true) on success, \c 0 (false) otherwise
 */
int Queue_insert_(Queue *self, void *data);

/*!
 \brief Insert \a data at the end of the \a queue

 The supplied \a freeFunction will be used to free the data when the
 queue is freed. NULL can be passed to prevent the data from being freed 
 automatically.

 \param self queue to insert data into
 \param data data to be inserted
 \param freeFunction function to be called to free \a data
 \return \c 1 (true) on success, \c 0 (false) otherwise
 */
int Queue_insert_withFreeFunction_(Queue *self, void *data,
	QueueNodeFreeFunction freeFunction);

/*!
 \brief Remove element from the front of the \a queue
 \param self queue from which to remove the element
 \param data pointer to which the data from the head node should be assigned
 \return \c 1 (true) on success, \c 0 (false) otherwise
 */
int Queue_remove_(Queue *self, void **data);

/*!
 \brief Return amount of elements in the queue
 \param self queue to be counted
 \return amount of elements in queue
 */
unsigned int Queue_count(Queue *self);

/*!
 \brief Free memory taken up by \a queue

 If \a freeFunction is not \c NULL the node data will also be freed

 \param self queue to be freed
 */
void Queue_release(Queue *self);

/*!
 \brief Retain queue and return itself

 This should be used instead of assigning the queue directly, to
 maintain an accurate reference count

 \param self queue to be retained
 \return the queue
 */
Queue *Queue_retain(Queue *self);

/*!
 \}
 */

#endif
