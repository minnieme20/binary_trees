#include "binary_trees.h"

int remove_type(bst_t *root);
bst_t *bst_remove(bst_t *root, int value);
int successor(bst_t *node);
void bal(avl_t **tree);
avl_t *avl_remove(avl_t *root, int value);

/**
 * remove_type - removes either of the child nodes
 * @root: pointer to the root node
 *
 * Return: 0 if children, else a child
 */
int remove_type(bst_t *root)
{
	int new_value = 0;

	if (!root->left && !root->right)
	{
		if (root->parent->right == root)
			root->parent->right == NULL;
		else
			root->parent->left == NULL;
		free(root);
		return (0);
	}
	else if ((!root->left && root->right) || (!root->right && root->left))
	{
		if (!root->left)
		{
			if (root->parent->right == root)
				root->parent->right = root->right;
			else
				root->parent->left = root->right;
			root->right->parent = root->parent;
		}
		if (!root->right)
		{
			if (root->parent->right == root)
				root->parent->right = root->left;
			else
				root->parent->left = root->left;
			root->left->parent = root->parent;
		}
		free(root);
		return (0);
	}
	else
	{
		new_value = successor(root->right);
		root->n = new_value;
		return (new_value);
	}
}

/**
 * bst_remove - remove node from bst
 * @root: root of the tree
 * @value: node value to remove
 *
 * Return: root node after deletion
 */
bst_t *bst_remove(bst_t *root, int value)
{
	int type = 0;

	if (root == NULL)
		return (NULL);
	if (value < root->n)
		bst_remove(root->left, value);
	else if (value > root->n)
		bst_remove(root->right, value);
	else if (value == root->n)
	{
		type = remove_type(root);
		if (type != 0)
			bst_remove(root->right, type);
	}
	else
		return (NULL);
	return (root);
}

/**
 * successor - gets the successor
 * @tree: pointer to the root node
 *
 * Return: the minimum value of the tree
 */
int successor(bst_t *node)
{
	int left = 0;

	if (node == NULL)
		return (0);
	else
	{
		left = successor(node->left);
		if (left == 0)
		{
			return (node->n);
		}
		return (left);
	}
}

/**
 * bal - balancer of the AVL
 * @tree: tree to traverse
 *
 * Return: balanced tree
 */
void bal(avl_t **tree)
{
	int bval;

	if (tree == NULL || *tree == NULL)
		return;
	if ((*tree)->left == NULL && (*tree)->right == NULL)
		return;
	bal(&(*tree)->left);
	bal(&(*tree)->right);
	bval = binary_tree_balance((const binary_tree_t *)*tree);
	if (bval > 1)
		*tree = binary_tree_rotate_right((binary_tree_t *)*tree);
	else if (bval < -1)
		*tree = binary_tree_rotate_left((binary_tree_t *)*tree);
}

/**
 * avl_remove - a function that removes a node from an AVL tree
 * @root: a function that removes a node from an AVL tree
 * @value: is the value to remove in the tree
 *
 * Return: new root node of the tree after removing the desired value
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *root_a = (avl_t *) bst_remove((bst_t *) root, value);

	if (root_a == NULL)
		return (NULL);
	bal(&root_a);

	return (root_a);
}
