#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;

struct node_t {
  int data;
  node_t *Left;
  node_t *Right;
};

struct tree_t {
  node_t *root;
};

struct CTreapNode {
    int Key;
	int Priority;
    CTreapNode* Left;
	CTreapNode* Right;
	CTreapNode(int key, int priority) : Key(key), Priority(priority), Left(0), Right(0) {}
};

node_t* tree_find_impl(node_t* node, int data) {
  node_t *current_node = node;
  
  while (current_node != NULL) {
    if (current_node->data > data) {
      if (current_node->Left != NULL) {
        current_node = current_node->Left;
      } else {
        return current_node;
      }
    } else if (current_node->data <= data) {
      if (current_node->Right != NULL) {
        current_node = current_node->Right;
      } else {
        return current_node;
      }
    }
  }
  
  return NULL;
}

node_t* tree_find(tree_t &tree, int data) {
  node_t *node = tree_find_impl(tree.root, data);
  if (node != NULL && node->data == data) {
    return node;
  }
  return NULL;
}

void init_node(node_t &node, int data) {
  node.data = data;
  node.Left = NULL;
  node.Right = NULL;
}

void tree_add(tree_t &tree, int data) {
  node_t *node = tree_find_impl(tree.root, data);
  if (node == NULL) {
    tree.root = new node_t;
    init_node(*tree.root, data);
  } else if (node->data > data) {
    node->Left = new node_t;
    init_node(*node->Left, data);
  } else { // node->data < data
    node->Right = new node_t;
    init_node(*node->Right, data);
  }
}

template<typename T>
int max_tree_width(T *node) {
    /* используя level-order обход найдем размер самого широкого слоя */
  queue<T*> s;
  queue<T*> childs;
  if (node == NULL) return 0 ;
  int tree_width = 1;
  s.push(node);
  while(!s.empty()) {
    while(!s.empty()) {
     T * temp_node = s.front();
     if(temp_node->Left !=NULL) childs.push(temp_node->Left);
     if(temp_node->Right !=NULL) childs.push(temp_node->Right);
     tree_width = max(tree_width, (int)childs.size());
     s.pop();
    }
    s = childs;
    queue<T*> empty;
    swap( childs, empty );
  }
  return tree_width;
}

CTreapNode* Merge(CTreapNode* left, CTreapNode* right)
{
	if( left == 0 || right == 0 ) {
		return left == 0 ? right : left;
	}
	if( left->Priority > right->Priority ) {
		left->Right = Merge(left->Right, right);
		return left;
    }
	right->Left = Merge(left, right->Left);
	return right;
}

void Split(CTreapNode* currentNode, int key, CTreapNode*& left, CTreapNode*& right)
{
	if( currentNode == 0 ) {
		left = 0;
		right = 0;
	} else if( currentNode->Key <= key ) {
		CTreapNode* tempLeft = 0;
		CTreapNode* tempRight = 0;
		Split(currentNode->Right, key, tempLeft, tempRight);
		right = tempRight;
		left = currentNode;
		left->Right = tempLeft;
    } else {
		CTreapNode* tempLeft = 0;
		CTreapNode* tempRight = 0;
		Split(currentNode->Left, key, tempLeft, tempRight);
		left = tempLeft;
		right = currentNode;
		right->Left = tempRight;
    }
}


CTreapNode* Insert(CTreapNode* root, int key, int priority) {
	CTreapNode* node = new CTreapNode(key, priority);
	CTreapNode* splitLeft = 0;
	CTreapNode* splitRight = 0;
	Split(root, key, splitLeft, splitRight);
    return Merge(Merge(splitLeft, node), splitRight);
}

CTreapNode* Delete(CTreapNode* root, int key)
{
	CTreapNode* splitLeft = 0;
	CTreapNode* splitRight = 0;
	Split(root, key - 1, splitLeft, splitRight);
	CTreapNode* splitRightLeft = 0;
	CTreapNode* splitRightRight = 0;
    Split(splitRight, key, splitRightLeft, splitRightRight);
    delete splitRightLeft;
	return Merge(splitLeft, splitRightRight);
}

int main()
{

	CTreapNode* root = 0; // декатово дерево
    tree_t  tree ; // наивное дерево поиска
    tree.root = 0;
    int n;
    cin >> n;
	while( n > 0 ) {
		int key = 0;
		int priority = 0;
		std::cin >> key >> priority;
        tree_add(tree, key);
		if( root == 0 ) {
			root = new CTreapNode(key, priority);
		} else {
			root = Insert(root, key, priority);
		}
        n--;
	} 
    std::cout << (max_tree_width(root) -  max_tree_width(tree.root));
}
