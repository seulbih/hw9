/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
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
void push(Node* ptr);
Node* pop();

/* you may add your own defined functions if necessary */
#define MAX_STACK_SIZE 100
int top = -1;
Node* stack[MAX_STACK_SIZE];

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[-------[황슬비] [2018032027] ------");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}
void push(Node* ptr){
	if(top<MAX_STACK_SIZE-1&& ptr !=NULL)
	stack[++top] = ptr;
}


Node* pop(){
	Node* p=NULL;
	if(top>=0)
		p=stack[top--];
	return p;

}


void inorderTraversal(Node* ptr) //root노드 데려옴, iterative-> 스택 이용
{/*중위순회 : 부모->왼->오*/
	if (ptr==NULL){
			printf("tree is empty!!!");
			return;
		}
	while(1){
		for(; ptr; ptr=ptr->left){
			push(ptr);
		}
		ptr=pop();
		if(!ptr)
			break;
		printf("%3d", ptr->key);
		ptr=ptr->right;
	}



}

void preorderTraversal(Node* ptr)
{
	if (ptr==NULL){
			printf("tree is empty!!!");
			return;
		}

	push(ptr);
	while(1){
		ptr=pop();
		if(!ptr)
			break;
		printf("%3d", ptr->key);
		push(ptr->right);
		push(ptr->left);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr==NULL){
	printf("tree is empty!!!");
	return;
	}
	while(1){
		do{
			if(ptr->key !=NULL && ptr !=NULL){
				push(ptr);
				ptr=ptr->left;
			}
			else
				break;
		}
		while(ptr !=NULL);
		ptr = pop();
		if(!ptr) break;
		if(ptr->right != NULL){
			if(ptr->right->key ==NULL){
				printf("%3d",ptr->key);
				ptr->key=NULL;
			}
			else{
				push(ptr);
				ptr=ptr->right;
			}
		}
		else {
			printf("%3d", ptr->key);
			ptr->key=NULL;
		}
	}

}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node)); //새로운 노드 생성
	Node* temp = (Node*)malloc(sizeof(Node)); //임시노드 생성

	temp=head->left; //root노드
	node->key=key;
	node->left=NULL;
	node->right=NULL;

	if(head->left==NULL)//초기상태인 경우, root노드가 없을 때
	{
		head->left=node;//헤드노드에 연결하려 root노드 생성
		return 0;
	}

	while(1){
		if(key<temp->key){ //key값이 root노드보다 작은 경우 > 왼쪽으로
				if(temp->left == NULL){ //왼쪽 서브트리가 존재하지 않는 경우
					temp->left = node; //노드 삽입
					break;//반복문 탈출
				}
				else//왼쪽 서브트리가 존재하는 경우
					temp=temp->left; //왼쪽 서브트리가 더이상 존재하지 않을 때까지 반복
			}
			else{
				if(temp->right == NULL){ //오른쪽 서브트리가 존재하지 않는 경우
					temp->right = node; //노드 삽입
					break;//반복문 탈출
					}
				else//오른쪽 서브트리가 존재하는 경우
					temp=temp->right; //오른쪽 서브트리가 더이상 존재하지 않을 때까지 반복
					}

	}


	/*if(key<temp->key){ //key값이 root노드보다 작은 경우 > 왼쪽으로
		if(temp->left != NULL){ //왼쪽 서브트리가 존재하는 경우
			temp->left = insert(temp->left, key); //왼쪽 서브트리로 이동하여 반복
		}
		else
			temp->left = node; //왼쪽 서브트리가 더이상 존재하지 않을 때 node추가
	}
	else{
		if(temp->right !=NULL){ //오른쪽 서브트리가 존재하는 경우
			temp->right = insert(temp->right, key); //오른쪽 서브트리로 이동하여 반복
			}
		else //오른쪽 서브트리가 더이상 존재하지 않을 때 node추가
			temp->right=node;
		}
*/
	return 0;

}

int deleteLeafNode(Node* head, int key)
{
	Node* temp = (Node*)malloc(sizeof(Node)); //임시노드 생성
	Node* p = (Node*)malloc(sizeof(Node)); //임시노드
	Node* del = (Node*)malloc(sizeof(Node)); //임시노드 생성
	if (head->left==NULL){
		printf("tree is empty!!!");
		return 0;
	}
	temp=head->left; //root노드
	while(temp->key !=key){ //key값을 찾을 때 까지 반복
		p=temp; //부모노드 저장
		if(key<temp->key){ //root노드보다 작을 때, 왼쪽으로 temp옮김
			temp=temp->left;
		}
		else{ //root노드보다 클 때, 오른쪽으로 temp옮김
			temp=temp->right;
		}
		if(temp=NULL) {//key값 없는 경우
			printf("key is not in treeeee");
			return 0; //그냥 종료
		}
	} //key값 찾으면 반복문 탈출 -> key=temp->key

	if(temp->left==NULL&&temp->right==NULL){ //temp가 leafnode인지 판별
		if(p->left!=NULL){ //부모의 왼쪽 노드가 NULL이 아니면
			if(temp->key==p->left->key){//부모의 왼쪽노드가 찾는 값이면
				p->left=NULL; //부모의 왼쪽노드 NULL로 설정
				return 1;
			}
		}
		p->right=NULL; //오른쪽 노드가 존재하고 NULL이 아니면 찾는 값이 오른쪽노드, NULL로설정해줌
		free(temp); //키값 메모리 해제
	}

	return 0;
}

Node* searchRecursive(Node* ptr, int key) //ptr=root노드
{
	if (ptr==NULL){
		printf("tree is empty!!!");
		return NULL;
	}
	if(key == ptr->key){ //root노드가 key인 경우
		return ptr;
	}
	if(key < ptr->key){ //key<root노드 인 경우 왼쪽 서브트리 탐색, recursive
		return searchRecursive(ptr->left, key);
	}
	else
		return searchRecursive(ptr->right, key); //아무것도 아닌 경우 오른쪽 서브트리 탐색, recursive

	return NULL; //찾는 값이 없는 경우 NULL리턴

}

Node* searchIterative(Node* head, int key)
{
	if (head->left==NULL){
			printf("tree is empty!!!");
			return NULL;
		}
	Node* temp = (Node*)malloc(sizeof(Node)); //임시노드 생성
	temp=head->left; //임시노드가 root노드 가리키도록 설정
	while(temp!=NULL){
		if (key==temp->key){ //key=root노드 인 경우
			return temp; //root노드 반환
		}
		if (key < temp->key){ //root>key인 경우 왼쪽 서브트리 탐색
			temp=temp->left;
		}
		else
			temp=temp->right; //오른쪽 서브트리 탐색
	}
	return NULL; //못찾으면 NULL 리턴


}


int freeBST(Node* head)
{

	return 0;
}





