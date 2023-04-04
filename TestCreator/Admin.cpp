#include "Admin.h"
#include "Functions.h"
#include "User.h"
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "Menu.h"
#include <regex>
#include "Question.h"

namespace fs = std::filesystem;

Admin::Admin(const User& obj)
{
	if (obj.is_Admin())
	{
		this->Username = obj.get_Username();
		this->FullName = obj.get_Fullname();
		this->HomeAdress = obj.get_HomeAdress();
		this->TelephoneNumber = obj.get_TelephoneNumber();
		this->Password = obj.get_Password();
		this->isAdmin = obj.is_Admin();
	}
}

void Admin::delete_user()
{

	std::string logins;

	while (true)
	{

	start:

		system("cls");

		render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

		render::gotoxy(25, 11);

		std::cout << "Tip: If you want to delete SEVERAL users,";

		render::gotoxy(15, 12);

		std::cout << "you can type their logins like that : User1,User2,User3";

		render::gotoxy(10, 13);

		std::cout << "Enter login you want to delete: ";

		for (size_t i = 0; i < logins.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(42, 13);

		logins.clear();

		char ch;
		ch = _getch();

		while (ch != 13)
		{
			if (ch == 27)
			{
				return;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (logins.length() <= 40)
				{
					logins.push_back(ch);
					std::cout << ch;
				}

			}
			else if (ch == 8)
			{
				if (!logins.empty())
				{
					logins.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				ch = _getch();
			}
			ch = _getch();
		}

		std::vector<std::string> deleted;
		std::string one_login;

		for (size_t i = 0; i < logins.length(); i++)
		{
			one_login.clear();
			while (logins[i] != ',')
			{
				one_login.push_back(logins[i]);
				i++;

				if (i == logins.length())
				{
					break;
				}
			}
			std::ifstream check_login(one_login + "{}.txt");
			if (!check_login.is_open())
			{
				MessageBox(0, (LPCWSTR)L"Error with some of logins", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start;
			}
			if (one_login == Username)
			{
				MessageBox(0, (LPCWSTR)L"You can't delete yourself", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start;
			}
			deleted.push_back(one_login);
		}

		ch = ' ';

		while (ch != 'y' and ch != 'n')
		{

			render::gotoxy(10, 15);

			std::cout << "                                                                    ";

			render::gotoxy(10, 15);

			std::cout << "Are you sure you want delete this logins? y or n: ";

			std::cin >> ch;

			if (ch != 'y' and ch != 'n')
			{
				MessageBox(0, (LPCWSTR)L"Wrong letter", (LPCWSTR)L"Warning", MB_ICONWARNING);
				continue;
			}
		}

		if (ch == 'n')
		{
			goto start;
		}

		std::vector<std::string> buff;
		std::string temp;

		for (auto removed : deleted)
		{
			fs::remove(removed + "{}.txt");
		}

		std::ifstream userbase("userbase.txt");
		if (userbase.is_open())
		{
			while (userbase >> temp)
			{
				if(std::none_of(deleted.begin(), deleted.end(), [&](std::string removed){
						return removed == temp;
				}))
				{
					buff.push_back(temp);
				}
			}
		}
		else
		{
			MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
			std::ofstream error_logs("logs.txt", std::ios::app);
			error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
			error_logs.close();
			return;
		}
		userbase.close();

		std::ofstream out("userbase.txt", std::ofstream::trunc);
		if (out.is_open())
		{
			for (auto new_el : buff)
			{
				out << new_el << std::endl;
			}
		}
		else
		{
			MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
			std::ofstream error_logs("logs.txt", std::ios::app);
			error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
			error_logs.close();
			return;
		}
	}

}
void Admin::edit_user()
{

	std::string login;

	while (true)
	{

		system("cls");

		render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

		render::gotoxy(22, 9);

		std::cout << "Enter a login you want to edit: ";

		for (size_t i = 0; i < login.length(); i++)
		{
			std::cout << " ";
		}
		render::gotoxy(54, 9);

		login.clear();

		char ch;
		ch = _getch();

		while (ch != 13)
		{
			if (ch == 27)
			{
				return;
			}
			if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
			{
				if (login.length() <= 40)
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
		if (check.is_open())
		{
			render::gotoxy(22, 10);

			std::cout << "Choose info you want to edit";

			int edit_choose = Menu::select_vertical({ "Full Name", "Home Adress", "Telephone Number", "Password"}, Center);

			std::string buff;

			switch (edit_choose)
			{
				case -1:
				{
					return;
				}
				case 0:
				{

					std::string fullname;

				fullname:

					render::gotoxy(22, 11);

					std::cout << "Enter Full Name: ";

					for (size_t i = 0; i < fullname.length(); i++)
					{
						std::cout << " ";
					}
					render::gotoxy(39, 11);

					fullname.clear();

					char ch;
					ch = _getch();
					while (ch != 13)
					{
						if (ch == 27)
						{
							return;
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
							goto fullname;
						}
					}

					std::string is_admin;
					std::getline(check, is_admin);
					std::string log;
					std::getline(check, log);
		
					std::getline(check, buff);

					std::string home;
					std::getline(check, home);
					std::string num;
					std::getline(check, num);
					std::string pass;
					std::getline(check, pass);

					std::ofstream fout(login + "{}.txt", std::ofstream::trunc);
					if (fout.is_open())
					{
						fout << is_admin << std::endl;
						fout << log << std::endl;
						fout << fullname << std::endl;
						fout << home << std::endl;
						fout << num << std::endl;
						fout << pass << std::endl;
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
						std::ofstream error_logs("logs.txt", std::ios::app);
						error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
						error_logs.close();
						return;
					}
					fout.close();
					break;
				}
				case 1:
				{

					std::string adress;

				adress:

					render::gotoxy(22, 11);

					std::cout << "Enter Your Home Adress: ";

					for (size_t i = 0; i < adress.length(); i++)
					{
						std::cout << " ";
					}
					render::gotoxy(46, 11);

					adress.clear();

					char ch;
					ch = _getch();
					while (ch != 13)
					{
						if (ch == 27)
						{
							return;
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
							goto adress;
						}
					}

					std::string is_admin;
					std::getline(check, is_admin);
					std::string log;
					std::getline(check, log);
					std::string full;
					std::getline(check, full);

					std::getline(check, buff);

					std::string num;
					std::getline(check, num);
					std::string pass;
					std::getline(check, pass);

					std::ofstream fout(login + "{}.txt", std::ofstream::trunc);
					if (fout.is_open())
					{
						fout << is_admin << std::endl;
						fout << log << std::endl;
						fout << full << std::endl;
						fout << adress << std::endl;
						fout << num << std::endl;
						fout << pass << std::endl;
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
						std::ofstream error_logs("logs.txt", std::ios::app);
						error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
						error_logs.close();
						return;
					}
					fout.close();

					break;
				}
				case 2:
				{

					std::string phone;

				phone:

					render::gotoxy(22, 11);

					std::cout << "Enter Your Phone Number: +";

					for (size_t i = 0; i < phone.length(); i++)
					{
						std::cout << " ";
					}

					render::gotoxy(48, 11);

					phone.clear();

					char ch;
					ch = _getch();
					while (ch != 13)
					{
						if (ch == 27)
						{
							return;
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
							goto phone;
						}
					}

					std::string is_admin;
					std::getline(check, is_admin);
					std::string log;
					std::getline(check, log);
					std::string full;
					std::getline(check, full);
					std::string adress;
					std::getline(check, adress);

					std::getline(check, buff);

					std::string pass;
					std::getline(check, pass);

					std::ofstream fout(login + "{}.txt", std::ofstream::trunc);
					if (fout.is_open())
					{
						fout << is_admin << std::endl;
						fout << log << std::endl;
						fout << full << std::endl;
						fout << adress << std::endl;
						fout << phone << std::endl;
						fout << pass << std::endl;
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
						std::ofstream error_logs("logs.txt", std::ios::app);
						error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
						error_logs.close();
						return;
					}
					fout.close();

					break;
				}
				case 3:
				{
					std::string password;
					while (true)
					{
						render::gotoxy(22, 11);
						std::cout << "Enter password: ";

						for (size_t i = 0; i < password.length(); i++)
						{
							std::cout << " ";
						}

						render::gotoxy(38, 11);

						password.clear();

						char ch;
						ch = _getch();
						while (ch != 13)
						{
							if (ch == 27)
							{
								return;
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

					std::string is_admin;
					std::getline(check, is_admin);
					std::string log;
					std::getline(check, log);
					std::string full;
					std::getline(check, full);
					std::string adress;
					std::getline(check, adress);
					std::string phone;
					std::getline(check, phone);


					std::ofstream fout(login + "{}.txt", std::ofstream::trunc);
					if (fout.is_open())
					{
						fout << is_admin << std::endl;
						fout << log << std::endl;
						fout << full << std::endl;
						fout << adress << std::endl;
						fout << phone << std::endl;

						std::hash<std::string> password_hash;
						uint64_t hash = password_hash(password);

						fout << hash << std::endl;
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
						std::ofstream error_logs("logs.txt", std::ios::app);
						error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
						error_logs.close();
						return;
					}
					fout.close();

				}
			}
		}
		else
		{
			MessageBox(0, (LPCWSTR)L"Wrong login", (LPCWSTR)L"Warning", MB_ICONWARNING);
			continue;
		}
		check.close();
	}
}

void Admin::create_test()
{
	std::ifstream categories("categories.txt");
	if (categories.is_open())
	{
		while (true)
		{
			render::gotoxy(0, 0);
			system("cls");
			render::SetColor(Color::LightCyan, Color::Black);
			render::renderText("Admin", 22, 1);

			std::string buff;
			std::vector<std::string> names;

			while (std::getline(categories, buff))
			{
				names.push_back(buff);
			}

			if (names.size() == 0)
			{
				return;
			}

			int category = Menu::select_vertical(names, Center);

			if (category == -1)
			{
				return;
			}

			std::string test_name;

		start_test:

			render::gotoxy(25, 10);

			std::cout << "Enter test name: ";

			for (size_t i = 0; i < test_name.length(); i++)
			{
				std::cout << " ";
			}
			render::gotoxy(42, 10);

			test_name.clear();

			char ch;
			ch = _getch();
			while (ch != 13)
			{
				if (ch == 27)
				{
					return;
				}
				if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
				{
					if (test_name.length() <= 14)
					{
						test_name.push_back(ch);
						std::cout << ch;
					}

				}
				else if (ch == 8)
				{
					if (!test_name.empty())
					{
						test_name.pop_back();
						std::cout << "\b \b";
					}
				}
				else
				{
					ch = _getch();
				}
				ch = _getch();
			}

			for (auto el : test_name)
			{
				if (el == '\\' or el == '/' or el == ':' or el == '*' or el == '?' or el == '"' or el == '<' or el == '>' or el == '|' or el == '{' or el == '}' or el == ',')
				{
					MessageBox(0, (LPCWSTR)L"You can't have special symbols \"\\ , / , : , * , ? , \" , < , > , | , { , }, , ,\" in your test name", (LPCWSTR)L"Warning", MB_ICONWARNING);
					goto start_test;
				}
			}

			std::ifstream fin(test_name + "{}" + names[category] + ".txt");
			if (fin.is_open())
			{
				MessageBox(0, (LPCWSTR)L"This test in category already exists", (LPCWSTR)L"Warning", MB_ICONWARNING);
				goto start_test;
			}
			else
			{

				std::vector<Question> questions;
				while (true)
				{
					system("cls");

					for (size_t i = 0; i < questions.size(); i++)
					{
						render::gotoxy(0, 1 + i);
						std::cout << questions[i].getQuestion();
					}

					render::gotoxy(25, 10);

					std::cout << "Enter test name: " << test_name;

					int test_choice = Menu::select_vertical({ "Create question", "Delete Question", "Upload Test"}, Center);

					switch(test_choice)
					{
						case -1:
						{
							return;
						}
						case 0:
						{
							render::gotoxy(1, 11);
							std::cout << "                                                                                                  ";
							Question current_question;
							int status = current_question.set();
							switch (status)
							{
								case -1:
								{
									continue;
								}
								case 0:
								{
									questions.push_back(current_question);
									continue;
								}
							}
							
						}
						case 1:
						{
							if (questions.size() == 0)
							{
								MessageBox(0, (LPCWSTR)L"You don't have questions for deleting", (LPCWSTR)L"Warning", MB_ICONWARNING);
								continue;
							}

							std::string pos;

							render::gotoxy(1, 11);
							std::cout << "                                                                                                  ";

						start_delete:

							render::gotoxy(25, 11);

							std::cout << "Enter position you want to delete: ";

							for (size_t i = 0; i < pos.length(); i++)
							{
								std::cout << " ";
							}
							render::gotoxy(39, 11);

							pos.clear();

							char ch;
							ch = _getch();
							while (ch != 13)
							{
								if (ch == 27)
								{
									return;
								}
								if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
								{
									if (pos.length() <= 5)
									{
										pos.push_back(ch);
										std::cout << ch;
									}

								}
								else if (ch == 8)
								{
									if (!pos.empty())
									{
										pos.pop_back();
										std::cout << "\b \b";
									}
								}
								else
								{
									ch = _getch();
								}
								ch = _getch();
							}
							for (auto el : pos)
							{
								if (!isdigit(el))
								{
									MessageBox(0, (LPCWSTR)L"You need to enter a number!", (LPCWSTR)L"Warning", MB_ICONWARNING);
									goto start_delete;
								}
							}
							int num = std::stoi(pos);
							if (num < 0 or num > questions.size())
							{
								MessageBox(0, (LPCWSTR)L"Wrong position!", (LPCWSTR)L"Warning", MB_ICONWARNING);
								goto start_delete;
							}
							questions.erase(questions.begin() + num - 1);
							continue;
						}
						case 2:
						{
							if (questions.size() != 0)
							{
								std::ofstream test(test_name + "{}" + names[category] + "'.txt");
								if (test.is_open())
								{
									std::ofstream category_tests(names[category] + "'.txt", std::ofstream::app);
									category_tests << test_name << std::endl;
									test << questions.size() << std::endl;
									for (size_t i = 0; i < questions.size(); i++)
									{
										test << questions[i].getQuestion() << std::endl;
										test << questions[i].getRight_Answer_Pos() << std::endl;
										std::vector<std::string> temp = questions[i].getAnswers();
										for (size_t i = 0; i < temp.size(); i++)
										{
											test << temp[i] << std::endl;
										}
										test << "{Ans}" << std::endl;
									}
									return;
								}
								else
								{
									MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
									std::ofstream error_logs("logs.txt", std::ios::app);
									error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
									error_logs.close();
									return;
								}
							}
							else
							{
								MessageBox(0, (LPCWSTR)L"You don't have questions in your test!", (LPCWSTR)L"Warning", MB_ICONWARNING);
								continue;
							}
						}
					}
				}
			}
			fin.close();
			break;
		}
	}
	else
	{
		MessageBox(0, (LPCWSTR)L"You don't have categories. Create one in admin menu!", (LPCWSTR)L"Warning", MB_ICONWARNING);
		return;
	}
	categories.close();
}

void Admin::delete_test()
{
	std::ifstream categories("categories.txt");
	if (categories.is_open())
	{

		render::gotoxy(0, 0);
		system("cls");
		render::SetColor(Color::LightCyan, Color::Black);
		render::renderText("Admin", 22, 1);

		std::string buff;
		std::vector<std::string> names;

		while (std::getline(categories, buff))
		{
			names.push_back(buff);
		}

		if (names.size() == 0)
		{
			return;
		}

		int category = Menu::select_vertical(names, Center);

		if (category == -1)
		{
			return;
		}

		std::ifstream categories_tests(names[category] + "'.txt");

		std::string temp = names[category];

		if (categories_tests.is_open())
		{
			names.clear();

			while (std::getline(categories_tests, buff))
			{
				names.push_back(buff);
			}

			if (names.size() == 0)
			{
				return;
			}

			category = Menu::select_vertical(names, Center);

			if (category == -1)
			{
				return;
			}

			fs::remove(names[category] + "{}" + temp + "'.txt");

			names.erase(names.begin() + category);

			std::ofstream fout(temp + "'.txt", std::ofstream::trunc);

			if (fout.is_open())
			{
				if (names.size() > 0)
				{
					for (size_t i = 0; i < names.size(); i++)
					{
						fout << names[i] << std::endl;
					}
				}
			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
				std::ofstream error_logs("logs.txt", std::ios::app);
				error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
				error_logs.close();
				return;
			}
			fout.close();
		}
		else
		{
			MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
			std::ofstream error_logs("logs.txt", std::ios::app);
			error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
			error_logs.close();
			return;
		}	
		categories_tests.close();
	}
	else
	{
		MessageBox(0, (LPCWSTR)L"You don't have categories yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
		return;
	}
	categories.close();
}

void Admin::create_category()
{

	std::string category_name;


start_category:

	render::gotoxy(25, 10);

	std::cout << "Enter Category Name: ";

	for (size_t i = 0; i < category_name.length(); i++)
	{
		std::cout << " ";
	}
	render::gotoxy(46, 10);

	category_name.clear();

	char ch;
	ch = _getch();
	while (ch != 13)
	{
		if (ch == 27)
		{
			return;
		}
		if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
		{
			if (category_name.length() <= 14)
			{
				category_name.push_back(ch);
				std::cout << ch;
			}

		}
		else if (ch == 8)
		{
			if (!category_name.empty())
			{
				category_name.pop_back();
				std::cout << "\b \b";
			}
		}
		else
		{
			ch = _getch();
		}
		ch = _getch();
	}

	std::ifstream fin(category_name + "'.txt");
	if (fin.is_open())
	{
		MessageBox(0, (LPCWSTR)L"This category is already exists", (LPCWSTR)L"Warning", MB_ICONWARNING);
		goto start_category;
	}
	for (auto el : category_name)
	{
		if (el == '\\' or el == '/' or el == ':' or el == '*' or el == '?' or el == '"' or el == '<' or el == '>' or el == '|' or el == '{' or el == '}' or el == ',' or el == '\'')
		{
			MessageBox(0, (LPCWSTR)L"You can't have special symbols \"\\ , / , : , * , ? , \" , < , > , | , { , }, , , ' ,\" in your category name", (LPCWSTR)L"Warning", MB_ICONWARNING);
			goto start_category;
		}
	}
	fin.close();
	
	std::ofstream cat(category_name + "'.txt");
	if (cat.is_open())
	{
		std::ofstream cat_base("categories.txt", std::ofstream::app);
		cat_base << category_name << std::endl;
	}
	else
	{
		MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
		std::ofstream error_logs("logs.txt", std::ios::app);
		error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
		error_logs.close();
		return;
	}
	cat.close();
	
}

void Admin::statistic()
{
	while (true)
	{
		system("cls");

		int choice = Menu::select_vertical({ "Categories Statistic", "Test Statistic", "User Statistic" }, Center);

		switch (choice)
		{
			case -1:
			{
				return;
			}
			case 0:
			{
				std::ifstream catbase("categories.txt");

				std::string log;

				std::vector<std::string> names;

				if (catbase.is_open())
				{
					while (std::getline(catbase, log))
					{
						names.push_back(log);
					}

					if (names.size() == 0)
					{
						MessageBox(0, (LPCWSTR)L"No statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						return;
					}

					int stat = Menu::select_vertical(names, Center);

					if (stat == -1)
					{
						continue;
					}

					std::ifstream user_stat(names[stat] + "Stat'.txt");

					if (user_stat.is_open())
					{
						while (std::getline(user_stat, log))
						{
							std::cout << log << std::endl;
						}
						system("pause");
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"This category has no statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}
					user_stat.close();
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					return;
				}
				catbase.close();
				break;
			}
			case 1:
			{
				std::ifstream catbase("categories.txt");

				std::string log;

				std::vector<std::string> names;

				if (catbase.is_open())
				{
					while (std::getline(catbase, log))
					{
						names.push_back(log);
					}

					if (names.size() == 0)
					{
						MessageBox(0, (LPCWSTR)L"No statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}

					int stat = Menu::select_vertical(names, Center);

					if (stat == -1)
					{
						continue;
					}

					std::ifstream user_stat(names[stat] + "'.txt");

					names.clear();

					if (user_stat.is_open())
					{
						while (std::getline(user_stat, log))
						{
							names.push_back(log);
						}
						stat = Menu::select_vertical(names, Center);

						if (stat == -1)
						{
							continue;
						}

						std::ifstream test_stat(names[stat] + "{}Stat.txt");

						if (test_stat.is_open())
						{
							while (std::getline(test_stat, log))
							{
								std::cout << log << std::endl;
							}
							std::cout << std::endl;
							system("pause");
						}
						else
						{
							MessageBox(0, (LPCWSTR)L"This test has no statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
							continue;
						}
						test_stat.close();
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"This category has no tests yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}
					user_stat.close();
				}
				catbase.close();
				break;
			}
			case 2:
			{
				std::ifstream userbase("userbase.txt");

				std::string log;

				std::vector<std::string> names;

				if (userbase.is_open())
				{
					std::getline(userbase, log);
					while (std::getline(userbase, log))
					{
						names.push_back(log);
					}

					if (names.size() == 0)
					{
						MessageBox(0, (LPCWSTR)L"No statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}

					int stat = Menu::select_vertical(names, Center);

					if (stat == -1)
					{
						continue;
					}

					std::ifstream user_stat(names[stat] + "{}" + "Stat.txt");

					if (user_stat.is_open())
					{
						while (std::getline(user_stat, log))
						{
							std::cout << log << std::endl;
						}
						system("pause");
					}
					else
					{
						MessageBox(0, (LPCWSTR)L"This user don't have statistic yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}
					user_stat.close();
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					return;
				}
				userbase.close();
				break;
			}
		}
		continue;
	}
}
