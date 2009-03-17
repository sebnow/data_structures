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

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/*!
 * \addtogroup binary_tree Binary Tree
 * \{
 */

/*!
 \brief A Binary Tree container
 */
typedef struct _BinaryTree BinaryTree;

/*!
 \brief Callback for freeing a \c BinaryTree node value
 \param value the value to be freed
 */
typedef void (*BinaryTreeFreeFunction)(void *value);

/*!
 \brief Initialize a new, empty \c BinaryTree
 \return initialized binary tree
 */
BinaryTree *BinaryTree_new();

/*!
 \brief Initialize a new \c BinaryTree with \a value

 Upon releasing the \c BinaryTree, \a value will not be freed. Memory
 management for \a value must thus be done externally.

 \param value value the \c BinaryTree should contain
 \return initialized binary tree with the value \a value.
 */
BinaryTree *BinaryTree_newWithValue_(void *value);

/*!
 \brief Initialize a new \c BinaryTree with \a value

 Upon releasing the \c BinaryTree, \a value will be freed using
 \a freeFunction.

 \param value value the \c BinaryTree should contain
 \param freeFunction function to be used to free \a value
 \return initialized binary tree with the value \a value.
 */
BinaryTree *BinaryTree_newWithValue_freeFunction_(void *value,
	BinaryTreeFreeFunction freeFunction);

/*!
 \brief Retain a \c BinaryTree

 This should be used whenever possession of \a self is wanted. This
 should be used in most cases when assigning \a self to another \c
 BinaryTree pointer.

 For example:
 \code
 BinaryTree *tree;
 BinaryTree *ref;
 tree = BinaryTree_new();
 // Initialization code for tree
 ref = BinaryTree_retain(tree);
 BinaryTree_release(tree);
 tree = NULL;
 \endcode

 \param self the \c BinaryTree
 \return \a self
 */
BinaryTree *BinaryTree_retain(BinaryTree *self);

/*!
 \brief Release the reference of a \c BinaryTree

 If there are no known references to \a self, all its child nodes will
 be released, and it will be freed. If a free function was specified, it
 will be used to free \a value.

 \param self the \c BinaryTree
 */
void BinaryTree_release(BinaryTree *self);

/*!
 \brief Set the left tree to \a tree

 \note The \c BinaryTree \a tree being assigned to the left branch is
 \link BinaryTree_retain() retained \endlink

 \param self the \c BinaryTree
 \param tree the \c BinaryTree to be assigned to the left branch
 \return 1 on success, 0 on failure
 */
int BinaryTree_setLeftTree_(BinaryTree *self, BinaryTree *tree);

/*!
 \brief Set the right tree to \a tree

 \note The \c BinaryTree \a tree being assigned to the left branch is
 \link BinaryTree_retain() retained \endlink

 \param self the \c BinaryTree
 \param tree the \c BinaryTree to be assigned to the right branch
 \return 1 on success, 0 on failure
 */
int BinaryTree_setRightTree_(BinaryTree *self, BinaryTree *tree);

/*!
 \brief Retrieve a pointer to the left tree
 \param self the \c BinaryTree
 \return the \c BinaryTree assigned to the left branch
 */
BinaryTree *BinaryTree_leftTree(BinaryTree *self);

/*!
 \brief Retrieve a pointer to the right tree
 \param self the \c BinaryTree
 \return the \c BinaryTree assigned to the right branch
 */
BinaryTree *BinaryTree_rightTree(BinaryTree *self);

/*!
 \brief Retrieve a pointer to the parent node
 \param self the \c BinaryTree
 \return the parent \c BinaryTree node or \c NULL if \a self is the root node
 */
BinaryTree *BinaryTree_parent(BinaryTree *self);

/*!
 \brief Set \a value as the new value for the \c BinaryTree \a self

 Upon releasing the \c BinaryTree, \a value will be freed using
 \a freeFunction.

 \param self the \c BinaryTree
 \param value value the \c BinaryTree should contain
 \return \c true on success, \c false otherwise.
 */
int BinaryTree_setValue_(BinaryTree *self, void *value);

/*!
 \brief Set \a value as the new value for the \c BinaryTree \a self

 Upon releasing the \c BinaryTree, \a value will not be freed. Memory
 management for \a value must thus be done externally.

 \param self the \c BinaryTree
 \param value value the \c BinaryTree should contain
 \param freeFunction function to be used to free \a value
 \return \c true on success, \c false otherwise.
 */
int BinaryTree_setValue_freeFunction_(BinaryTree *self, void *value,
	BinaryTreeFreeFunction freeFunction);

/*!
 \brief Return the value in the \c BinaryTree \a self
 \param self the \c BinaryTree
 \return the value in \a self
 */
void *BinaryTree_value(BinaryTree *self);

/*!
 \brief Determine if this node is a leaf

 A node is considered to be a leaf when both its left and right branches
 are \c NULL

 \param self the \c BinaryTree
 \return 1 if \a self is a leaf node, 0 otherwise.
 */
int BinaryTree_isLeafNode(BinaryTree *self);

/** \} */

#endif /* BINARY_TREE_H */
