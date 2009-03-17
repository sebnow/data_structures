/*
 * Copyright (c) 2009 Sebastian Nowicki <sebnow@gmail.com>
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

#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Default free function */
#define BINARY_TREE_FREE NULL

struct _BinaryTree {
	/*! count of references to this tree */
	unsigned int refCount;
	/*! function for freeing the \link BinaryTree::value value \endlink */
	BinaryTreeFreeFunction freeFunction;
	/*! pointer to the parent node, \c NULL if this is the root node */
	BinaryTree *parent;
	/*! pointer to the value contained in the node */
	void *value;
	/*! pointer to the left branch */
	BinaryTree *left;
	/*! pointer to the right branch */
	BinaryTree *right;
};

BinaryTree *BinaryTree_new()
{
	return BinaryTree_newWithValue_(NULL);
}

BinaryTree *BinaryTree_newWithValue_(void *value)
{
	return BinaryTree_newWithValue_freeFunction_(value, BINARY_TREE_FREE);
}

BinaryTree *BinaryTree_newWithValue_freeFunction_(void *value,
	BinaryTreeFreeFunction freeFunction)
{
	BinaryTree *self;
	self = malloc(sizeof(*self));
	if(self != NULL) {
		self = memset(self, 0, sizeof(*self));
		BinaryTree_setValue_freeFunction_(self, value, freeFunction);
		self = BinaryTree_retain(self);
	}
	return self;
}

BinaryTree *BinaryTree_retain(BinaryTree *self)
{
	assert(self != NULL);
	self->refCount++;
	return self;
}

void BinaryTree_release(BinaryTree *self)
{
	assert(self != NULL);
	self->refCount--;
	if(self->refCount == 0) {
		BinaryTree_setLeftTree_(self, NULL);
		BinaryTree_setRightTree_(self, NULL);
		BinaryTree_setValue_(self, NULL);
		free(self);
	}
}

static int _setTree_forBranch_(BinaryTree *tree, BinaryTree **branch)
{
	if(*branch != NULL) {
		BinaryTree_release(*branch);
	}
	if(tree == NULL) {
		*branch = tree;
	} else {
		*branch = BinaryTree_retain(tree);
		tree->parent = *branch;
	}
	return 1;
}

int BinaryTree_setLeftTree_(BinaryTree *self, BinaryTree *tree)
{
	assert(self != NULL);
	return _setTree_forBranch_(tree, &self->left);
}

int BinaryTree_setRightTree_(BinaryTree *self, BinaryTree *tree)
{
	assert(self != NULL);
	return _setTree_forBranch_(tree, &self->right);
}

BinaryTree *BinaryTree_leftTree(BinaryTree *self)
{
	assert(self != NULL);
	return self->left;
}

BinaryTree *BinaryTree_rightTree(BinaryTree *self)
{
	assert(self != NULL);
	return self->right;
}

BinaryTree *BinaryTree_parent(BinaryTree *self)
{
	assert(self != NULL);
	return self->parent;
}

int BinaryTree_setValue_(BinaryTree *self, void *value)
{
	assert(self != NULL);
	return BinaryTree_setValue_freeFunction_(self, value, BINARY_TREE_FREE);
}

int BinaryTree_setValue_freeFunction_(BinaryTree *self, void *value,
	BinaryTreeFreeFunction freeFunction)
{
	assert(self != NULL);
	if(self->freeFunction != NULL) {
		self->freeFunction(self->value);
	}
	self->value = value;
	self->freeFunction = freeFunction;
	return 1;
}

void *BinaryTree_value(BinaryTree *self)
{
	assert(self != NULL);
	return self->value;
}

int BinaryTree_isLeafNode(BinaryTree *self)
{
	assert(self != NULL);
	return self->left == NULL && self->right == NULL;
}
