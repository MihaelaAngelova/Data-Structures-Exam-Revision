// https://github.com/stranxter/lecture-notes/blob/master/samples/03_sdp/2022-23-is/trees/trees.cpp
#include <iostream>
#include <stack>
#include <cstring>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

template<class T>
struct BinTreeNode{
    T data;
    BinTreeNode* left;
    BinTreeNode* right;
    BinTreeNode(const T& data, BinTreeNode<T>* left = nullptr, BinTreeNode<T>* right = nullptr): 
                data(data), left(left), right(right){};
};

template<typename T>
class BinTree{
    private:
    BinTreeNode<T>* root;
    
    void clearHelper(BinTreeNode<T>*& root){
        if(root){
            clearHelper(root->left);
            clearHelper(root->right);
            delete root;
        }
        root = nullptr;
    }

    void insertHelper(BinTreeNode<T>*& root, const T& element){
        if(!root){
            root = new BinTreeNode<T>(element);
            return;
        }

        if(element >= root->data){
            insertHelper(root->right, element);
        } else{
            insertHelper(root->left, element);
        }
    }

    void removeHelper(BinTreeNode<T>*& root, T element){
        if(!root){
            throw std::runtime_error("Element not found!");
        }

        if(element < root->data){
            removeHelper(root->left, element);
        } else if(element > root->data){
            removeHelper(root->right, element);
        } else { // if element == root->data
            if(!root->left && !root->right){
                delete root;
                root = nullptr; 
            } else if(!root->left){
                BinTreeNode<T>* curr = root;
                root = root->right;
                delete curr;
            } else if(!root->right){
                BinTreeNode<T>* curr = root;
                root = root->left;
                delete curr;
            } else {
                root->data = minNum(root->right);
                removeHelper(root->right, root->data);
            }
        }
    }

     int searchHelper(BinTreeNode<T>*& root, bool (*pred)(const T&)){
        if(!root){
            return 0;
        }
        if(pred(root->data)){
            return 1 + searchHelper(root->left, pred) + searchHelper(root->right, pred);
        }
        return searchHelper(root->left, pred) + searchHelper(root->right, pred);
    }

    T& getElementHelper(BinTreeNode<T>*& root, const char* s){
        if(!root){
            throw std::runtime_error("Element not found!");
        }
        if(*s == '\0'){
            return root->data;
        }
        if(*s == 'L'){
            return getElementHelper(root->left, s+1);
        } else if(*s == 'R'){
            return getElementHelper(root->right, s+1);
        }
        throw std::runtime_error("You're doing it wrong.");
    }

    void findTraceHelper(BinTreeNode<T>*& root, const T& x, std::string& result, std::string path){
        if(!root){
            return;
        }

        if(x == root->data) {
            result = path;
            return;
        }

        findTraceHelper(root->left, x, result, path + "L");
        findTraceHelper(root->right, x, result, path + "R");
    }

    void getAtHelper(BinTreeNode<T>*& root, unsigned int& i, T& result){
        if(!root){
            throw std::out_of_range("Out of range!");
        }
        if(i == 0){
            result = root->data;
            return;
        }
        
        if(root->left){
            i--;
            getAtHelper(root->left, i, result);
        }

        if(root->right){
            i--;
            getAtHelper(root->right, i, result);
        }
    }

    BinTree<T> parseTreeHelper(std::istream& iss ){
        char c;
        T data;
        iss >> c;
        if(c == '('){
            iss >> data;
            BinTreeNode<T>* root = new BinTreeNode<T>(data);
            root->left = parseTreeHelper(iss).root;
            root->right = parseTreeHelper(iss).root;
            iss >> c;
            return BinTree<T>(root);
        } else if(c == ')'){
            return nullptr;
        } else {
            iss.putback(c);
            iss >> data;
            return BinTree<T>(new BinTreeNode<T>(data));
        }
    }

    public:
// constructor
    BinTree(BinTreeNode<T>* root = nullptr): root(root){};

// copy constructor
    BinTree(const BinTree<T>&other){
        root = copy(other.root);
    }

// for the copy constructor
    BinTreeNode<T>* copy(BinTreeNode<T>* other){
        if(!other){
            return nullptr;
        }
        return new BinTreeNode<T>(other->data, copy(other->left), copy(other->right));
    }

// for the destructor
    void clear(){
        clearHelper(root);
        root = nullptr;
    }

// destructor
    ~BinTree(){
        clear();
    }

// проверява дали елемент е част от дървото
    bool member(BinTreeNode<T>*& root, T element){
        if(!root){
            return false;
        }
        return element == root->data || member(root->left, element) || member(root->right, element);       
    }

// връща сумата от елементите на дървото
    T sum(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        return root->data + sum(root->left) + sum(root->right);
    }

