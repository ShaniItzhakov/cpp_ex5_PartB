#pragma once
#include <iostream>
#include <queue>

namespace ariel {
    template<typename T>
    class BinaryTree {
    private:
        struct Node {
            T value;
            Node* leftNode;
            Node* rightNode;
            Node* parentNode;
            Node(const T& val) : value(val), leftNode(nullptr), rightNode(nullptr), parentNode(nullptr){}
        };
        Node* root;

    public:
        class Iterator_pre_order {
        private:
            Node* pNode_pre_order;
            std::queue<Node*> stack_pre_order;
        public:
            Iterator_pre_order(Node *ptr) : pNode_pre_order(ptr) {
                if(ptr == nullptr) {
                    return;
                }
                addToStack(pNode_pre_order);
                pNode_pre_order = stack_pre_order.front();
                stack_pre_order.pop();
            }
            
            T& operator*() const {
                return pNode_pre_order->value;
            }

            T* operator->() const {
                return &(pNode_pre_order->value);
            }

            void addToStack(Node* currentNode) {
                if (currentNode == nullptr) {
                    return;
                }
                stack_pre_order.push(currentNode);
                addToStack(currentNode->leftNode);
                addToStack(currentNode->rightNode);
            }

            Iterator_pre_order& operator++() { // ++i
               if (stack_pre_order.empty()) {
                    pNode_pre_order = nullptr;
                    return *this;
                }
                pNode_pre_order = stack_pre_order.front();
                stack_pre_order.pop();
                return *this;
            }

            Iterator_pre_order operator++(int flag) { // i++
                Iterator_pre_order temp = *this;
                if (!stack_pre_order.empty()) {
                    pNode_pre_order = stack_pre_order.front();
                    stack_pre_order.pop();
                }
                else {
                    pNode_pre_order = nullptr;
                }
                return temp;
            }

            bool operator==(const Iterator_pre_order& bt) const {
                return pNode_pre_order == bt.pNode_pre_order;
            }

            bool operator!=(const Iterator_pre_order& bt) const {
                return pNode_pre_order != bt.pNode_pre_order;
            }
        };

        class Iterator_in_order {
        private:
            Node* pNode_in_order;
            std::queue<Node*> stack_in_order;
        public:
            Iterator_in_order(Node *ptr) : pNode_in_order(ptr) {
                if(ptr == nullptr) {
                    return;
                }
                addToStack(pNode_in_order);
                pNode_in_order = stack_in_order.front();
                stack_in_order.pop();
            }

            T& operator*() const {
                return pNode_in_order->value;
            }

            T* operator->() const {
                return &(pNode_in_order->value);
            }

            void addToStack(Node* currentNode) {
                if (currentNode == nullptr) {
                    return;
                }
                addToStack(currentNode->leftNode);
                stack_in_order.push(currentNode);
                addToStack(currentNode->rightNode);
            }

            Iterator_in_order& operator++() { // ++i
                if (stack_in_order.empty()) {
                    pNode_in_order = nullptr;
                    return *this;
                }
                pNode_in_order = stack_in_order.front();
                stack_in_order.pop();
                return *this;
            }

            Iterator_in_order operator++(int flag) { // i++
                Iterator_in_order temp = *this;
                if (!stack_in_order.empty()) {
                    pNode_in_order = stack_in_order.front();
                    stack_in_order.pop();
                }
                else {
                    pNode_in_order = nullptr;
                }
                return temp;
            }

            bool operator==(const Iterator_in_order& bt) const {
                return pNode_in_order == bt.pNode_in_order;
            }

            bool operator!=(const Iterator_in_order& bt) const {
                return pNode_in_order != bt.pNode_in_order;
            }
        };

        class Iterator_post_order {
        private:
            Node* pNode_post_order;
            std::queue<Node*> stack_post_order;
        public:
            Iterator_post_order(Node *ptr) : pNode_post_order(ptr) {
                if(ptr == nullptr){
                    return;
                }
                addToStack(pNode_post_order);
                pNode_post_order = stack_post_order.front();
                stack_post_order.pop();
            }

            T& operator*() const {
                return pNode_post_order->value;
            }

            T* operator->() const {
                return &(pNode_post_order->value);
            }

            void addToStack(Node* currentNode) {
                if (currentNode == nullptr) {
                    return;
                }
                addToStack(currentNode->leftNode);
                addToStack(currentNode->rightNode);
                stack_post_order.push(currentNode);
            }

            Iterator_post_order& operator++() { // ++i
                if (stack_post_order.empty()) {
                    pNode_post_order = nullptr;
                    return *this;
                }    
                pNode_post_order = stack_post_order.front();
                stack_post_order.pop();
                return *this;
            }

