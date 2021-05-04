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
void isEmpty(Node* ptr);

/* you may add your own defined functions if necessary */


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
			isEmpty(head->left);
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			isEmpty(head->left);
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			isEmpty(head->left);
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

void isEmpty(Node* ptr){
	if(ptr==NULL){
		printf("tree is empty!\n");
		return ;
	}
}
void inorderTraversal(Node* ptr) //root노드 데려옴 //순환
{/*중위순회 : 부모->왼->오*/

	if(ptr!=NULL){ //순환형 중위순회
	inorderTraversal(ptr->left); //왼쪽 방문
	printf("%3d", ptr->key); //키값 출력
	inorderTraversal(ptr->right); //오른쪽방문
	}
	else
		return ;

}

void preorderTraversal(Node* ptr)
{

	if(ptr!=NULL){ //순환형 전위순회
		printf("%3d", ptr->key); //ptr값 먼저 출력
		preorderTraversal(ptr->left); //왼쪽방문
		preorderTraversal(ptr->right); //오른쪽 방문
	}
	else
		return ;
}

void postorderTraversal(Node* ptr)
{

	if(ptr!=NULL){ //순환형 후위순회
		postorderTraversal(ptr->left);//왼쪽방문
		postorderTraversal(ptr->right);//오른쪽 방문
		printf("%3d", ptr->key); //키값출력
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
		return 1;
	}

	while(1){
		if(temp->key==key){
			printf("같은 값안됨!!!!");
			return 0;
		}
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

	return 0;

}

int deleteLeafNode(Node* head, int key)
{
	if(head->left==NULL){ //빈 트리일 경우
			printf("tree is empty!\n");
			return 0;
		}

	Node* temp = (Node*)malloc(sizeof(Node)); //임시노드 생성
	Node* p = (Node*)malloc(sizeof(Node)); //임시노드

	temp=head->left; //루트노드
	p=NULL; //부모노드

	while((temp!=NULL)&&(temp->key!=key)){ //노드 위치 탐색
		p=temp;
		if(key<temp->key) //찾는 값이 루트노드보다 작은 경우
			temp=temp->left; //왼쪽트리로 옮겨 재탐색
		else
			temp=temp->right; //큰경우에는 오른쪽트리로 옮겨 재탐색
	}
	if(temp==NULL){ //key를 찾지 못한 경우
		printf("%d is not in tree\n", key);
		return 0;
	}

	//key를 찾은 경우
	if((temp->left==NULL)&&(temp->right==NULL)){ //leafnode인지 검사
		if (p !=NULL){ //리프노드인 경우, 부모노드가 있는 경우
			if(p->left==temp)//key가 왼쪽 노드인 경우
				p->left=NULL;//부모노드의 왼쪽을 NULL로
			else
				p->right=NULL;//오른쪽 노드인 경우 오른쪽링크를 NULL로
		}
		else
			head->left==NULL; //루트노드뿐인 트리, 루트노드=단말노드이므로 head->left를 NULL로
		free(temp);
	}
	else{
		printf("%d is not leafNode\n");
		return 0;
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

	Node* ptr = head->left;//루트노드
	if(ptr!=NULL){//후위순위를 이용한 메모리 해제
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->left);
	free(ptr);
	}
	free(head); //헤드노드까지 해제해줌
	return 0;
}





