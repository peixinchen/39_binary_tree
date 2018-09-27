#pragma once

#include <stdlib.h>

typedef int TDataType;

// �Ա�������Ľ�㿴
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

// ���ú��ս���ǰ�򴴽�������
// ���ؽ���Ƕ������ĸ����
// preorder: ���ս���ǰ��
// size: preorder�ĳ���
// 1. �ݹ�
// 2. �������Ĺ����л᷵��ʹ�ù��Ľ�����
RESULT CreateTree(TDataType preorder[], int size)
{
	if (size == 0) {
		RESULT result = { NULL, 0 };
		return result;
	}

	// �� �� ��������  ������
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
	// ��ֹ����
	if (root == NULL) {
		return;
	}

	// ��
	printf("%d ", root->data);
	// ���������������õݹ鴦��
	Preorder(root->left);
	// ���������������õݹ鴦��
	Preorder(root->right);
}



void Inorder(BNode *root)
{
	// ��ֹ����
	if (root == NULL) {
		return;
	}

	// ���������������õݹ鴦��
	Inorder(root->left);
	// ��
	printf("%d ", root->data);
	// ���������������õݹ鴦��
	Inorder(root->right);
}

void Postorder(BNode *root)
{
	// ��ֹ����
	if (root == NULL) {
		return;
	}

	// ���������������õݹ鴦��
	Postorder(root->left);
	// ���������������õݹ鴦��
	Postorder(root->right);
	// ��
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