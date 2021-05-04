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


void inorderTraversal(Node* ptr) //root노드 데려옴 //순환
{/*중위순회 : 부모->왼->오*/
	if(ptr!=NULL){
	inorderTraversal(ptr->left);
	printf("%3d", ptr->key);
	inorderTraversal(ptr->right);
	}

}

void preorderTraversal(Node* ptr)
{
	if(ptr!=NULL){
		printf("%3d", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr!=NULL){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("%3d", ptr->key);
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
	if(temp->key>key){
		temp->left=deleteLeafNode(temp->left, key);
	}
	else if (temp->key<key){
		temp->right=deleteLeafNode(temp->right, key);
	}
	else{
		if(temp->left==NULL){
			p=temp->right;
			free(temp);
			return p;
		}
		else {
			p=temp->left;
			free(temp);
			return temp;
		}
	}


	/*while(temp->key !=key){ //key값을 찾을 때 까지 반복
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
*/
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

//다시
int freeBST(Node* head)
{
	Node* ptr = head->left; //부모노드
	Node* lptr = NULL; //왼쪽트리
	Node* rptr = NULL; //오른쪽트리

	while(ptr!=NULL){
		lptr=ptr->left; //자식노드 지정
		rptr=ptr->right;
		free(ptr); //부모노드 메모리 해제
		if(lptr==NULL&&rptr==NULL){ //자식노드가 없으면 반복문 끝냄
			if(head->left->right==NULL){ //헤드노드ㅇ
			break;
			}
			else{
				ptr=head->left->right;
			}
		}
		else if(lptr==NULL){ //왼쪽자식이 없으면 오른쪽자식을 부모노드로 두고 반복
			ptr=rptr;}
		else if (rptr==NULL){//오른쪽자식이 없으면 왼쪽자식을 부모노드로 두고 반복
			ptr=lptr;
		}
		else if (lptr!=NULL && rptr!=NULL){
			ptr=lptr;
			/*freeBST(lptr);
			freeBST(rptr);*/
		}
		else{
			if(lptr->right==NULL&&lptr->right==NULL){//왼쪽오른쪽자식 둘 다 있을 경우 리프노드인지 판별하여 메모리 해제
				free(lptr);
				ptr=rptr; //오른쪽자식을 부모노드로 다시 반복 (왼쪽에 노드 없음)
			}
			if(rptr->right==NULL&&rptr->right==NULL){ //리프노드아니면 처음부터 반복
				free(rptr);
				if(lptr!=NULL){ //왼쪽자식 메모리 해제 안된경우(리프노드 아닌경우)
					ptr=lptr; //왼쪽자식을 부모노드로 반복 (오른쪽에 노드 없음)
				}
			}

		}

	}

	free(head); //헤드노드 메모리 해제



	/*while(ptr != NULL) { //트리가 존재할 때, 왼쪽트리부터 순회
		lptr=ptr;
		lptr=lptr->left;
		rptr=ptr->right;
		free(ptr);
			}

		while(rptr != NULL) { //트리가 존재할 때, 왼쪽트리부터 순회
			p = rptr;
			rptr = rptr->right;
			free(p);
			}
		free(head); //head노드 해제*/

	/*if(ptr!=NULL){
		freeBST(ptr->left);
		freeBST(ptr->right);
		free(ptr);
	}*/
	return 0;
}





