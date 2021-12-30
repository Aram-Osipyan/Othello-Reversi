#include"pch.h"
#include "State.h"
#include <iostream>
bool othello_state::state::is_empty(int x, int y) {
	if (is_on_field(x, y))
	{
		return _field[x][y] == _empty_simb;
	}
	return false;
}

bool othello_state::state::is_on_field(int x, int y) {
	return x >= 0 && x < _dimension
		&& y >= 0 && y < _dimension;
}

bool othello_state::state::is_valid(int i, int j, bool make_step)
{
	if (!is_empty(i, j))
	{
		return false;
	}
	bool is_val = false;
	for (size_t k = 0; k < _direction_count; ++k)
	{
		int x = i, y = j;
		x += _directions[k][0];
		y += _directions[k][1];
		if (is_on_field(x, y) && _field[x][y] == !_current_step)
		{
			x += _directions[k][0];
			y += _directions[k][1];
			if (!is_on_field(x, y))
				continue;
			while (_field[x][y] == !_current_step)
			{
				x += _directions[k][0];
				y += _directions[k][1];
				if (!is_on_field(x, y))
					break;
			}
			if (!is_on_field(x, y))
				continue;

			if (_field[x][y] == _current_step)
			{
				if (make_step)
				{
					int xt = i, yt = j;
					do
					{
						_field[xt][yt] = _current_step;
						xt += _directions[k][0];
						yt += _directions[k][1];

					} while (xt != x || yt != y);
					
				}
				is_val = true;
			}
		}
	}
	if (is_val && make_step)
	{
		_current_step = !_current_step;
	}
	return is_val;
}

void othello_state::state::make_step(int i, int j) {
	if (is_valid(i, j, true))
	{
		//std::cout << (char)(i + 'a') << j + 1 << std::endl;
		//console_print();
	}
	else
	{
		//console_print();
		std::cout << (char)(i + 'a') << j + 1<< " the step is not valid" << std::endl;
	}
}

othello_state::state othello_state::state::init_state(bool current) {
	state init = state(current);
	init._field[3][3] = init._field[4][4] = 0;
	init._field[3][4] = init._field[4][3] = 1;
	return init;
}

othello_state::state* othello_state::state::init_dynamic_state(bool current) {
	state* init = new state(current);
	init->_field[3][3] = init->_field[4][4] = 0;
	init->_field[3][4] = init->_field[4][3] = 1;
	return init;
}

othello_state::state::state(bool current_step) :_current_step(current_step) {
	_field = new char* [_dimension];
	for (size_t i = 0; i < _dimension; i++)
	{
		_field[i] = new char[_dimension];
		for (size_t j = 0; j < _dimension; j++)
		{
			_field[i][j] = _empty_simb;

		}
	}
}

othello_state::state::state(state&& st) {
	std::cout << "move constr" << std::endl;
	std::swap(_field, st._field);
}

othello_state::state::state(const state& st) {
	_field = new char* [_dimension];
	for (size_t i = 0; i < _dimension; i++)
	{
		_field[i] = new char[_dimension];
		for (size_t j = 0; j < _dimension; j++)
		{
			_field[i][j] = st._field[i][j];

		}
	}
}

void othello_state::state::clear() {
	for (size_t i = 0; i < _dimension; i++)
	{
		delete[] _field[i];
	}
	delete[] _field;
}

int othello_state::state::heuristic(bool current){
	int sum = 0;
	for (size_t i = 0; i < _dimension; i++)
	{
		for (size_t j = 0; j < _dimension; j++)
		{
			int deter = (_field[i][j] == current);
			int is_border = (i == 0 || i == (_dimension - 1) || j == 0 || j == (_dimension - 1));
			int is_corner = (i == 0 && (j == _dimension - 1 || j == 0) || i == _dimension - 1 && (j == _dimension - 1 || j == 0));
			sum += deter;
			sum += 2 *deter*is_border;
			sum += 10 * deter * is_corner;
		}
	}
	return sum;
}

void othello_state::state::console_print(){
	// header printing /////////////
	std::cout << " ";
	for (size_t i = 0; i < _dimension; i++)
	{
		std::cout << " " << (char)(i + 'a');
	}
	std::cout << std::endl;
	///////////////////////////////
	for (int i = 0; i < _dimension; i++)
	{
		std::cout << (char)('1' + i) << " ";
		for (int j = 0; j < _dimension; j++)
		{
			if (this->is_valid(i, j, false))
			{
				std::cout << (char)(_available_step_simb) << " ";
			}
			else
			{
				std::cout << (char)(_field[i][j] + '0') << " ";
			}

		}
		std::cout << std::endl;
	}
}

