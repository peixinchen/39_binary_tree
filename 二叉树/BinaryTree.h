#pragma once

#include <stdlib.h>

typedef int TDataType;

// 对比着链表的结点看
typedef struct BNode {
	TDataType data;
	struct BNode *left;
	struct BNode *right;
}	BNode;

static BNode * CreateNode(TDataType data)
{
	BNode *node = (BNode *)malloc(sizeof(BNode));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

typedef struct {
	BNode *root;
	int	used;
}	RESULT;

// 利用含空结点的前序创建二叉树
// 返回结果是二叉树的根结点
// preorder: 带空结点的前序
// size: preorder的长度
// 1. 递归
// 2. 创建树的过程中会返回使用过的结点个数
RESULT CreateTree(TDataType preorder[], int size)
{
	if (size == 0) {
		RESULT result = { NULL, 0 };
		return result;
	}

	// 根 ， 左子树，  右子树
	TDataType rootValue = preorder[0];
	if (rootValue == -1) {
		RESULT result = { NULL, 1 };
		return result;
	}

	BNode *root = CreateNode(rootValue);

	RESULT lr = CreateTree(&preorder[1], size - 1);
	root->left = lr.root;
	RESULT rr = CreateTree(&preorder[1 + lr.used], size - 1 - lr.used);
	root->right = rr.root;

	RESULT result = { root, 1 + lr.used + rr.used };
	return result;
}

void Preorder(BNode *root)
{
	// 终止条件
	if (root == NULL) {
		return;
	}

	// 根
	printf("%d ", root->data);
	// 左子树，子问题用递归处理
	Preorder(root->left);
	// 右子树，子问题用递归处理
	Preorder(root->right);
}



void Inorder(BNode *root)
{
	// 终止条件
	if (root == NULL) {
		return;
	}

	// 左子树，子问题用递归处理
	Inorder(root->left);
	// 根
	printf("%d ", root->data);
	// 右子树，子问题用递归处理
	Inorder(root->right);
}

void Postorder(BNode *root)
{
	// 终止条件
	if (root == NULL) {
		return;
	}

	// 左子树，子问题用递归处理
	Postorder(root->left);
	// 右子树，子问题用递归处理
	Postorder(root->right);
	// 根
	printf("%d ", root->data);
}

#include <stdio.h>

void Test()
{
	TDataType preorder[] = { 1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, 7 };
	int size = sizeof(preorder) / sizeof(TDataType);
	RESULT r = CreateTree(preorder, size);
	Preorder(r.root); printf("\n");

	printf("%d, %d\n", size, r.used);
}