#pragma once
#include "SimpleList.h"
#include "AdvancedList.h"

class ArrayList : public SimpleList // or delete SimpleList and replace it with AdvancedList 
{
public:
	int size();
	bool isEmpty();
	bool add(string value);
	string get(int atIndex);
	string remove(int atIndex);
	void clear();
	string set(int atIndex, string value);
	bool contains(string value);
	bool remove(string value);
	int indexOf(string value);
	int lastIndexOf(string value);
};