bool othello_state::state::is_game_end(int& status) {
	int sum = 0;
	int black_count = 0;
	int white_count = 0;
	for (size_t i = 0; i < _dimension; i++)
	{
		for (size_t j = 0; j < _dimension; j++)
		{
			sum += (int)is_valid(i, j);
			black_count += _field[i][j] == 1;
			white_count += _field[i][j] == 0;
		}
	}
	switch_step();
	for (size_t i = 0; i < _dimension; i++)
	{
		for (size_t j = 0; j < _dimension; j++)
		{
			sum += (int)is_valid(i, j);
		}
	}
	switch_step();
	status = black_count - white_count;
	return (sum == 0);
}

bool better(int p1, int p2, bool minmax) {
	if (minmax)
	{
		return p1 < p2;
	}
	return p1 > p2;
}

void othello_state::state::minimax(othello_state::state& current_state, int& chosen_score, int& pi, int& pj, bool minmax, bool alpha_beta, int black_best, int white_best, int depth,bool current_step) {
	if (depth == 0)
	{
		chosen_score = current_state.heuristic(current_step);
		//std::cout << chosen_score << " " << std::endl;
	}
	else {
		std::vector<state*> steps = current_state.generate_steps();
		if (steps.size() == 0)
		{
			//chosen_score = current_state.heuristic(current_step);
			state* st = current_state.empty_step();
			minimax(*st, chosen_score, pi, pj, !minmax, alpha_beta, black_best, white_best, depth - 1, current_step);
			//std::cout << chosen_score<<" " << std::endl;
			delete st;
		}
		else {
			int best_score = minmax * INT16_MAX +!minmax * INT16_MIN;
			int x = pi, y = pj;
			for (size_t i = 0; i < steps.size(); i++)
			{
				int score  = chosen_score;
				int xt, yt;
				minimax(*steps[i], score, xt, yt, !minmax, alpha_beta, black_best, white_best, depth - 1,current_step);
				if (alpha_beta)
				{
					// if is step of white disks
					if (minmax && score < white_best)
					{
						if (score < black_best)
						{
							break;
						}
						else {
							white_best = score;
						}
					}
					// if is step of black disks
					if (!minmax && score > black_best)
					{
						if (score > white_best)
						{
							break;
						}
						else {
							black_best = score;
						}
					}
				}
				if (better(score, best_score, minmax))
				{
					best_score = score;
					x = steps[i]->_i;
					y = steps[i]->_j;
				}

			}
			for (size_t i = 0; i < steps.size(); i++)
			{
				delete steps[i];
			}
			chosen_score = best_score;
			pi = x;
			pj = y;

		}

	}
}

void minimax_eval( othello_state::state& current_state, int& x, int& y,bool current_step) {
	int chosen_score = -1;
	bool minmax = false;
	bool alpha_beta = true;
	int black_best = INT16_MAX;
	int white_best = INT16_MIN;
	int depth = 5;
	othello_state::state::minimax(current_state,chosen_score, x, y,minmax,alpha_beta,black_best,white_best,depth,current_step );
}

int othello_state::state::make_computer_step() {
	int x, y;
	minimax_eval(*this, x, y, _current_step);

	return x * _dimension + y;
}

void othello_state::state::make_computer_step(bool) {
	int x, y;
	minimax_eval(*this, x, y, _current_step);
	make_step(x, y);
}

std::vector<othello_state::state*> othello_state::state::generate_steps() const {
	std::vector<othello_state::state*> steps;
	for (size_t i = 0; i < _dimension; i++)
	{
		for (size_t j = 0; j < _dimension; j++)
		{
			othello_state::state* current = copy_state();
			if (current->is_valid(i, j, true))
			{
				current->_i = i;
				current->_j = j;
				steps.push_back(current);
			}
			else {
				delete current;
			}
		}
	}
	return steps;
}

othello_state::state* othello_state::state::copy_state() const{
	othello_state::state* st = new othello_state::state(_current_step);
	/// copy field
	for (size_t i = 0; i < _dimension; i++)
	{
		for (size_t j = 0; j < _dimension; j++)
		{
			st->_field[i][j] = _field[i][j];
		}
	}
	return st;
}
