/*
This was created by Blake Bonheim
*/
#include <string>
#include "BST.h"

using namespace std;

int main(int argc, char** argv)
{


	cout << "Blake Bonheim -- Threaded BST" << endl << endl;


	BST<int,string> x;
	const int b[13] = {77,70,75,66,79,68,67,69,90,85,83,87,65}; //create array of items to create tree with
	const string z[13] = { "seventy-seven","seventy","seventy-five","sixty-six","seventy-nine","sixty-eight","sixty-seven","sixty-nine","ninety","eighty-five","eighty-three","eighty-seven","sixty-five" };


	std::cout << "Testing the insert function to build me tree." << std::endl;
	for (int i = 0; i < 13; i++)
	{
		x.insert(b[i], z[i]);     //insert all items
	}
	std::cout << "My BST tree size is " << x.getSize() << std::endl;

	//print using printhelp, inorder, and reverse order
	x.print();

	int temp;
	cin >> temp; //pause
}