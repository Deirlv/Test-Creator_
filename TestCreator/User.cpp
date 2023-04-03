#include "User.h"
#include<fstream>
#include <regex>
#include<conio.h>
#include"Functions.h"
#include<iomanip>

User::User() : Password(0) {}

int User::Registration()
{
	render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

	std::string login;
	std::string fullname;
	std::string adress;
	std::string phone;
	std::string password;

	
	while (true)
	{

	start_login:

		render::gotoxy(25, 10);

		std::cout << "Enter login: ";

		for (size_t i = 0; i < login.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(38, 10);

		login.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (login.length() <= 14)
				{
					login.push_back(ch);
					std::cout << ch;
				}
				
			}
			else if (ch == 8)
			{
				if (!login.empty())
				{
					login.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		std::ifstream fin(login + "{}.txt");
		if (fin.is_open())
		{
			MessageBox(0, (LPCWSTR)L"This user is already exists", (LPCWSTR)L"Warning", MB_ICONWARNING);
			goto start_login;
		}
		for (auto el : login)
		{
			if (el == ' ')
			{
				MessageBox(0, (LPCWSTR)L"You can't have spaces in your login", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_login;
			}
			else if (el == '\\' or el == '/' or el == ':' or el == '*' or el == '?' or el == '"' or el == '<' or el == '>' or el == '|' or el == '{' or el == '}' or el == ',')
			{
				MessageBox(0, (LPCWSTR)L"You can't have special symbols \"\\ , / , : , * , ? , \" , < , > , | , { , }, , ,\" in your login", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_login;
			}
		}
		fin.close();
		break;
	}

	while (true)
	{

	start_fullname:

		render::gotoxy(25, 11);

		std::cout << "Enter Full Name: ";

		for (size_t i = 0; i < fullname.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(42, 11);

		fullname.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (fullname.length() <= 35)
				{
					fullname.push_back(ch);
					std::cout << ch;
				}

			}
			else if (ch == 8)
			{
				if (!fullname.empty())
				{
					fullname.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		for (auto el : fullname)
		{
			if (el == '\\' or el == '/' or el == ':' or el == '*' or el == '?' or el == '"' or el == '<' or el == '>' or el == '|' or el == '{' or el == '}')
			{
				MessageBox(0, (LPCWSTR)L"You can't have special symbols \"\\ , / , : , * , ? , \" , < , > , | , { , }\" in your full name", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_fullname;
			}
		}
		break;
	}

	while (true)
	{

	start_adress:

		render::gotoxy(25, 12);

		std::cout << "Enter Your Home Adress: ";

		for (size_t i = 0; i < adress.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(49, 12);

		adress.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (adress.length() <= 25)
				{
					adress.push_back(ch);
					std::cout << ch;
				}

			}
			else if (ch == 8)
			{
				if (!adress.empty())
				{
					adress.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		for (auto el : adress)
		{
			if (el == '\\' or el == '/' or el == ':' or el == '*' or el == '?' or el == '"' or el == '<' or el == '>' or el == '|' or el == '{' or el == '}')
			{
				MessageBox(0, (LPCWSTR)L"You can't have special symbols \"\\ , / , : , * , ? , \" , < , > , | , { , }\" in your adress", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_adress;
			}
		}
		break;
	}

	while (true)
	{
	start_phone:

		render::gotoxy(25, 13);

		std::cout << "Enter Your Phone Number: +";

		for (size_t i = 0; i < phone.length(); i++)
		{
			std::cout << " ";
		}

		render::gotoxy(51, 13);

		phone.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (phone.length() <= 15)
				{
					phone.push_back(ch);
					std::cout << ch;
				}

			}
			else if (ch == 8)
			{
				if (!phone.empty())
				{
					phone.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		for (auto el : phone)
		{
			if (!isdigit(el))
			{
				MessageBox(0, (LPCWSTR)L"The telephone number must contain only NUMBERS", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_phone;
			}
		}
		break;
	}
	

	while (true) 
	{

		render::gotoxy(25, 14);
		std::cout << "Enter password: ";

		for (size_t i = 0; i < password.length(); i++)
		{
			std::cout << " ";
		}

		render::gotoxy(41, 14);

		password.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (password.length() <= 14)
				{
					password.push_back(ch);
					std::cout << '*';
				}

			}
			else if (ch == 8)
			{
				if (!password.empty())
				{
					password.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		if (std::regex_match(password, std::regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$")))
		{
			break;
		}
		else
		{
			MessageBox(0, (LPCWSTR)L"The password must be minimum eight characters, have at least one uppercase letter, one lowercase letter and one number", (LPCWSTR)L"Warning", MB_ICONWARNING);
			continue;
		}
	}

	std::ofstream fout_user(login + "{}.txt", std::ios::app);
	if (!fout_user.is_open())
	{
		MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
		std::ofstream error_logs("logs.txt", std::ios::app);
		error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
		error_logs.close();
		system("pause");
		return -1;
	}

	std::ifstream fin_check("userbase.txt");
	if (fin_check.is_open())
	{
		fout_user << false << std::endl;
		isAdmin = false;
	}
	else
	{
		fout_user << true << std::endl;
		isAdmin = true;
	}
	fin_check.close();

	std::ofstream fout_base("userbase.txt", std::ios::app);
	if (fout_base.is_open())
	{
		fout_base << login << std::endl;
	}
	else
	{
		MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
		std::ofstream error_logs("logs.txt", std::ios::app);
		error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
		error_logs.close();
		system("pause");
		return -1;
	}
	fout_base.close();


	fout_user << login << std::endl;
	fout_user << fullname << std::endl;
	fout_user << adress << std::endl;
	fout_user << phone << std::endl;
	std::hash<std::string> password_hash;
	uint64_t hash = password_hash(password);
	fout_user << hash << std::endl;

	Username = login;
	FullName = fullname;
	HomeAdress = adress;
	TelephoneNumber = phone;
	Password = hash;

	fout_user.close();


	return 1;
}

int User::Login()
{
	render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

	std::string login;
	std::string password;


	while (true)
	{

		render::gotoxy(25, 11);

		std::cout << "Enter login: ";

		for (size_t i = 0; i < login.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(38, 11);

		login.clear();

		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (login.length() <= 14)
				{
					login.push_back(ch);
					std::cout << ch;
				}

			}
			else if (ch == 8)
			{
				if (!login.empty())
				{
					login.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		std::ifstream check(login + "{}.txt");
		if (!check.is_open())
		{
			MessageBox(0, (LPCWSTR)L"This username doesn't exit", (LPCWSTR)L"Warning", MB_ICONWARNING);
			check.close();
			continue;
		}
		else
		{
			check.close();
			break;
		}
	}

	while (true)
	{

		render::gotoxy(25, 12);

		std::cout << "Enter password: ";

		for (size_t i = 0; i < password.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(41, 12);

		password.clear();
		
		char ch;
		ch = _getch();
		while (ch != 13)
		{
			if (ch == 27)
			{
				return 0;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (password.length() <= 14)
				{
					password.push_back(ch);
					std::cout << '*';
				}

			}
			else if (ch == 8)
			{
				if (!password.empty())
				{
					password.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		std::ifstream check(login + "{}.txt");
		if (!check.is_open())
		{
			MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
			std::ofstream error_logs("logs.txt", std::ios::app);
			error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
			error_logs.close();
			system("pause");
			check.close();
			return -1;
		}
		else
		{
			uint64_t pass;
			std::string buff;
			std::getline(check, buff);
			std::getline(check, buff);
			std::getline(check, buff);
			std::getline(check, buff);
			std::getline(check, buff);
			check >> pass;
			check.close();

			std::hash<std::string> password_hash;
			uint64_t hash = password_hash(password);
			
			if (pass == hash)
			{
				std::ifstream current_user(login + "{}.txt");
				if (current_user.is_open())
				{
					std::getline(current_user, buff);
					isAdmin = std::stoi(buff);
					std::getline(current_user, buff);
					Username = login;
					std::getline(current_user, buff);
					FullName = buff;
					std::getline(current_user, buff);
					HomeAdress = buff;
					std::getline(current_user, buff);
					TelephoneNumber = buff;
					Password = pass;
					current_user.close();
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					system("pause");
					check.close();
					return -1;
				}
				return 1;
			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Wrong password", (LPCWSTR)L"Warning", MB_ICONWARNING);
				check.close();
				continue;
			}
		}
	}
}

bool User::is_Admin() const
{
	return isAdmin;
}

std::string User::get_Username() const
{
	return Username;
}

std::string User::get_Fullname() const
{
	return FullName;
}

std::string User::get_HomeAdress() const
{
	return HomeAdress;
}

std::string User::get_TelephoneNumber() const
{
	return TelephoneNumber;
}

uint64_t User::get_Password() const
{
	return Password;
}
