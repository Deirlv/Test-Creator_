#pragma once
#include<iostream>
#include "User.h"

class Student : public User
{
	
public:

	Student(const User& obj);

	void choose_test();

	void completed_test();

};
