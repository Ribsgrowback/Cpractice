
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
실습 시험: Section F - 이진 탐색 트리 문제
목적: 문제 1에서 요구하는 함수를 구현하기 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // BSTNode 구조체 정의는 변경하면 안 됨

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // QueueNode 구조체 정의는 변경하면 안 됨


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // queue 구조체 정의는 변경하면 안 됨

///////////////////////////////////////////////////////////////////////////////////

// 이 함수들의 원형(prototype)은 변경하면 안 됨
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// 이진 탐색 트리를 빈 트리로 초기화
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // 이 함수를 직접 구현해야 함
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{
    /* 여기에 코드를 작성 */

	//재귀 DFS는 조건에 안맞음

	/* pseudo 코드로 로직 먼저 작성
	enqueue(root)
	while (!empty):
    	dequeue → 출력
    	좌 우 노드를 큐에 삽입 
	*/

	if (root == NULL) { //트리가 비었는가??
		return 0;
	}
	

	/*
	QueueNode 구조 
	typedef struct _QueueNode {
		BSTNode *data;
		struct _QueueNode *nextPtr;
	} QueueNode;
	*/

	QueueNode *head = NULL; //큐의 시작점, 마지막 포인터 
	QueueNode *tail = NULL;
	enqueue(&head, &tail, root);//루트노드부터 큐에 넣기
	// 현재 큐 상태: [root]
//			10 (root)
//		   / \
//		  5   15
/*
head
 ↓
[root] -> NULL
  ↑
tail
*/

	BSTNode *current;

	while (head!=NULL) { //헤드 포인터로 남은 노드 있을 동안 체크
		current = dequeue(&head, &tail); //큐에서 노드 꺼내기: 현재 root 노드
		printf("%d ", current->item); 

		if (current->left!=NULL) {  //왼쪽에 노드 있으면 :
			enqueue(&head, &tail, current->left); //큐에 넣기
		}
		if (current->right!=NULL) {//오른쪽에 노드 있으면 :
			enqueue(&head, &tail, current->right); //큐에 넣기
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}