    T maxNum (BinTreeNode<T>*& root)const { // same as maxLeaf
        BinTreeNode<T>* curr = root;
        while(curr->right){
            curr = curr->right;
        }
        return curr->data;
    }

    T minNum (BinTreeNode<T>*& root)const{
        BinTreeNode<T>* curr = root;
        while(root->left){
            curr = curr->left;
        }
        return curr->data;
    }

// Да се дефинира метод count на клас BinTree, който намира броя на елементите на дървото.
    int count(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        return 1 + count(root->left) + count(root->right);
    }

// Да се дефинира метод bool BinTree<T>::height(), намиращ височината на дърво.
    int height(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        if(leftHeight >= rightHeight){
            return 1 + leftHeight;
        }
        return 1 + rightHeight;
    }

// Да се дефинира метод leaves на клас BinTree, който намира броя на листата в дървото.
    int leaves(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        if(!root->left && !root->right){
            return 1;
        }
        return leaves(root->right) + leaves(root->left);
    }

// inserts an element
    void insert(const T& element){
        insertHelper(root, element);
    }

// removes an element
    void remove(T element){
        removeHelper(root, element);
    }

// prints inorder
    void print(BinTreeNode<T>* root){
        if(!root){
            return;
        }

        print(root->left);
        std::cout << root->data << " ";
        print(root->right);
    }

// Да се дефинира метод countEvens на клас BinTree, който намира броя на елементите на дърво от числа, които са четни.
    int countEvens(BinTreeNode<T>*& root){
        if(!root){
            return 0;
        }
        if(root->data %2 == 0){
            return 1 + countEvens(root->left) + countEvens(root->right);
        }
        return countEvens(root->left) + countEvens(root->right);
    }

// Даседефинираметодint BTree<T>::searchCount (bool (*pred)(const T&)) към клас BinTree, който намира броя на елементите 
// на дървото, които удовлетворяват предиката pred.
    int searchCount (bool (*pred)(const T&)){
        return searchHelper(root, pred);
    }

// Да се дефинира метод maxLeaf на клас BinTree, който намира най-голямото по стойност листо на непразно 
// дърво. Да се приеме, че за типа T на шаблона BinTree е дефиниран операторът <.
    T maxLeaf(BinTreeNode<T>*& root)const {
        if(root == nullptr){
            throw std::runtime_error("Empty tree!");
        }
        if(root->right){
            return maxLeaf(root->right);
        }
        return root->data;
    }

// getter
    T& getElement(const char* s)const {
        return getElementHelper(root, s);
    }

/*
ДаседефинирафункцияprettyPrint ([подходящ тип]t),отпечатваща двоично дърво на стандартния изход по следния начин: 
всеки наследник е вдясно от родителя си, елементите на еднакво ниво в дървото се отпечатват на еднаква колона
от екрана, десните наследници са на предишен ред от родителя си и левите наследници са следващ ред спрямо родителя си.
*/
    void prettyPrint(BinTreeNode<T>* root, int level, int offset) {
        if (root) {
            prettyPrint(root->right, level + 1, offset + 4);

            for (int i = 0; i < offset; i++) {
                std::cout << " ";
            }   

            std::cout << level << ": " << root->data << std::endl;

            prettyPrint(root->left, level + 1, offset + 4);
        }
    }

    void prettyPrint() {
        prettyPrint(root, 1, 0);
    }

// Да се дефинират функции std::string serializeTree ([подходящ тип]t) и BinTree<int> parseTree (std::string) за сериализация и
// десериализация на двоично дърво, съдържащо числа, като се използва “Scheme формат”.
    std::string serializeTree(BinTreeNode<T>*& root){
        if(!root){
            return "()";
        }

        std::ostringstream oss;

        oss << "(" << root->data << " " << serializeTree(root->left) << " " << serializeTree(root->right) << ")";

        return oss.str();
    }