            Iterator_post_order operator++(int flag) { // i++
                Iterator_post_order temp = *this;
                if (!stack_post_order.empty()) {
                    pNode_post_order = stack_post_order.front();
                    stack_post_order.pop();
                }
                else {
                    pNode_post_order = nullptr;
                }
                return temp;
            }

            bool operator==(const Iterator_post_order& bt) const {
                return pNode_post_order == bt.pNode_post_order;
            }

            bool operator!=(const Iterator_post_order& bt) const {
                return pNode_post_order != bt.pNode_post_order;
            }
        };
        // Binary tree functions
        BinaryTree() : root(nullptr) {}

        ~BinaryTree() {
           deleteTree(root);
        }

        void deleteTree(Node* currentNode) {
            if (currentNode != nullptr) {
                deleteTree(currentNode->leftNode);
                deleteTree(currentNode->rightNode);
                delete currentNode;
                this->root = nullptr;
            }
        }

        BinaryTree(const BinaryTree& otherBT) : root(nullptr) {
            add_root(otherBT.root->value);
            addNodes(otherBT.root, this->root);
        }
        
        BinaryTree& operator=(const BinaryTree& otherBT) {
            if (this == &otherBT) {
                return *this;
            }
            if (root != nullptr) {
                deleteTree(root);
            }
            add_root(otherBT.root->value);
            addNodes(otherBT.root, this->root);
            return *this;
        }

        void addNodes(Node* srcNode, Node* destNode) {
            if (srcNode->leftNode != nullptr) {
                add_left(destNode->value, srcNode->leftNode->value);
                addNodes(srcNode->leftNode, destNode->leftNode);
            }

            if (srcNode->rightNode != nullptr) {
                add_right(destNode->value, srcNode->rightNode->value);
                addNodes(srcNode->rightNode, destNode->rightNode);
            }
        }

        BinaryTree& add_root(const T& root) {
            if (this->root != nullptr) {
                this->root->value = root;
            }
            else {
                this->root = new Node(root);
            }
            return *this;
        }

        BinaryTree& add_left(const T& value, const T& leftValue) {
            Node* node = findNodeByValue(value, root);
            if (node == nullptr) {
                throw std::invalid_argument("Cannot insert to unexisting node in the tree");
            }
            if (node->leftNode == nullptr) {
                Node* left_node = new Node(leftValue);
                // connect parent and left node
                node->leftNode = left_node;
                left_node->parentNode = node;  
            }
            else {
                node->leftNode->value = leftValue;
            }
            return *this;
        }

        BinaryTree& add_right(const T& value, const T& rightValue) {
            Node* node = findNodeByValue(value, root);
            if (node == nullptr) {
                throw std::invalid_argument("Cannot insert to unexisting node in the tree");
            }
            if (node->rightNode == nullptr) {
                Node* right_node = new Node(rightValue);
                // connect parent and right node
                node->rightNode = right_node;
                right_node->parentNode = node;  
            }
            else {
                node->rightNode->value = rightValue;
            }
            return *this;
        }

        Node* findNodeByValue(const T& value, Node* currentNode) {
            if (currentNode == nullptr) {
                return nullptr;
            }
            if (currentNode->value == value) {
                return currentNode;
            }
            Node* left = findNodeByValue(value, currentNode->leftNode);
            Node* right = findNodeByValue(value, currentNode->rightNode);
            if (left != nullptr) {
                return left;
            }
            return right;
        }

        // Move constructor and operator=:
	    BinaryTree(BinaryTree&& otherBT) noexcept {
		    root = otherBT.root;
		    otherBT.root = nullptr;
    	}

	    BinaryTree& operator=(BinaryTree&& otherBT) noexcept {
		    if (root != nullptr) {
                deleteTree(root);
            }
		    root = otherBT.root;
		    otherBT.root = nullptr;
            return *this;
	    }

        Iterator_pre_order begin_preorder() {
            return Iterator_pre_order{root};
        }

        Iterator_pre_order end_preorder() {
            return Iterator_pre_order{nullptr};
        }

        Iterator_in_order begin_inorder() {
            return Iterator_in_order{root};
        }

        Iterator_in_order end_inorder() {
            return Iterator_in_order{nullptr};
        }

        Iterator_post_order begin_postorder() {
            return Iterator_post_order{root};
        }

        Iterator_post_order end_postorder() {
            return Iterator_post_order{nullptr};
        }

        Iterator_in_order begin() {
            return begin_inorder();
        }

         Iterator_in_order end() {
            return end_inorder();
        }

        friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& bt) {
            std::cout << "Printing tree" << std::endl;
            return os;
        }
    };
}