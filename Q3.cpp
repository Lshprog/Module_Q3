#include <iostream>
#include "Header3.h"
int main()
{
	char string_to_read[100] = { 0 };
	std::cout << "Enter your expression:\n";
	std::cin >> string_to_read;

	int string_size = strlen(string_to_read);
	q3::BinaryTree tree = q3::BinaryTree();
	tree.create_rpn(string_to_read, string_size);
}

