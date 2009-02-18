#include "queue.h"
#include <stdlib.h>
#include <assert.h>

typedef union {
	int integer;
	char *string;
	void *pointer;
} DataValue;

struct Data {
	enum {
		DATA_TYPE_INT = 0,
		DATA_TYPE_STRING,
		DATA_TYPE_POINTER
	} type;
	DataValue value;
};

struct Data *Data_new() {
	struct Data *self;
	self = malloc(sizeof(*self));
	return self;
}

#define TEST_DATA_COUNT 5

int main()
{
	Queue *queue;
	void *nodeData;
	struct Data *testData[TEST_DATA_COUNT];
	int count;

	queue = Queue_new();
	
	for(count = 0; count < TEST_DATA_COUNT; count++) {
		testData[count] = NULL;
	}

	/* New queues should have 0 nodes */
	assert(Queue_count(queue) == 0);

	testData[0] = Data_new();
	testData[0]->type = DATA_TYPE_STRING;
	testData[0]->value.string = "testing";
	
	Queue_insert_withFreeFunction_(queue, testData[0], NULL);
	/* Inserting a node should increase count */
	assert(Queue_count(queue) == 1);
	
	/* Removing from non-empty should succeed */
	assert(Queue_remove_(queue, &nodeData));
	/* Removing last node should reduce count to 0 */
	assert(Queue_count(queue) == 0);
	/* Removed data should be equal to previously inserted data */
	assert(nodeData == testData[0]);

	Queue_release(queue);
	queue = Queue_new();

	/* Insert TEST_DATA_COUNT elements */
	for(count = 0; count < TEST_DATA_COUNT; count++) {
		testData[count] = Data_new();
		testData[count]->type = DATA_TYPE_INT;
		testData[count]->value.integer = count;
		Queue_insert_withFreeFunction_(queue, testData[count], NULL);
	}

	/* Verify data integrity of all inserted elements */
	for(count = 0; count < TEST_DATA_COUNT; count++) {
		assert(Queue_count(queue) == TEST_DATA_COUNT - count);
		assert(Queue_remove_(queue, &nodeData));
		assert(nodeData == testData[count]);
		free(testData[count]);
		testData[count] = NULL;
		nodeData = NULL;
	}
	
	Queue_release(queue);
	
	return 0;
}
