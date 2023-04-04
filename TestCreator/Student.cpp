#include "Student.h"
#include <iostream>
#include <fstream>
#include "Functions.h"
#include <vector>
#include "Menu.h"
#include "Question.h"

Student::Student(const User& obj)
{
	if (!obj.is_Admin())
	{
		this->Username = obj.get_Username();
		this->FullName = obj.get_Fullname();
		this->HomeAdress = obj.get_HomeAdress();
		this->TelephoneNumber = obj.get_TelephoneNumber();
		this->Password = obj.get_Password();
		this->isAdmin = obj.is_Admin();
	}
}

void Student::choose_test()
{
	std::ifstream categories("categories.txt");
	if (categories.is_open())
	{

		render::gotoxy(0, 0);
		system("cls");
		render::SetColor(Color::LightCyan, Color::Black);
		render::renderText("Student", 22, 1);

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

		render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

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

			render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

			category = Menu::select_vertical(names, Center);

			if (category == -1)
			{
				return;
			}

			std::ifstream curr(names[category] + "{}" + temp + "'.txt");
			
			if (curr.is_open())
			{
				float size;
				curr >> size;

				curr.ignore();

				std::string question;
				std::vector<std::string> answers;
				std::string answer;

				int r_pos;

				float mark = 0;

				float one_question_mark = 12 / size;

				float count_right = 0;

				for (size_t i = 0; i < size; i++)
				{
					answers.clear();

					std::getline(curr, question);
					curr >> r_pos;

					curr.ignore();

					while(true)
					{
						std::getline(curr, answer);
						if (answer == "{Ans}")
						{
							break;
						}
						else
						{
							answers.push_back(answer);
						}
					}
					Question q(question, answers, r_pos);

					bool r_or_f = q.show();
					if (r_or_f)
					{
						mark += one_question_mark;
						count_right++;
					}
				}

				float percent = (count_right / size) * 100;


				std::ofstream user(names[category] + "{}Stat.txt", std::ios::app);

				if (user.is_open())
				{
					user << names[category] << " - Mark: " << mark << ", Percent: " << percent << ", Right Answers: " << count_right << std::endl;
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					return;
				}

				std::ofstream user_stat(Username + "{}" + "Stat.txt", std::ios::app);

				if (user_stat.is_open())
				{
					user_stat << names[category] << " - Mark: " << mark << ", Percent: " << percent << ", Right Answers: " << count_right << std::endl;
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					return;
				}

				std::ofstream cat_stat(temp + "Stat'.txt", std::ios::app);

				if (cat_stat.is_open())
				{
					cat_stat << names[category] << " - Mark: " << mark << ", Percent: " << percent << ", Right Answers: " << count_right << std::endl;
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
					std::ofstream error_logs("logs.txt", std::ios::app);
					error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
					error_logs.close();
					return;
				}
				
				user_stat.close();
				user.close();
				cat_stat.close();

				system("cls");

				render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

				render::gotoxy(23, 12);

				std::cout << "Mark - " << mark << ", Percent - " << percent << "%, Right Answers - " << count_right << std::endl;

				system("pause");

			}
			else
			{
				MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
				std::ofstream error_logs("logs.txt", std::ios::app);
				error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
				error_logs.close();
				return;
			}
			curr.close();
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
		MessageBox(0, (LPCWSTR)L"Error with loading file :(", (LPCWSTR)L"Warning", MB_ICONWARNING);
		std::ofstream error_logs("logs.txt", std::ios::app);
		error_logs << __DATE__ << ", " << __TIME__ << ", " << __FILE__ << ", " << __LINE__ << ", " << std::endl;
		error_logs.close();
		return;
	}
	categories.close();
}

void Student::completed_test()
{
	std::ifstream user_stat(Username + "{}" + "Stat.txt");

	if (user_stat.is_open())
	{
		std::string buff;
		while (std::getline(user_stat, buff))
		{
			std::cout << buff << std::endl;
		}
		std::cout << std::endl;
	}
	else
	{
		MessageBox(0, (LPCWSTR)L"You don't have completed tests yet!", (LPCWSTR)L"Warning", MB_ICONWARNING);
		return;
	}

	system("pause");

	user_stat.close();
}
