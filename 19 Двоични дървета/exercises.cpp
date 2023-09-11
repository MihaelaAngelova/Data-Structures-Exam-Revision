#include <iostream>

template<class T>
struct BinTreeNode{
    T data;
    BinTreeNode<T>* left;
    BinTreeNode<T>* right;

    BinTreeNode(const T& data): 
        data(data), left(nullptr), right(nullptr){};

    BinTreeNode(const T& data, BinTreeNode<T>* left, BinTreeNode<T>* right): 
        data(data), left(left), right(right) {};
};


template <class T>
class BinTree{
    private:
    BinTreeNode<T>* root;

    public:
    BinTree(): root(nullptr){};
    BinTree(BinTreeNode<T>*& root): root(root){};
    int count(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        return 1 + count(root->left) + count(root->right);
    }

    int countEvens(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        if(root->data %2 == 0){
            return 1 + countEvens(root->left) + countEvens(root->right);
        }
        return countEvens(root->left) + countEvens(root->right);
    }

    int height(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        int maxLeft = height(root->left);
        int maxRight = height(root->right);
        if(maxLeft > maxRight){
            return 1 + maxLeft;
        } else{
            return 1 + maxRight;
        }
    }

    int countLeaves(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        if(!root->left && !root->right){
            return 1;
        }
        return countLeaves(root->left) + countLeaves(root->right);
    }

};

int main(){
    BinTreeNode<int>* root = new BinTreeNode<int>(6);
    BinTreeNode<int>* node1 = new BinTreeNode<int>(4);
    BinTreeNode<int>* node2 = new BinTreeNode<int>(3);
    BinTreeNode<int>* node3 = new BinTreeNode<int>(7);
    BinTreeNode<int>* node4 = new BinTreeNode<int>(5);

    root->left = node1;
    root->right = node3;
    node1->left = node2;
    node1->right = node4;

    //     6
    //   4   7 
    //  3 5

    BinTree<int> binaryTree(root);

    std::cout << binaryTree.countLeaves(root);

}