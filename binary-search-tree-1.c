#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; /* ���� Ž�� Ʈ���� ��忡 ����Ǵ� �� (Ű). */
	struct node *left; /* ���� ����Ʈ���� ����Ű�� ������. */
	struct node *right; /* ������ ����Ʈ���� ����Ű�� ������. */
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

int main()
{
    printf("[----- [������] [2022041043] -----]\n");
	char command; /* ����� �Է� ����� �����ϴ� ����. */
	int key; /* ����� �Է� Ű ���� �����ϴ� ����. */
	Node* head = NULL; /* ���� Ž�� Ʈ���� ��� ��带 ����Ű�� ������ ����. */
	Node* ptr = NULL;	/* temp */ /* �ӽ÷� ���Ǵ� ��� ������ ����. */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); /* ���� Ž�� Ʈ�� �ʱ�ȭ. */
			break;
		case 'q': case 'Q':
			freeBST(head); /* �޸� ����. */
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); /* ��� ����. */
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); /* ���� ��� ����. */
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); /* �ݺ����� ������� ��� �˻�. */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); /* ������� ������� ��� �˻�. */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); /* ���� ��ȸ. */
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); /* ���� ��ȸ. */
			break;
		case 't': case 'T':
			postorderTraversal(head->left); /* ���� ��ȸ. */
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* �߸��� �Է¿� ���� �ȳ� �޽���. */
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* ���� Ž�� Ʈ�� �ʱ�ȭ �Լ�. */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); /* Ʈ���� ������� ������ ��� �Ҵ�� ��带 ����. */

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); /* ��� ��� ����. */
	(*h)->left = NULL;	/* root */ /* ���� �ڽ� �����͸� NULL�� �����Ͽ� ��Ʈ ���� �ʱ�ȭ. */
	(*h)->right = *h; /* ������ �ڽ� �����Ͱ� ��� ��� ��ü�� ����Ű���� ����. */
	(*h)->key = -9999; /* ��� ����� Ű ���� -9999�� ����. */
	return 1;
}

/* ���� ��ȸ �Լ�. */
void inorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        inorderTraversal(ptr->left); /* ���� ����Ʈ���� ���� ��ȸ�� �湮. */
        printf("%d ", ptr->key); /* ���� ����� Ű ���� ���. */
        inorderTraversal(ptr->right); /* ������ ����Ʈ���� ���� ��ȸ�� �湮. */
    }
}

/* ���� ��ȸ �Լ�. */
void preorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        printf("%d ", ptr->key); /* ���� ����� Ű ���� ���. */
        preorderTraversal(ptr->left); /* ���� ����Ʈ���� ���� ��ȸ�� �湮. */
        preorderTraversal(ptr->right); /* ������ ����Ʈ���� ���� ��ȸ�� �湮. */
    }
}

/* ���� ��ȸ �Լ�. */
void postorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        postorderTraversal(ptr->left); /* ���� ����Ʈ���� ���� ��ȸ�� �湮. */
        postorderTraversal(ptr->right); /* ������ ����Ʈ���� ���� ��ȸ�� �湮. */
        printf("%d ", ptr->key); /* ���� ����� Ű ���� ��� */
    }
}

/* ��带 �����ϴ� �Լ�. */
int insert(Node* head, int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); /* ���ο� ��� ����. */
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    Node* cur = head->left; /* ���� ��带 ����Ű�� ������. */
    Node* parent = NULL; /* �θ� ��带 ����Ű�� ������. */

    while (cur != NULL) {
        parent = cur;
        if (key < cur->key)
            cur = cur->left; /* ������ Ű�� ���� ����� Ű���� ������ ���� �ڽ� ���� �̵�. */
        else if (key > cur->key)
            cur = cur->right; /* ������ Ű�� ���� ����� Ű���� ũ�� ������ �ڽ� ���� �̵�. */
        else {
            free(newNode);
            return 0; // Duplicate key /* �ߺ��� Ű�� �����Ͽ� ���� ����. */
        }
    }

    if (parent == NULL)
        head->left = newNode; /* Ʈ���� ������� ��� ���ο� ��带 ��Ʈ�� ����. */
    else {
        if (key < parent->key)
            parent->left = newNode; /* �θ� ����� ���� �ڽ����� ���ο� ��� ����. */
        else
            parent->right = newNode; /* �θ� ����� ������ �ڽ����� ���ο� ��� ����. */
    }

    return 1; /* ���� ����. */
}

