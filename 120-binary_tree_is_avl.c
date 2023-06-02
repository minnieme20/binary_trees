#include "binary_trees.h"
#include "limits.h"

size_t height(const binary_tree_t *tree);
int is_avl_helper(const binary_tree_t *tree, int lo, int hi);
int binary_tree_is_avl(const binary_tree_t *tree);

/**
 * height - function to calculate height of tree
 * @tree: the tree from the root node
 *
 * Return: height of the tree elso 0
 */
size_t height(const binary_tree_t *tree)
{
	if (tree)
	{
		size_t left = 0, right = 0;

		left = tree->left ? 1 + height(tree->left) : 1;
		right = tree->right ? 1 + height(tree->right) : 1;
		return ((left > right) ? left : right);
	}
	return (0);
}

/**
 * is_avl_helper - checks if the AVL tree is valid
 * @tree: pointer to the root node of the tree
 * @lo: lowest node visited
 * @hi: highest node visited
 *
 * Return: if tree is valid 1, 0 otherwise
 */
int is_avl_helper(const binary_tree_t *tree, int lo, int hi)
{
	size_t lefthgt, righthgt, diff;

	if (tree != NULL)
	{
		if (tree->n < lo || tree->n > hi)
			return (0);
		lefthgt = height(tree->left);
		righthgt = height(tree->right);
		diff = lefthgt > righthgt ? lefthgt - righthgt : righthgt - lefthgt;
		if (diff > 1)
			return (0);
		return (is_avl_helper(tree->left, lo, tree->n - 1) &&
			is_avl_helper(tree->right, tree->n + 1, hi));
	}
	return (1);
}

/**
 * binary_tree_is_avl - checks if a binary tree is a valid AVL Tree
 * @tree: pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid AVL Tree, and 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (is_avl_helper(tree, INT_MIN, INT_MAX));
}
