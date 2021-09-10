
// Project 1 AVL Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <istream>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
	string name;
	int id;
	int height;
	Node* left;
	Node* right;

	Node() {
		this->name = "";
		this->id = -1;
		this->height = -1;
		this->left = nullptr;
		this->right = nullptr;

	}
	Node(string name, int id, int height) {
		this->name = name;
		this->id = id;
		this->height = height;
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(string name, int id, int height, Node* left, Node* right) {
		this->name = name;
		this->id = id;
		this->height = height;
		this->left = left;
		this->right = right;
	}

	//Copy constructor

	Node(const Node*& obj) {
		this->name = obj->name;
		this->id = obj->id;
		this->height = obj->height;
		this->left = obj->left;
		this->right = obj->right;
	}

	Node& operator=(const Node& obj) {

		if (this != &obj) {
			this->name = obj.name;
			this->id = obj.id;
			this->height = obj.height;
			this->left = obj.left;
			this->right = obj.right;
		}
		return *this;
	}

	void setLeft(Node* n) {

		this->left = n;

	}

	void setRight(Node* n) {

		this->right = n;

	}
};

Node* insertName(string& name, int& id, Node* heap);
Node* removeID(int& id, Node* root, Node* firstRoot);
bool search(int& ID, Node* root, bool found);
int search(string& name, Node* root, bool found);
void printInorder(Node* root, string delimiter);
void printPreorder(Node* root, bool isFirst);
void printPostorder(Node* root, string delimiter);
int printLevelCount(Node* root);
bool removeInorderN(Node* root, int n, int traverseNum, Node* firstRoot);
Node* rotateLeft(Node* root);
Node* rotateRight(Node* root);
Node* rotateLeftRight(Node* root);
Node* rotateRightLeft(Node* root);
Node* rebalance(Node* root);

int main()
{

	string x, y;

	Node* heap = nullptr;

	while (std::getline(cin, y)) {

		x = y.substr(0, y.find(' '));

		if (x == "insert") {

			string name = y.substr(y.find('\"') + 1, y.find_last_of("\" ") - y.find('\"') - 2);

			string tempID = y.substr(y.find_last_of("\" ")+1, y.find('\0'));

			bool isGood = false;

			if (tempID.size() != 8) {

				isGood = false;

			}

			else {

				int id = stoi(tempID);

				heap = insertName(name, id, heap);

				isGood = true;
			}


			if (heap == nullptr || isGood == false) {

				cout << "unsuccessful" << endl;

			}


			else {

				cout << "successful" << endl;

			}


		}
		if (x == "search") {

			if (y.find('\"') == string::npos) {

				int id = stoi(y.substr(y.find(' '), y.find('\0')));

				if (search(id, heap, false) == false) {

					cout << "unsuccessful" << endl;

				}

			}


			else {

				string name = y.substr(y.find('\"') + 1, y.find_last_of("\" ") - y.find('\"') - 1);

				if (search(name, heap, false) == false) {

					cout << "unsuccessful" << endl;

				}

			}

		}


		if (x == "remove") {

			int id = stoi(y.substr(y.find(' '), y.find('\0')));

			heap = removeID(id, heap, heap);

			if (heap) {

				cout << "successful" << endl;

			}

			else {

				cout << "unsuccessful" << endl;

			}

		}


		if (x == "printInorder") {
			cout << heap->name << endl;
			printInorder(heap, ", ");

			cout << endl;

		}


		if (x == "removeInorder") { // Needs work

			int n = stoi(y.substr(y.find(' '), y.find('\0')));

			if (removeInorderN(heap, n, 0, heap)) {

				cout << "successful" << endl;

			}

			else {

				cout << "unsuccessful" << endl;

			}

		}


		if (x == "printPreorder") {

			printPreorder(heap, true);

			cout << endl;

		}


		if (x == "printPostorder") {

			printPostorder(heap, "");

			cout << endl;

		}


		if (x == "printLevelCount") {

			cout << printLevelCount(heap) << endl;

		}


	}


}


Node* insertName(string& name, int& id, Node* root) {

	if (root == nullptr) {

		root = new Node(name, id, 1);

		return root;

	}


	else if (root->id == id) {

		return nullptr;
	}


	if (root->id < id) {

		root->right = insertName(name, id, root->right);

		if (root->right == nullptr) {

			return nullptr;

		}

	}


	if (root->id > id) {

		root->left = insertName(name, id, root->left);

		if (root->left == nullptr) {

			return nullptr;

		}

	}



	if (root->left == nullptr && root->right != nullptr) {

		root->height = root->right->height + 1;

	}


	else if (root->left != nullptr && root->right == nullptr) {

		root->height = root->left->height + 1;

	}


	else if (root->left == nullptr && root->right == nullptr) {

		root->height = 1;

	}


	else {

		root->height = ((root->left->id > root->right->id) ? root->left->height : root->right->height) + 1;

	}

	rebalance(root);

}

