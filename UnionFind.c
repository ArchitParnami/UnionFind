#include <stdio.h>
#include <malloc.h>

typedef struct Node Node;

Node* root(int);
int connected(int,int);
void Union(int,int);
void destroy();
void menu();



struct Node {
	int elements_attached;
	Node *next;
};

Node **id;
int n;

int main(int argc, char const *argv[])
{
	int i;

	printf("Enter the number of elements : ");
	scanf("%d",&n);

	if(n <=0) {
		printf("Number if elements must be greater than zero!");
		return 1;
	}

	id = (Node**) malloc(sizeof(Node*) * n);

	for(i=0; i < n; i++) {
		id[i] = NULL;
	}

	printf("Numbers 0 to %d created\n\n",n-1);
	menu();
	destroy();
	return 0;
}

Node* root(int p) {
	Node *prev = id[p];
	
	if(prev == NULL)
		return NULL;

	while(prev->next != NULL) {
		prev = prev->next;
	}

	return prev;
}

int connected(int p, int q) {
	Node *root_p, *root_q;
	if ( (root_p = root(p)) == NULL || (root_q = root(q)) == NULL )
		return 0;
	else {
		if(root_p == root_q)
			return 1;
		else
			return 0;
	}
}

void Union(int p, int q) {

	Node *parent_p = id[p];
	Node *parent_q = id[q];

	Node *joint;
	if (parent_p == NULL && parent_q == NULL) {
		
		joint = (Node*)malloc(sizeof(Node));
		joint->next = NULL;
		joint->elements_attached = 2;
		id[p] = id[q] = joint;
	}

	else if(parent_p == NULL && parent_q != NULL) {
		id[p] = parent_q;
		parent_q->elements_attached += 1;
		
		Node *temp = parent_q->next;
		
		while(temp != NULL) {
			temp->elements_attached += 1;
			temp = temp -> next;
		}
	}

	else if (parent_q == NULL && parent_p != NULL) {
		id[q] = parent_p;
		parent_p->elements_attached += 1;
		
		Node *temp = parent_p->next;
		
		while(temp != NULL) {
			temp->elements_attached += 1;
			temp = temp -> next;
		}
	}
	
	else if (parent_p != parent_q) {

		Node *root_p = root(p);
		Node *root_q = root(q);

		if(root_p != root_q) {
			if( root_p->elements_attached < root_q->elements_attached) {
				root_p->next = root_q;
				root_q->elements_attached += root_p->elements_attached;
			}
			else {
				root_q->next = root_p;
				root_p->elements_attached += root_q->elements_attached;
			}
		}
	}

}

void destroy() {

	int i;
	for(i =0 ; i < n; i++) {

		if(id[i] != NULL) {
			
			Node* parent = id[i];
			Node* grandParent = parent->next;
			
			parent->elements_attached -= 1;

			while(grandParent != NULL) {
				
				grandParent->elements_attached -= 1;
				
				if(grandParent->elements_attached == 0) {
					Node *temp = grandParent;
					grandParent = grandParent->next;
					temp->next = NULL;
					free(temp);
				}
				else {
					grandParent = grandParent->next;
				}
			}

			
			if(parent->elements_attached == 0) {
				parent->next = NULL;
				free(parent);
			}
		}
	}

	for(i=0; i <n; i++) {
		id[i] = NULL;
	}

	free(id);
}

void menu() {
	int i;
	int p,q;
 do {
 	printf("\n");
	printf("1.connected\n");
	printf("2.Union\n");
	printf("3.Exit\n");
	printf("Enter Choice : ");
	scanf("%d",&i);
	switch(i) {
		case 1 : printf("\nEnter p & q : ");
				 scanf("%d%d",&p,&q);
				 if(connected(p,q)) {
				 	printf("true\n");
				 }
				 else {
				 	printf("false\n");
				 }
				 break;
		case 2 : printf("\nEnter p & q : ");
				 scanf("%d%d",&p,&q);
				 Union(p,q);
				 break;
		case 3 : break;
	}
 }while(i!=3);

}