#include "stdio.h"
#include "stdlib.h"
// node definition
typedef struct Node {
	struct Node *small;
	struct Node *large;
	int data;
} Node;
/* SOLUTION START*/
Node* treeToList(Node* root) {
	Node *head = NULL;
	if(root->small) {
		Node* leftTree = treeToList(root->small);
		head = leftTree;
		root->small = head->small;
		head->small = head->small->large = root;
	} else head = root->small = root;
	if(root->large) {
		Node* rightTree = treeToList(root->large);
		root->large = rightTree;
		head->small = rightTree->small;
		rightTree->small->large = head; 
	} else root->large = head;
	return head;
}
/* SOLUTION END*/
/* ---------------------------------------------------------- */
// --- helper functions for validating our solution is correct.
// inserts node into the BST.
Node* insert(Node *root, int x) {
	if(!root) {
		Node* node = (Node*) malloc(sizeof(Node));
		node->small = node->large = NULL;
		node->data = x;
		return node;
	}
	else if(root->data >= x) root->small = insert(root->small, x);
	else root->large = insert(root->large, x);
	return root;
}
// function that prints a doubly linked circular list.
void print(Node* root) {
	Node* r = root;
	do {
		printf("%d ", r->data);
		r = r->large;
	} while(r != root);
}
int main(void) {
	Node* root = NULL;
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 5);
	print(treeToList(root));
}