    BinTree<T> parseTree(std::string s){
        std::istringstream iss(s);
        return parseTreeHelper(iss);
    }

// Да се реализира функция std::vector<T> listLeaves ([подходящ тип]t), намираща списък със стойностите на листата на дървото.
    std::vector<T> listLeaves(BinTreeNode<T>*& root){
        std::vector<T> leaves;
        if(!root){
            return leaves;
        }
        if(!root->left && !root->right){
            leaves.push_back(root->data);
        } else {
            std::vector<T> leftLeaves = listLeaves(root->left);
            std::vector<T> rightLeaves = listLeaves(root->right);

            leaves.insert(leaves.end(), leftLeaves.begin(), leftLeaves.end());
            leaves.insert(leaves.end(), rightLeaves.begin(), rightLeaves.end());
        }
        return leaves;
    }

// Да се дефинира функция std::string findTrace ([подходящ тип]t, const T& x). Ако x е елемент на дървото, функцията да връща
// следата на x (според дефиницията на “следа”, обсъдена на лекции). Ако x не е елемент на дървото, функцията да връща низа “_”.
    std::string findTrace(BinTreeNode<T>*& root, const T& x){
        std::string result = "_";
        findTraceHelper(root, x, result, "");
        return result;
    }

// Да се дефинира функция T getAt([подходящ тип]t, size_t i), която намира i-тия пореден елемент на дървото при обхождане корен-ляво-дясно.
    T getAt(BinTreeNode<T>*& root, unsigned int i){
        T result = T();
        getAtHelper(root, i, result);
        return result;
    }

/*
Нека е дадено двоично дърво, чиито възли съдържат символи (char). Да се намери:
а) Най-дългия символен низ, който може да се получи при последователно конкатениране на символите от корена на дървото по пътя до някое
негово листо.
б) Най-дългия символен низ, който може да се получи при конкатениране на символите по възлите на някое ниво в дървото, отляво надясно.
*/

    void dfs(const BinTreeNode<T>* root, std::string& currPath, std::string& longestPath)const{
        if(!root){
            return;
        }

        currPath += root->data;

        if(!root->left && !root->right){
            if(currPath.length() > longestPath.length()){
                longestPath = currPath;
            }
        }

        dfs(root->left, currPath, longestPath);
        dfs(root->right, currPath, longestPath);

        currPath.pop_back();
    }

    std::string longestCharArray(const BinTreeNode<T>* root)const{
        if(!root){
            return "";
        }

        std::string currentPath = "";
        std::string longestPath = "";

        dfs(root, currentPath, longestPath);

        return longestPath;
    }

    void printInorder(const BinTreeNode<T>*& root)const{ // dfs
        if(!root){
            return;
        }
        printInorder(root->left);
        std:: cout << root->data << " ";
        printInorder(root->left);
    }

    void printCurrentLevel(const BinTreeNode<T>* root, int level)const{
        if(!root){
            return;
        }
        if(level == 1){
            std::cout << root->data << " ";
        } else if(level > 1){
            printCurrentLevel(root->left, level - 1);
            printCurrentLevel(root->right, level - 1);
        }
    }

    void levelOrderTraversal(BinTreeNode<T>* root){ // bfs
        if(!root){
            return;
        }
        BinTreeNode<T>* curr = root;
        std::queue<BinTreeNode<T>*> q;
        q.push(curr);
        while (!q.empty()){
            curr = q.front();
            q.pop();
            std::cout << curr->data;
            if(curr->left){
                q.push(curr->left);
            }
            if(root->right){
                q.push(curr->right);
            }
        }
    }

    std::string longestConcatenatedString(BinTreeNode<T>* root){
        if(!root){
            return "";
        }
        std::string longestString = "";
        std::queue<BinTreeNode<T>*> q;
        q.push(root);
        while(!q.empty()){
            int levelSize = q.size();
            std::string currentLevelString = "";
            for(int i = 0; i < levelSize; i++){
                BinTreeNode<T>* curr = q.front();
                q.pop();
                currentLevelString += curr->data;

                if(curr->left){
                    q.push(curr->left);
                }
                if(curr->right){
                    q.push(curr->right);
                }
            }
            if(currentLevelString.length() > longestString.length()){
                longestString = currentLevelString;
            }
        }
        return longestString;
    }

// Нека са дадени две дървета t1 и t2. Да се напише функция bool equals([подходящ тип] t1,[подходящ тип] t2), която проверява дали
// двете дървета са еднакви (използвайте интуитивна дифиниция за еднаквост на дървета).
    bool equals(BinTreeNode<T>* root1, BinTreeNode<T>* root2){
        if(!root1 && !root2){
            return true;
        }
        if(!root1 || !root2){
            return false;
        }
        if(root1->data != root2->data){
            return false;
        }
        return equals(root1->left, root->left) && equals(root1->right, root2->right);
    }

// Нека са дадени две дървета t1 и t2. Да се напише функция bool subtree([подходящ тип] t1,[подходящ тип] t2), която проверява дали
// някое поддърво на t1 е еднакво с t2. 
    bool subtree(BinTreeNode<T>* root1, BinTreeNode<T>* root2){
        if(!root2){
            return true;
        }
        if(!root1){
            return false;
        }
        if(equals(root1, root2)){
            return true;
        }
        return subtree(root1->left, root2) || subtree(root1->right, root2);
    }

