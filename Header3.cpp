#include "Header3.h"
#include "string"
#include <iostream>

q3::BinaryTree::Node::Node() {
	this->left = nullptr;
	this->right = nullptr;
	this->next = nullptr;
}
q3::BinaryTree::Node::Node(char value) {
	this->value = value;
	this->left = nullptr;
	this->right = nullptr;
	this->next = nullptr;
}


void q3::BinaryTree::inorder(Node* z)
{
	if (z == nullptr) {
		return;
	};

	inorder(z->left);

	std::cout << z->value;

	inorder(z->right);

}

void q3::BinaryTree::simplify_tree(Node* node)
{
	if (node == nullptr)
		return;

	simplify_tree(node->left);
	simplify_tree(node->right);

	if (node->value == '&') {
		if ((node->left)->value == '0' || (node->right)->value == '0') {
			distructtree(node->left);
			node->left = nullptr;
			distructtree(node->right);
			node->right = nullptr;
			node->value = '0';
		}
	}
	else if (node->value == '|') {
		if ((node->left)->value == '1' || (node->right)->value == '1') {
			distructtree(node->left);
			node->left = nullptr;
			distructtree(node->right);
			node->right = nullptr;
			node->value = '1';
		}
	}
	else if (node->value == '-') {
		if ((node->left)->value != 'x') {
			if ((node->left)->value == '0') {
				node->value = '1';
				distructtree(node->left);
				node->left = nullptr;
			}
			else if ((node->left)->value == '1') {
				node->value = '0';
				distructtree(node->left);
				node->left = nullptr;
			}
		}
	}

}

void q3::BinaryTree::distructtree(Node* dek)
{
	Node* temp = dek;
	while (dek != nullptr) {
		temp = temp->next;
		delete dek;
		dek = temp;
	}
	delete temp;
}

bool q3::BinaryTree::evalute(Node* node)
{
	if (node == nullptr)
		return 0;
	int x = evalute(node->left);
	int y = evalute(node->right);

	int result = 0;

	if (node->value == '0')
		return 0;
	else if (node->value == '1')
		return 1;
	else if (node->value == 'x')
		return 1;
	else if (node->value == '&')
		result = x && y ? 1 : 0;

	else if (node->value == '|') {
		result = x || y ? 1 : 0;
	}

	else if (node->value == '-') {
		if (x == 1)
			result = 0;
		else
			result = 1;
	}
	return result;


}

void q3::BinaryTree::build_expression_tree(int size, char* s)
{
	char k;
	q3::Stack<Node*> numbers = q3::Stack<Node*>();
	Node* x = new Node();
	Node* y = new Node();
	Node* z = new Node();

	for (int i = 0; i < size; i++) {
		if (s[i] == '&' || s[i] == '|') {
			z = new Node(s[i]);
			x = numbers.pop();
			y = numbers.pop();
			z->left = y;
			z->right = x;
			numbers.push(z);
		}
		else if (s[i] == '-') {
			z = new Node(s[i]);
			x = numbers.pop();
			z->left = x;
			numbers.push(z);
		}
		else {
			x = new Node(s[i]);
			numbers.push(x);
		}
	}

	std::cout << '\n';
	std::cout << '\n';
	std::cout << "Look of tree before simplifying:       ";
	inorder(z);
	std::cout << '\n';
	simplify_tree(z);
	std::cout << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "Look of tree after simplifying:         ";
	inorder(z);
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "---------------------------------------------";
	std::cout << '\n';
	std::cout << "Result using tree after simplifying:       ";
	std::cout << evalute(z);
	std::cout << '\n';
	std::cout << "---------------------------------------------";
	std::cout << '\n';

	return;
}


void q3::BinaryTree::create_rpn(char* func, int size)
{
	char* finish = new char[size];
	int index_finish = 0;

	q3::Stack<char> stack = q3::Stack<char>();
	q3::Map mp = q3::Map();

	mp.addtomap('&', 1);
	mp.addtomap('|', 1);
	mp.addtomap('-', 2);
	mp.addtomap('(', 3);
	mp.addtomap(')', 3);


	for (int i = 0; i < size; i++) {
		if (func[i] == '&' || func[i] == '|' || func[i] == '-' || func[i] == ')' || func[i] == '(') {
			if (stack.arr[0] == NULL) {
				if (func[i] == ')') {
					std::cout << "Error";
					return;
				}
				stack.push(func[i]);
			}

			else if (func[i] == ')') {
				while (stack.arr[stack.index] != '(') {
					if (stack.index == 0) {
						std::cout << "Error";
						return;
					}

					finish[index_finish] = stack.pop();
					index_finish++;
				}
				char k = stack.pop();

			}
			else if (func[i] == '(' || mp.give_val(func[i]) > mp.give_val(stack.arr[stack.index]))
				stack.push(func[i]);

			else if (mp.give_val(func[i]) <= mp.give_val(stack.arr[stack.index])) {
				while ((mp.give_val(func[i]) <= mp.give_val(stack.arr[stack.index])) && (stack.arr[stack.index] != '(')) {

					finish[index_finish] = stack.pop();
					index_finish++;
					if (stack.arr[0] == NULL) {
						break;
					}
				}
				stack.push(func[i]);
			}
		}
		else {
			finish[index_finish] = func[i];
			index_finish++;
		}

	}
	while (stack.arr[0] != NULL) {
		finish[index_finish] = stack.pop();
		index_finish++;
	}


	for (int i = 0; i < index_finish; i++) {
		std::cout << finish[i];
	}

	build_expression_tree(index_finish, finish);
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "If rpn version :     ";
	functionate(1, finish, index_finish);

}


void q3::BinaryTree::functionate(int value, char* func, int size)
{
	Stack<int> stack = Stack<int>();

	int i = 0;
	while (i < size) {
		if (int(func[i]) == 48 || int(func[i]) == 49 || func[i] == 'x') {
			if (func[i] == 'x')
				stack.push(value + '0');
			else
				stack.push(func[i]);
		}
		else if (func[i] == '&' || func[i] == '|' || func[i] == '-') {
			int result = 0;
			int x, y;

			if (stack.arr[0] != NULL)
				x = stack.pop() - '0';

			if ((stack.arr[0] != NULL) && (func[i] != '-'))
				y = stack.pop() - '0';
			else if ((stack.arr[0] == NULL) && (func[i] != '-')) {
				std::cout << "Error";
				return;
			}
			if (func[i] == '&')
				result = x && y ? 1 : 0;

			else if (func[i] == '|')
				result = x || y ? 1 : 0;

			else if (func[i] == '-') {
				if (x == 1)
					result = 0;
				else
					result = 1;
			}

			stack.push(result + '0');

		}
		else {

			return;
		}
		i++;
	}
	if (stack.index != 0)
		return;
	std::cout << "Result:      " << stack.pop() - '0';

}
q3::Map::KeyVal::KeyVal(char key, int val)
{
	this->key = key;
	this->val = val;
	this->next = nullptr;

}

void q3::Map::addtomap(char key, int val)
{
	KeyVal* node = new KeyVal(key, val);
	if (head == nullptr && tail == nullptr) {
		tail = node;
		head = node;
	}
	else {
		tail->next = node;
		tail = node;
	}
}

int q3::Map::give_val(char key)
{
	KeyVal* temp = head;
	while (true) {
		if (temp->key == key)
			return temp->val;
		if (temp->next == nullptr) {
			std::cout << "Error";
			return 0;
		}
		temp = temp->next;
	}
}