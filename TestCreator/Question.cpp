#include "Question.h"
#include "Functions.h"
#include <conio.h>
#include "Menu.h"
#include "User.h"

Question::Question() {}

Question::Question(std::string question, std::vector<std::string> answers, int right_answer_pos) : question(question), answers(answers)
{
	this->right_answer_pos = new int(right_answer_pos);
}

Question::Question(const Question& obj)
{
	question = obj.question;
	answers = obj.answers;
	right_answer_pos = new int(*obj.right_answer_pos);
}

Question& Question::operator=(const Question& obj)
{

	if (this == &obj)
	{
		return *this;
	}
	delete right_answer_pos;
	question = obj.question;
	answers = obj.answers;
	if (obj.right_answer_pos != nullptr)
	{
		right_answer_pos = new int(*obj.right_answer_pos);
	}
	else
	{
		right_answer_pos = nullptr;
	}
	return *this;

}

Question::~Question()
{
	delete right_answer_pos;
}

int Question::set()
{

	std::string q;

start_question:

	render::gotoxy(25, 11);

	std::cout << "Enter question: ";

	for (size_t i = 0; i < q.length(); i++)
	{
		std::cout << " ";
	}
	render::gotoxy(41, 11);

	q.clear();

	char ch;
	ch = _getch();
	while (ch != 13)
	{
		if (ch == 27)
		{
			return -1;
		}
		if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
		{
			if (q.length() <= 25)
			{
				q.push_back(ch);
				std::cout << ch;
			}

		}
		else if (ch == 8)
		{
			if (!q.empty())
			{
				q.pop_back();
				std::cout << "\b \b";
			}
		}
		else
		{
			ch = _getch();
		}
		ch = _getch();
	}
	for (auto el : q)
	{
		if (el == '{' or el == '}')
		{
			MessageBox(0, (LPCWSTR)L"You can't have special symbols { , } in your question", (LPCWSTR)L"Warning", MB_ICONWARNING);
			goto start_question;
		}
	}
	question = q;

	while (true)
	{
		system("cls");
		render::gotoxy(0, 9);
		std::cout << question;
		if (answers.size() != 0)
		{
			for (size_t i = 0; i < answers.size(); i++)
			{
				render::gotoxy(0, 10 + i);
				std::cout << i + 1 << ". " << answers[i];
			}
		}
		int q_choice = Menu::select_vertical({ "Add Wrong Answer", "Add Correct Answer", "Delete Answer", "Set Question"}, Center);
		switch (q_choice)
		{
			case -1:
			{
				return -1;
			}
			case 0:
			{
				std::string ans;

			start_answer:

				render::gotoxy(25, 12);

				std::cout << "Enter answer: ";

				for (size_t i = 0; i < ans.length(); i++)
				{
					std::cout << " ";
				}
				render::gotoxy(39, 12);

				ans.clear();

				char ch;
				ch = _getch();
				while (ch != 13)
				{
					if (ch == 27)
					{
						return -1;
					}
					if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
					{
						if (ans.length() <= 20)
						{
							ans.push_back(ch);
							std::cout << ch;
						}

					}
					else if (ch == 8)
					{
						if (!ans.empty())
						{
							ans.pop_back();
							std::cout << "\b \b";
						}
					}
					else
					{
						ch = _getch();
					}
					ch = _getch();
				}
				for (auto el : ans)
				{
					if (el == '{' or el == '}')
					{
						MessageBox(0, (LPCWSTR)L"You can't have special symbols { , } in your answer", (LPCWSTR)L"Warning", MB_ICONWARNING);
						goto start_answer;
					}
				}
				answers.push_back(ans);
				continue;
			}
			case 1:
			{
				if (right_answer_pos != nullptr)
				{
					MessageBox(0, (LPCWSTR)L"You already have right answer", (LPCWSTR)L"Warning", MB_ICONWARNING);
					continue;
				}

				std::string ans;

			answer:

				render::gotoxy(25, 12);

				std::cout << "Enter answer: ";

				for (size_t i = 0; i < ans.length(); i++)
				{
					std::cout << " ";
				}
				render::gotoxy(39, 12);

				ans.clear();

				char ch;
				ch = _getch();
				while (ch != 13)
				{
					if (ch == 27)
					{
						return -1;
					}
					if (ch != 8 and ch != '\t' and ch != -32 and ch != 224)
					{
						if (ans.length() <= 20)
						{
							ans.push_back(ch);
							std::cout << ch;
						}

					}
					else if (ch == 8)
					{
						if (!ans.empty())
						{
							ans.pop_back();
							std::cout << "\b \b";
						}
					}
					else
					{
						ch = _getch();
					}
					ch = _getch();
				}
				for (auto el : ans)
				{
					if (el == '{' or el == '}')
					{
						MessageBox(0, (LPCWSTR)L"You can't have special symbols { , } in your answer", (LPCWSTR)L"Warning", MB_ICONWARNING);
						goto answer;
					}
				}
				answers.push_back(ans);
				if (right_answer_pos)
				{
					*right_answer_pos = answers.size() - 1;
				}
				else
				{
					right_answer_pos = new int(answers.size() - 1);
				}
				continue;
			}
			case 2:
			{
				if (answers.size() == 0)
				{
					MessageBox(0, (LPCWSTR)L"You don't have answers for deleting", (LPCWSTR)L"Warning", MB_ICONWARNING);
					continue;
				}

				std::string pos;

			start_delete:

				render::gotoxy(25, 11);

				std::cout << "Enter position you want to delete: ";

				for (size_t i = 0; i < pos.length(); i++)
				{
					std::cout << " ";
				}
				render::gotoxy(60, 11);

				pos.clear();

				char ch;
				ch = _getch();
				while (ch != 13)
				{
					if (ch == 27)
					{
						return -1;
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
				if (num <= 0 or num > answers.size())
				{
					MessageBox(0, (LPCWSTR)L"Wrong position!", (LPCWSTR)L"Warning", MB_ICONWARNING);
					goto start_delete;
				}
				answers.erase(answers.begin() + num - 1);
				if (right_answer_pos)
				{
					if (*right_answer_pos == num - 1)
					{
						right_answer_pos = nullptr;
					}
				}
				continue;
			}
			case 3:
			{
				if (answers.size() != 0)
				{
					if (right_answer_pos == nullptr)
					{
						MessageBox(0, (LPCWSTR)L"You don't have right answer for your question! Add one with a button", (LPCWSTR)L"Warning", MB_ICONWARNING);
						continue;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					MessageBox(0, (LPCWSTR)L"You don't have answers for your question! Add some with a button", (LPCWSTR)L"Warning", MB_ICONWARNING);
					continue;
				}
			}
		}
	}
}

std::string Question::getQuestion()
{
	return question;
}

std::vector<std::string> Question::getAnswers()
{
	return answers;
}

int Question::getRight_Answer_Pos()
{
	return *right_answer_pos;
}

bool Question::show()
{
	system("cls");

	render::renderFrame(console_x, console_y - 4, (char)220, (char)223, (char)219);

	render::gotoxy(20, 11);

	std::cout << question;

	int ans = Menu::select_vertical(answers, Center);

	if (ans == *right_answer_pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}


