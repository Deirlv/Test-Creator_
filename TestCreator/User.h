#pragma once
#include <iostream>
#include<string>

#define console_x 80
#define console_y 30

class User
{

protected:

	std::string Username;
	std::string FullName;
	std::string HomeAdress;
	std::string TelephoneNumber;
	uint64_t Password;
	bool isAdmin = 0;

public:

	User();

	int Registration();

	int Login();

	bool is_Admin() const;

	std::string get_Username() const;

	std::string get_Fullname() const;

	std::string get_HomeAdress() const;

	std::string get_TelephoneNumber() const; 

	uint64_t get_Password() const;
};