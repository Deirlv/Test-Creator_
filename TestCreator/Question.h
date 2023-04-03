#pragma once
#include <iostream>
#include <vector>

class Question
{
	std::string question;
	std::vector<std::string> answers;
	int* right_answer_pos = nullptr;

public:

	Question();

	Question(std::string question, std::vector<std::string> answers, int right_answer_pos);

	Question(const Question& obj);

	Question& operator=(const Question& obj);

	~Question();

	int set();

	std::string getQuestion();

	std::vector<std::string> getAnswers();

	int getRight_Answer_Pos();

	bool show();


	

};