/* �ܸ� ��带 �����ϴ� �Լ�. */
int deleteLeafNode(Node* head, int key)
{
    Node* cur = head->left; /* ���� ��带 ����Ű�� ������. */
    Node* parent = NULL; /* �θ� ��带 ����Ű�� ������. */

    while (cur != NULL && cur->key != key) {
        parent = cur;
        if (key < cur->key)
            cur = cur->left; /* ������ Ű�� ���� ����� Ű���� ������ ���� �ڽ� ���� �̵�. */
        else
            cur = cur->right; /* ������ Ű�� ���� ����� Ű���� ũ�� ������ �ڽ� ���� �̵�. */
    }

    if (cur == NULL)
        return 0; // Node not found  /* ������ ��尡 �������� ����. */

    if (cur->left != NULL || cur->right != NULL)
        return 0; // Node is not a leaf node  /* ������ ��尡 �ܸ� ��尡 �ƴ�. */

    if (parent == NULL)
        head->left = NULL;  /* ������ ��尡 ��Ʈ ����� ��� Ʈ���� ���. */
    else {
        if (parent->left == cur)
            parent->left = NULL;  /* ������ ��尡 �θ� ����� ���� �ڽ��� ��� ������ ����. */
        else
            parent->right = NULL;  /* ������ ��尡 �θ� ����� ������ �ڽ��� ��� ������ ����. */
    }

    free(cur);  /* ��� ����. */
    return 1;  /* ���� ����. */
}

/* ��������� Ʈ���� Ž���Ͽ� �־��� Ű ���� ������ ��带 ã�� �Լ�. */
Node* searchRecursive(Node* ptr, int key)
{
    if (ptr == NULL || ptr->key == key)
        return ptr; /* ��尡 NULL�̰ų� �־��� Ű ���� ������ ��带 ã�� ��� �ش� ��� ��ȯ. */

    if (key < ptr->key)
        return searchRecursive(ptr->left, key); /* �־��� Ű ���� ���� ����� Ű���� ������ ���� ����Ʈ������ Ž��. */
    else
        return searchRecursive(ptr->right, key); /* �־��� Ű ���� ���� ����� Ű���� ũ�� ������ ����Ʈ������ Ž��. */
}

/* �ݺ����� ����Ͽ� �־��� Ű ���� ������ ��带 ã�� �Լ�. */
Node* searchIterative(Node* head, int key)
{
    Node* cur = head->left;

    while (cur != NULL) {
        if (key == cur->key)
            return cur; /* �־��� Ű ���� ���� ����� Ű ���� ��ġ�ϸ� �ش� ��� ��ȯ. */
        else if (key < cur->key)
            cur = cur->left; /* �־��� Ű ���� ���� ����� Ű ������ ������ ���� ����Ʈ���� �̵�. */
        else
            cur = cur->right; /* �־��� Ű ���� ���� ����� Ű ������ ũ�� ������ ����Ʈ���� �̵�. */
    }

    return NULL; /* Ʈ���� ��� Ž���� �Ŀ��� ��带 ã�� ���� ��� NULL ��ȯ. */
}

/* ���� Ž�� Ʈ���� ��� �޸𸮸� �����ϴ� �Լ�. */
int freeBST(Node* head)
{
    if (head != NULL) {
        freeBST(head->left); /* ���� ����Ʈ���� �޸� ����. */
        freeBST(head->right); /* ������ ����Ʈ���� �޸� ����. */
        free(head); /* ���� ����� �޸� ����. */
    }

    return 1;
}