Node* rebalance(Node* root) {

	if (root == nullptr) {

		return root;

	}


	int leftHeight = (root->left == nullptr) ? 0 : root->left->height;

	int rightHeight = (root->right == nullptr) ? 0 : root->right->height;

	int balanceFactor = leftHeight - rightHeight;

	root->height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;

	//Rebalance
	//Left left
	if (balanceFactor > 1 && root->left != nullptr && root->left->id < root->id) {

		return rotateRight(root);

	}
	//Right right
	if (balanceFactor < -1 && root->right != nullptr && root->right->id < root->id) {

		return rotateLeft(root);

	}

	//Left right
	if (balanceFactor > 1 && root->id > root->id) {

		return rotateLeftRight(root);

	}

	//Right left
	if (balanceFactor<-1 && root->id > root->id) {

		return rotateLeftRight(root);

	}

	return root;
}


Node* removeID(int& id, Node* root, Node* firstRoot) {

	if (root == nullptr) {

		return root;

	}

	else if (root->id > id) {

		root = removeID(id, root->left, firstRoot);

	}

	else if (root->id < id) {

		root = removeID(id, root->right, firstRoot);
	
	}

	else if (root->id == id) {

		//If id is found
		//Case if root has right child
		if (root->right) {

			Node* rightChild = root->right;

			Node* grandChild = root->right->left;

			Node* iterator = root->right->left;

			//Case if root right node has more than 1 left child
			if (iterator) {

				rightChild->height = rightChild->height - 1;

				while (iterator) {

					if (iterator->left == nullptr) {

						Node* temp = iterator->right;

						iterator->right = rightChild;

						iterator->left = root->left;

						iterator->height = root->height - 1;

						delete root;

						root = new Node(iterator->name, iterator->id, iterator->height, iterator->left, iterator->right);

						Node* deletedNode = root->right;

						while (deletedNode != nullptr) {

							if (deletedNode->left->id == root->id) {

								if (deletedNode->left->right) {

									deletedNode->left = temp;

								}

								else {

									deletedNode->left == nullptr;

								}

								break;
							}

							deletedNode = deletedNode->left;
						}
						break;
					}

					else if (iterator->left->left == nullptr) {

						iterator->height = iterator->height - 1;

						Node* temp = iterator->left;

						iterator->left = nullptr;

						iterator = temp;

					}

					else {

						iterator->height = iterator->height - 1;

						iterator = iterator->left;

					}

				}

				return root;

			}
			//Case if root right node has no left child, root right node is next inheritance
			else {

				rightChild->left = root->left;

				rightChild->height = root->height - 1;

				root = rightChild;

				Node* traversalNode = firstRoot;

				while (traversalNode != nullptr) {

					if (traversalNode->id = firstRoot->id) {

						delete firstRoot;

						firstRoot = new Node(rightChild->name, rightChild->id, rightChild->height, rightChild->left, rightChild->right);

						traversalNode = firstRoot;

						break;

					}

					if (id == traversalNode->id) {

						delete root;

						root = new Node(rightChild->name, rightChild->id, rightChild->height, rightChild->left, rightChild->right);

						traversalNode = root;

						break;

					}


					if (id < traversalNode->id) {

						if (traversalNode->right->id != id) {

							traversalNode = traversalNode->right;

						}
						else {

							traversalNode->right = root;

							break;

						}

					}


					else if (id > traversalNode->id) {

						if (traversalNode->left->id != id) {

							traversalNode = traversalNode->left;

						}

						else {

							traversalNode->left = root;

							break;

						}
					}

				}
			}

		}

		//Case if root has no right child, root leftmost leaf is next inherited node
		else if (root->left) {

			Node* leftChild = root->left;

			leftChild->right = nullptr;

			leftChild->height = root->height - 1;

			root = leftChild;

			Node* traversalNode = firstRoot;

			while (traversalNode != nullptr) {

				if (traversalNode->id == firstRoot->id) {

					delete firstRoot;

					firstRoot = new Node(leftChild->name, leftChild->id, leftChild->height, leftChild->left, leftChild->right);

					traversalNode = firstRoot;

					break;

				}


				if (id == traversalNode->id) {

					delete root;

					root = new Node(leftChild->name, leftChild->id, leftChild->height, leftChild->left, leftChild->right);

					traversalNode = root;

					break;

				}

				if (id > traversalNode->id) {

					if (traversalNode->right->id != id) {

						traversalNode = traversalNode->right;

					}

					else {

						traversalNode->right = root;

						break;

					}

				}

				else if (id < traversalNode->id) {

					if (traversalNode->left->id != id) {

						traversalNode = traversalNode->left;

					}

					else {

						traversalNode->left = root;

						break;

					}
				}

			}
		}

		//Case where there is no child
		else {

			Node* traversalNode = firstRoot;

			while (traversalNode != nullptr) {

				if (traversalNode->id == root->id) {

					delete firstRoot;

					firstRoot = new Node();

					firstRoot = nullptr;

					traversalNode = firstRoot;

					break;

				}

				if (traversalNode->left->id == root->id) {

					delete traversalNode->left;

					traversalNode->left = new Node();

					traversalNode->left = nullptr;

					break;

				}


				if (traversalNode->right->id == root->id) {

					delete traversalNode->right;

					traversalNode->right = new Node();

					traversalNode->right = nullptr;

					break;

				}


				else if (id > traversalNode->id) {

					if (traversalNode->right->id != id) {

						traversalNode = traversalNode->right;

					}

					else {

						traversalNode->right = nullptr;

						break;

					}

				}


				else if (id < traversalNode->id) {

					if (traversalNode->left->id != id) {

						traversalNode = traversalNode->left;

					}

					else {

						traversalNode->left = nullptr;

						break;
					}
				}

			}

		}

		rebalance(root);

		return firstRoot;

	}
}

