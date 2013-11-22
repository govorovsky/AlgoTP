#include <iostream>
#include <stack>
#include <stdio.h>
#include <queue>
using namespace std;

struct node_t {
  int data;
  node_t *Left;
  node_t *Right;
};

struct tree_t {
  node_t *root;
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

void tree_traverse_stack(node_t *node, void(*foo)(int)) {
  queue<node_t*> s;
  if (node == NULL) return;
  s.push(node);
  while(!s.empty()) {
      node_t * temp_node = s.front();
      foo(temp_node->data);
      s.pop();
     if(temp_node->Left !=NULL) s.push(temp_node->Left);
     if(temp_node->Right !=NULL) s.push(temp_node->Right);
  }
    
}

void print(int data) {
    printf("%d ",data);
}

int main() {
    int n, data=0;
    tree_t tree;
    tree.root = NULL;
    cin >> n;
    for(int i=0;i<n;i++) {
        cin >> data;
        tree_add(tree,data);
    }
    tree_traverse_stack(tree.root,print);

};
