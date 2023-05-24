#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; /* 이진 탐색 트리의 노드에 저장되는 값 (키). */
	struct node *left; /* 왼쪽 서브트리를 가리키는 포인터. */
	struct node *right; /* 오른쪽 서브트리를 가리키는 포인터. */
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
    printf("[----- [이은총] [2022041043] -----]\n");
	char command; /* 사용자 입력 명령을 저장하는 변수. */
	int key; /* 사용자 입력 키 값을 저장하는 변수. */
	Node* head = NULL; /* 이진 탐색 트리의 헤드 노드를 가리키는 포인터 변수. */
	Node* ptr = NULL;	/* temp */ /* 임시로 사용되는 노드 포인터 변수. */

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
			initializeBST(&head); /* 이진 탐색 트리 초기화. */
			break;
		case 'q': case 'Q':
			freeBST(head); /* 메모리 해제. */
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); /* 노드 삽입. */
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); /* 리프 노드 삭제. */
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); /* 반복적인 방법으로 노드 검색. */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); /* 재귀적인 방법으로 노드 검색. */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); /* 중위 순회. */
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); /* 전위 순회. */
			break;
		case 't': case 'T':
			postorderTraversal(head->left); /* 후위 순회. */
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); /* 잘못된 입력에 대한 안내 메시지. */
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/* 이진 탐색 트리 초기화 함수. */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); /* 트리가 비어있지 않으면 모든 할당된 노드를 제거. */

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); /* 헤드 노드 생성. */
	(*h)->left = NULL;	/* root */ /* 왼쪽 자식 포인터를 NULL로 설정하여 루트 노드로 초기화. */
	(*h)->right = *h; /* 오른쪽 자식 포인터가 헤드 노드 자체를 가리키도록 설정. */
	(*h)->key = -9999; /* 헤드 노드의 키 값을 -9999로 설정. */
	return 1;
}

/* 중위 순회 함수. */
void inorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        inorderTraversal(ptr->left); /* 왼쪽 서브트리를 중위 순회로 방문. */
        printf("%d ", ptr->key); /* 현재 노드의 키 값을 출력. */
        inorderTraversal(ptr->right); /* 오른쪽 서브트리를 중위 순회로 방문. */
    }
}

/* 전위 순회 함수. */
void preorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        printf("%d ", ptr->key); /* 현재 노드의 키 값을 출력. */
        preorderTraversal(ptr->left); /* 왼쪽 서브트리를 전위 순회로 방문. */
        preorderTraversal(ptr->right); /* 오른쪽 서브트리를 전위 순회로 방문. */
    }
}

/* 후위 순회 함수. */
void postorderTraversal(Node* ptr)
{
    if (ptr != NULL) {
        postorderTraversal(ptr->left); /* 왼쪽 서브트리를 후위 순회로 방문. */
        postorderTraversal(ptr->right); /* 오른쪽 서브트리를 후위 순회로 방문. */
        printf("%d ", ptr->key); /* 현재 노드의 키 값을 출력 */
    }
}

/* 노드를 삽입하는 함수. */
int insert(Node* head, int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); /* 새로운 노드 생성. */
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    Node* cur = head->left; /* 현재 노드를 가리키는 포인터. */
    Node* parent = NULL; /* 부모 노드를 가리키는 포인터. */

    while (cur != NULL) {
        parent = cur;
        if (key < cur->key)
            cur = cur->left; /* 삽입할 키가 현재 노드의 키보다 작으면 왼쪽 자식 노드로 이동. */
        else if (key > cur->key)
            cur = cur->right; /* 삽입할 키가 현재 노드의 키보다 크면 오른쪽 자식 노드로 이동. */
        else {
            free(newNode);
            return 0; // Duplicate key /* 중복된 키가 존재하여 삽입 실패. */
        }
    }

    if (parent == NULL)
        head->left = newNode; /* 트리가 비어있을 경우 새로운 노드를 루트로 지정. */
    else {
        if (key < parent->key)
            parent->left = newNode; /* 부모 노드의 왼쪽 자식으로 새로운 노드 삽입. */
        else
            parent->right = newNode; /* 부모 노드의 오른쪽 자식으로 새로운 노드 삽입. */
    }

    return 1; /* 삽입 성공. */
}

/* 단말 노드를 삭제하는 함수. */
int deleteLeafNode(Node* head, int key)
{
    Node* cur = head->left; /* 현재 노드를 가리키는 포인터. */
    Node* parent = NULL; /* 부모 노드를 가리키는 포인터. */

    while (cur != NULL && cur->key != key) {
        parent = cur;
        if (key < cur->key)
            cur = cur->left; /* 삭제할 키가 현재 노드의 키보다 작으면 왼쪽 자식 노드로 이동. */
        else
            cur = cur->right; /* 삭제할 키가 현재 노드의 키보다 크면 오른쪽 자식 노드로 이동. */
    }

    if (cur == NULL)
        return 0; // Node not found  /* 삭제할 노드가 존재하지 않음. */

    if (cur->left != NULL || cur->right != NULL)
        return 0; // Node is not a leaf node  /* 삭제할 노드가 단말 노드가 아님. */

    if (parent == NULL)
        head->left = NULL;  /* 삭제할 노드가 루트 노드일 경우 트리를 비움. */
    else {
        if (parent->left == cur)
            parent->left = NULL;  /* 삭제할 노드가 부모 노드의 왼쪽 자식인 경우 연결을 끊음. */
        else
            parent->right = NULL;  /* 삭제할 노드가 부모 노드의 오른쪽 자식인 경우 연결을 끊음. */
    }

    free(cur);  /* 노드 삭제. */
    return 1;  /* 삭제 성공. */
}

/* 재귀적으로 트리를 탐색하여 주어진 키 값을 가지는 노드를 찾는 함수. */
Node* searchRecursive(Node* ptr, int key)
{
    if (ptr == NULL || ptr->key == key)
        return ptr; /* 노드가 NULL이거나 주어진 키 값을 가지는 노드를 찾은 경우 해당 노드 반환. */

    if (key < ptr->key)
        return searchRecursive(ptr->left, key); /* 주어진 키 값이 현재 노드의 키보다 작으면 왼쪽 서브트리에서 탐색. */
    else
        return searchRecursive(ptr->right, key); /* 주어진 키 값이 현재 노드의 키보다 크면 오른쪽 서브트리에서 탐색. */
}

/* 반복문을 사용하여 주어진 키 값을 가지는 노드를 찾는 함수. */
Node* searchIterative(Node* head, int key)
{
    Node* cur = head->left;

    while (cur != NULL) {
        if (key == cur->key)
            return cur; /* 주어진 키 값과 현재 노드의 키 값이 일치하면 해당 노드 반환. */
        else if (key < cur->key)
            cur = cur->left; /* 주어진 키 값이 현재 노드의 키 값보다 작으면 왼쪽 서브트리로 이동. */
        else
            cur = cur->right; /* 주어진 키 값이 현재 노드의 키 값보다 크면 오른쪽 서브트리로 이동. */
    }

    return NULL; /* 트리를 모두 탐색한 후에도 노드를 찾지 못한 경우 NULL 반환. */
}

/* 이진 탐색 트리의 모든 메모리를 해제하는 함수. */
int freeBST(Node* head)
{
    if (head != NULL) {
        freeBST(head->left); /* 왼쪽 서브트리의 메모리 해제. */
        freeBST(head->right); /* 오른쪽 서브트리의 메모리 해제. */
        free(head); /* 현재 노드의 메모리 해제. */
    }

    return 1;
}