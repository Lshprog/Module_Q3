#pragma once
#include <iostream>
namespace q3 {
	struct BinaryTree {
		struct Node {
			char value;
			Node* left;
			Node* right;
			Node* next;
			Node();
			Node(char value);
		};

		void build_expression_tree(int size, char* s);
		void create_rpn(char* func, int size);
		void functionate(int value, char* func, int size);
		void inorder(Node*);
		void simplify_tree(Node*);
		void distructtree(Node*);
		bool evalute(Node*);

	};
	template <typename T> struct Stack {
		T arr[20] = { 0 };
		int index = 0;

		T pop()
		{
			T k = arr[index];
			if (index == 0)
				arr[index] = NULL;
			else
				index--;
			return k;

		}

		void push(T value)
		{
			if (arr[index] == 0)
				arr[index] = value;
			else {
				index++;
				arr[index] = value;
			}

		}
	};
	struct Map {
		struct KeyVal {
			char key;
			int val;
			KeyVal* next;
			KeyVal(char key, int val);
		};
		KeyVal* tail = nullptr;
		KeyVal* head = nullptr;

		void addtomap(char key, int val);
		int give_val(char key);
	};
}

