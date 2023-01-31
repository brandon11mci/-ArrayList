#pragma once
#include "SimpleLIst.h"

class AdvancedList : public virtual SimpleList
{
public:
	virtual bool contains(string value) = 0;
	virtual bool remove(string value) = 0;
	virtual int indexOf(string value) = 0;
	virtual int lastIndexOf(string value) = 0;
};