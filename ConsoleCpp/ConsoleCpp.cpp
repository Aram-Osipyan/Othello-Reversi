// ConsoleCpp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <numeric>
#include <vector>
#include"../Othello/State.h"
#include <string>
#include "ConsoleCpp.h"
using namespace othello_state;
int end_game(int status, bool step_queue)
{
	std::cout << "end of game: ";
	if (status > 0)
	{
		std::cout << "blacks is win" << std::endl;
		if (!step_queue)
		{
			return 0;
		}
		return 3;
	}
	else if (status < 0) {
		std::cout << "whites is win" << std::endl;
		if (!step_queue)
		{
			return 3;
		}
		return 0;
	}
	else {
		return 4;
	}
}
int main(int argc, char* argv[])
{
	bool step_queue = (*argv[1]-'0');
	std::cout << step_queue << std:: endl;
	state st = state::init_state(true);
	st.console_print();
	if (!step_queue)
	{
		int step = st.make_computer_step();
		int i = step / 8;
		int j = step % 8;
		st.make_step(i, j);
		std::cerr << (char)('a' + j) << (char)(i + '1') << std::endl;
		//std::cout << (char)('a' + j) << (char)(i + '1') << std::endl;
		st.console_print();

	}
	while (true)
	{
		if (st.has_step())
		{
			std::string input;
			std::cin >> input;
			std::cout <<input<< std::endl;
			int i = input[0] - 'a';
			int j = input[1] - '1';
			if (!st.is_valid(j, i))
			{
				std::cout << "is not correct step" << std::endl;
				continue;
			}
			st.make_step(j, i);
			st.console_print();
		}
		else {
			st.switch_step();
		}
		int status;
		int is_end = st.is_game_end(status);
		if (is_end)
		{
			return end_game(status, step_queue);
		}
		if (st.has_step())
		{
			int step = st.make_computer_step();
			int i = step / 8;
			int j = step % 8;
			st.make_step(i, j);
			std::cerr << (char)('a' + j) << (char)(i + '1') << std::endl;
			//std::cout << (char)('a' + j) << (char)(i + '1') << std::endl;
			st.console_print();
		}
		else {
			st.switch_step();
		}
		std::cout << "====================================" << std::endl;
		status;
		is_end = st.is_game_end(status);
		if (is_end)
		{
			return end_game(status, step_queue);
		}
		/*std::cout << "enter answer :";
		std::string input;
		std::cin >> input;

		int i = input[0] - 'a';
		int j = input[1] - '1';
		if (!st.is_valid(j,i))
		{
			std::cout << "is not correct step" << std::endl;
			continue;
		}
		st.make_step(j, i);
		st.console_print();
		st.make_computer_step(true);
		st.console_print();
		std::cout << "====================================" << std::endl;
		int is_end = st.is_game_end();
		if (is_end)
		{
			std::cout << "end of game: ";
			if (is_end>0)
			{
				std::cout << "blacks is win" << std::endl;
			}
			else {
				std::cout << "whites is win" << std::endl;
			}
			break;
		}
	}*/

	};
}


