#include<iostream>
#include "SmartPointer.h"
using namespace std;
main()
{
	SmartPointer<string> myPtr(new string);
	*myPtr = "This is a string";
	cout<<*myPtr<<endl;

	SmartPointer<string> other = myPtr;
	cout<<*other<<endl;
	cout<<other->length()<<endl;
}