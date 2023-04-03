#pragma once
#include<iostream>
#include "User.h"

class Admin : public User
{

public:

	Admin(const User& obj);

	void delete_user();

	void edit_user();

	void create_test();

	void delete_test();

	void create_category();

	void statistic();
};
