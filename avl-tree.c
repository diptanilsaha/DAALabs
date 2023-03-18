#include <stdio.h>
#include <stdlib.h>
 
typedef struct BST{
	int data;
	struct BST *left, *right;
}TreeNode;
 
void insert(TreeNode *root, TreeNode *temp) {
	if(root->data >= temp->data) {
		if(root->left) {
			insert(root->left, temp);
		} else {
			root->left = temp;
		}
	}else {
		if(root->right) {
			insert(root->right, temp);
		} else {
			root->right = temp;
		}
	}
}
 
void inorder(TreeNode *root) {
	if(!root) {
		return;
	}
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}
 
void preorder(TreeNode *root) {
	if(!root) {
		return;
	}
	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}
 
void postorder(TreeNode *root) {
	if(!root) {
		return;
	}
	preorder(root->left);
	preorder(root->right);
	printf("%d ", root->data);
}
 
TreeNode *create_node(int data) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
 
TreeNode *searchNode(TreeNode *root, int data) {
	if(root == NULL)
		return NULL;
 
	if(root->data == data) {
		return root;
	}else if(root->data > data && root->left) {
		if(root->left->data == data){
			return root->left;
		} else {
			searchNode(root->left, data);
		}
	} else if(root->data < data && root->right) {
		if(root->right->data == data) {
			return root->right;
		} else {
			searchNode(root->right, data);
		}
	} else {
		return NULL;
	}
}
 
TreeNode *searchParentNode(TreeNode *root, int data) {
	if(!root)
	return NULL;
 
	if(root->data == data){
		return NULL;
	}else if(root->data > data && root->left) {
		if(root->left->data == data){
			return root;
		} else {
			searchParentNode(root->left, data);
		}
	} else if(root->data < data && root->right){
		if(root->right->data == data) {
			return root;
		} else {
			searchParentNode(root->right, data);
		}
	}
}
 
void case1delete(TreeNode *node, TreeNode *parent, TreeNode **root) {
	if(!parent) {
		*root = NULL;
	}
	else if (parent->left == node) {
		parent->left = NULL;
	} else if (parent->right == node) {
		parent->right = NULL;
	}
	free(node);
	printf("\nNode deleted");
}
 
void case2delete(TreeNode *node, TreeNode *parent, TreeNode **root) {
	TreeNode *child;
	if (node->left != NULL) {
		child = node->left;
	} else if (node->right != NULL) {
		child = node->right;
	}
	if (parent == NULL) {
		*root = child;
	} else if(parent->left == node) {
		parent->left = child;
	} else {
		parent->right = child;
	}
	free(node);
	printf("\nNode deleted");
}
 
TreeNode *getInorderSucc(TreeNode *node) {
	TreeNode *ptr = node->right;
	while(ptr->left) {
		ptr = ptr->left;
	}
	return ptr;
}
 
void case3delete(TreeNode *node, TreeNode *inorderSucc, TreeNode **root) {
	TreeNode *parentDNode = NULL;
	parentDNode = searchParentNode(*root, inorderSucc->data);
	node->data = inorderSucc->data;
	if(!(inorderSucc->left) && !(inorderSucc->right)) {
		case1delete(inorderSucc, parentDNode, &(*root));
	} else {
		case2delete(inorderSucc, parentDNode, &(*root));
	}
}
 
void deletion(TreeNode **root) {
	int data;
	printf("\nEnter the node you want to delete: ");
	scanf("%d", &data);
	TreeNode *node = NULL, *parentNode = NULL;
	node = searchNode(*root, data);
	if(node){
		parentNode = searchParentNode(*root, data);	
	}
	if(!(node->left) && !(node->right)) {
		case1delete(node, parentNode, &(*root));
	} else if(((node->left) && !(node->right)) || (!(node->left) && (node->right))) {
		case2delete(node, parentNode, &(*root));
	} else {
		parentNode = getInorderSucc(node);
		case3delete(node, parentNode, &(*root));
	}
}
 
int height(TreeNode *root) {
	int lh, rh;
	if(!root) {
		return 0;
	}
	lh = height(root->left);
	rh = height(root->right);
	return (1 + (lh >= rh ? lh : rh));
}
 
void leftRotation(TreeNode *node, TreeNode **root) {
	TreeNode* pnode = searchParentNode(*root, node->data);
	TreeNode *right_child = node->right;
	int left = 0, right = 0;
	if(pnode) {
		if(pnode->right->data == node->data) {
			right = 1;
		} else {
			left = 1;
		}
	}
	node->right = right_child->left;
	right_child->left = node;
	if(!pnode) {
		*root = right_child;
	} else {
		if(left){
			pnode->left = right_child;
		} else {
			pnode->right = right_child;
		}
	}
}
 
void rightRotation(TreeNode *node, TreeNode **root) {
	TreeNode* pnode = searchParentNode(*root, node->data);
	TreeNode *left_child = node->left;
	int left = 0, right = 0;
	if(pnode) {
		if(pnode->right->data == node->data) {
			right = 1;
		} else {
			left = 1;
		}
	}
	node->left = left_child->right;
	left_child->right = node;
	if(!pnode) {
		*root = left_child;
	} else {
		if(left){
			pnode->left = left_child;
		} else {
			pnode->right = left_child;
		}
	}
}
 
void bal_height_check(TreeNode *node, TreeNode **root) {
	if(!node) {
		return;
	}
	bal_height_check(node->left, &(*root));
	bal_height_check(node->right, &(*root));
	int lh, rh, balance;
	lh = height(node->left);
	rh = height(node->right);
	balance = lh - rh;
	if(balance < -1) {
		leftRotation(node, &(*root));
	} 
	else if (balance > 1) {
		rightRotation(node, &(*root));
	}
}
 
int main() {
	TreeNode *root=NULL, *temp=NULL;
	int ch, data;
	while(1) {
		printf("\n1. Insert Node in BST");
		printf("\n2. Print BST");
		printf("\n3. Deletion");
		printf("\n4. Height");
		printf("\n5. Exit");
		printf("\nEnter your Choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				printf("\nEnter data: ");
				scanf("%d", &data);
				temp = create_node(data);
				if(!root) {
					root = temp;
				} else {
					insert(root, temp);
				}
				printf("\nInorder: ");
				inorder(root);
				printf("\nPreorder: ");
				preorder(root);
				bal_height_check(root, &root);
				printf("\n\nAfter balancing");
				printf("\nInorder: ");
				inorder(root);
				printf("\nPreorder: ");
				preorder(root);
				break;
			case 2:
				printf("\nTree:\nInorder: ");
				inorder(root);
				printf("\nPreorder: ");
				preorder(root);
				printf("\nPostorder: ");
				postorder(root);
				break;
			case 3:
				deletion(&root);
				break;
			case 4:
				printf("\nHeight of Tree: ");
				printf("%d", height(root));
				break;
			case 5:
				printf("\nExiting Program!");
				exit(1);
				break;
			default:
				printf("\nWrong Choice!");
				break;
		}
	}
	return 0;
}