bool search(int& ID, Node* root, bool found) {

	if (root == nullptr) {

		return false;

	}

	if (ID == root->id) {

		cout << root->name << endl;

		found = true;

		return true;

	}

	if (found == true) {

		return found;

	}

	found = search(ID, root->left, found);

	if (found == true) {

		return found;

	}

	found = search(ID, root->right, found);

	if (found == true) {

		return found;

	}

	return found;

}

int search(string& name, Node* root, bool found) {

	if (root == nullptr) return found;

	if (name == root->name) {

		cout << root->id << endl;

		found = true;

	}

	found += search(name, root->left, found);

	found += search(name, root->right, found);

}

void printInorder(Node* root, string delimiter) {

	if (root != nullptr) {

		if (root->left != nullptr) {

			printInorder(root->left, delimiter);

		}

		if (root->left) { cout << delimiter; }

		cout << root->name;

		if (root->right) { cout << delimiter; }

		if (root->right != nullptr) {

			printInorder(root->right, delimiter);

		}

	}

}

void printPreorder(Node* root, bool isFirst) {

	if (root != nullptr) {

		if (isFirst) {

			cout << root->name;

		}
		else {

			cout << ", " << root->name;

		}

		if (root->left != nullptr) {

			printPreorder(root->left, false);

		}

		if (root->right != nullptr) {

			printPreorder(root->right, false);

		}

	}

}

void printPostorder(Node* root, string delimiter) {

	if (root != nullptr) {

		if (root->left != nullptr) {

			printPostorder(root->left, ", ");

		}
		if (root->right != nullptr) {

			printPostorder(root->right, ", ");

		}

		cout << root->name + delimiter;

	}
}

int printLevelCount(Node* root) {

	if (root == nullptr) {

		return 0;

	}

	int leftHeight = 1 + printLevelCount(root->left);

	int rightHeight = 1 + printLevelCount(root->right);

	if (leftHeight > rightHeight) {

		return leftHeight;

	}
	else {

		return rightHeight;

	}

}


bool removeInorderN(Node* root, int n, int traverseNum, Node* firstRoot) {

	if (root != nullptr) {

		removeInorderN(root->left, n, traverseNum++, firstRoot);

		if (traverseNum == n) {

			removeID(root->id, root, firstRoot);

			return true;

		}

		removeInorderN(root->right, n, traverseNum++, firstRoot);

	}

	else {

		return false;

	}
}

Node* rotateLeft(Node* root) {

	Node* grandChild = root->right->left;

	Node* newParent = root->right;

	newParent->left = root;

	root->right = grandChild;

	return newParent;

}

Node* rotateRight(Node* root) {

	Node* grandChild = root->left->right;

	Node* newParent = root->left;

	newParent->right = root;

	root->left = grandChild;

	return newParent;

}

Node* rotateLeftRight(Node* root) {

	Node* rLeft = rotateLeft(root->left);

	root->left = rLeft;

	Node* rLRight = rotateRight(root);

	return rLRight;

}

Node* rotateRightLeft(Node* root) {

	Node* rRight = rotateRight(root->left);

	root->right = rRight;

	Node* rRLeft = rotateLeft(root);

	return rRLeft;

}