    BinTreeNode<T>* buildBalancedTree(int level, int maxLevel){
        if(level > maxLevel){
            return nullptr;
        }
        BinTreeNode<T>* root = new BinTreeNode<T>(level);
        root->left = buildBalancedTree(level + 1, maxLevel);
        root->right = buildBalancedTree(level + 1, maxLevel);
        return root;
    }

    void topView(BinTreeNode<T>* root){
        if(!root){
            return;
        }

        std::map<int, T>m;
        int hd = 0;
        std::queue<std::pair<int, BinTreeNode<T>*>> q;
        q.push(std::pair<int, BinTreeNode<T>*>(hd, root));
        while(!q.empty()){
            BinTreeNode<T>* temp = q.front().second;
            hd = q.front().first;
            q.pop();
            if(m.find(hd) == m.end()){
                m.insert(std::pair<int, T>(hd, temp->data));
            }
            if(temp->left){
                q.push(std::pair<int, BinTreeNode<T>*>(hd-1,temp->left));
            }
            if(temp->right){
                q.push(std::pair<int, BinTreeNode<T>*>(hd+1, temp->right));
            }
        }
        for(auto it = m.begin(); it != m.end(); it++){
            std:: cout << it->second << " ";
        }
    }
};

template <typename T>
struct TNode {
    T data;
    std::vector<TNode*> children;
};

template <typename T>
bool ordered_levels (TNode<T>* head){
    if(!head){
        return true;
    }
    if(head->children.empty()){
        return true;
    }

    std::queue<TNode<T>*>q;
    int levelSize = head->children.size();

    for(int i = 0; i < head->children.size(); i++){
        q.push(head->children[i]);
    }

    int visited = 1;
    TNode<T>* prev = nullptr;
    while(!q.empty()){
        TNode<T>* curr = q.front();
        q.pop();

        if(prev && prev->data > curr->data){
            return false;
        }

        for(int i = 0; i < curr->children.size(); i++){
            q.push(curr->children[i]);
        }

        if(levelSize == visited) {
            prev = nullptr;
            visited = 1;
            levelSize = q.size();
        } else {
            prev = curr;
            visited++;
        }
    }

    return true;
}

typedef unsigned long Row;
typedef std::pair<Row, char> Key;

template <typename T>
class Spreadsheet {

    private:
    std::map<Key, T> m;

    public:

    Spreadsheet(): m() {}

    void set(Row row, char col, const T& value) {
        if ('A' > col || col > 'Z') {
            return;
        }
        
        // m.insert(std::pair<Key, T>(Key(row, col), value)); // alternative way
        m[Key(row, col)] = value;
    }

    T get(Row row, char col) const {
        if (m.find(Key(row, col)) != m.end()) {
            return m[Key(row, col)];
        } else {
            return T();
        }
    }

    T max() const {
        T result = m.begin()->second;
        for (auto it = m.begin() + 1; it != m.end(); it++) {
            if (result <= it->second) {
                result = it->second;
            }
        }
        return result;
    }
};


bool isEven(const int& value) {
    return value % 2 == 0;
}

int main(){
    /*
    BinTreeNode<int>* root = new BinTreeNode<int>(5);
    BinTreeNode<int>* node1 = new BinTreeNode<int>(3);
    BinTreeNode<int>* node2 = new BinTreeNode<int>(8);
    BinTreeNode<int>* node3 = new BinTreeNode<int>(2);
    BinTreeNode<int>* node4 = new BinTreeNode<int>(4);

    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    

    //    5
    //   / \'
    //  3   8
    // / \'
    //2   4

    BinTree<int> binaryTree{root};

    std::cout << binaryTree.member(root, 7) << std::endl;
    binaryTree.insert(7);
    std::cout << binaryTree.member(root, 2) << std::endl;
    binaryTree.remove(7);
    std::cout << binaryTree.member(root, 7) << std::endl;
    binaryTree.print(root);
    std::cout << std::endl;

    char arr[] = "LL";
    std::cout << binaryTree.getElement(arr);
    std:: cout << std::endl << "___________________________" << std::endl;
    std::cout << binaryTree.findTrace(root, 8) << std::endl;
    std::cout << binaryTree.getAt(root, 4);
    */

    BinTreeNode<char>* root = new BinTreeNode<char> ('a');
    root->left = new BinTreeNode<char> ('b');
    root->right = new BinTreeNode<char> ('c');
    root->left->left = new BinTreeNode<char> ('d');
    root->left->right = new BinTreeNode<char> ('e');
    root->right->right = new BinTreeNode<char> ('f');

    BinTree<char> binaryTree{root};

    std::string result = binaryTree.longestConcatenatedString(root);
    std::cout << result << std::endl;

}