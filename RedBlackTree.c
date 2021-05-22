/*
Data Structure
Dehit Trivedi
RED - BLACK TREE

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct node{
	int key;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(int key);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);
void red_black_transplant(struct node *u, struct node *v);
void red_black_delete(struct node *z);
void red_black_delete_fixup(struct node *x);

int main(){
  double time_spent = 0.0;
  clock_t begin = clock();
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;

	ROOT = NILL;

	printf("Insert elements\n\n");

	int i, key;
	printf("Number of key: ");
	scanf("%d", &i);
	while(i--){
		printf("Enter key: ");
		scanf("%d", &key);
		red_black_insert(key);
	}

  printf("Tree\n\n");
	tree_print(ROOT);
	printf("\n");


	printf("minimum test\n\n");
	printf("MIN: %d\n", (tree_minimum(ROOT))->key);
	printf("----------\n");

	printf("Tree \n\n");
	tree_print(ROOT);
	printf("\n");
  printf("\n");


  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("----------\n");
  printf("The elapsed time is %f seconds", time_spent);

	return 0;
}

void tree_print(struct node *x){
	if(x != NILL){
		tree_print(x->left);
		printf("%d\t", x->key);
		tree_print(x->right);
	}
}

struct node *tree_search(int key){
	struct node *x;

	x = ROOT;
	while(x != NILL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	return x;
}

struct node *tree_minimum(struct node *x){
	while(x->left != NILL){
		x = x->left;
	}
	return x;
}

void red_black_insert(int key){
	struct node *z, *x, *y;
	z = malloc(sizeof(struct node));

	z->key = key;
	z->color = RED;
	z->left = NILL;
	z->right = NILL;

	x = ROOT;
	y = NILL;

	while(x != NILL){
		y = x;
		if(z->key <= x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	if(y == NILL){
		ROOT = z;
	}
	else if(z->key <= y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}

void red_black_insert_fixup(struct node *z){
	while(z->parent->color == RED){

		if(z->parent == z->parent->parent->left){

			if(z->parent->parent->right->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else{

				if(z == z->parent->right){
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		else{

			if(z->parent->parent->left->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else{

				if(z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}

	ROOT->color = BLACK;
}

void left_rotate(struct node *x){
	struct node *y;


	y = x->right;
	x->right = y->left;
	if(y->left != NILL){
		y->left->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}


	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x)
{
	struct node *y;

	y = x->left;
	x->left = y->right;
	if(y->right != NILL){
		y->right->parent = x;
	}


	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
  y->right = x;
	x->parent = y;
}
