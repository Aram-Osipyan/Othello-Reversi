#include<vector>
#include<iostream>
namespace othello_state {

	const int _directions[8][2] = { 
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 1, -1 },
		{ 0, -1 },
		{ -1, -1 },
		{ -1, 0 },
		{ -1, 1 } };

	class state {
	public:
	private:

		const static int _dimension = 8;
		const static int _direction_count = 8;
		const static char _empty_simb = '_' - '0';
		const static char _available_step_simb = '?';

		bool _current_step;
		char** _field;
		// step from parent
		int _i, _j;
		bool is_empty(int x, int y);
		bool is_on_field(int x, int y);
		std::vector<state*> generate_steps() const;
		state* empty_step() const {
			state* st = copy_state();
			st->switch_step();
			return st;
		}
		state* copy_state() const;
		void clear();
		int heuristic(bool);
	public:
		static void minimax(state& current_state, int& chosen_score, int& pi, int& pj, bool minmax, bool alpha_beta, int black_best, int white_best, int depth, bool);
		bool is_valid(int i, int j, bool make_step = false);
		void make_step(int i, int j);
		static state init_state(bool current = false); 
		static state* init_dynamic_state(bool current = false);
		state(bool current_step = false);
		state(state&& st);
		state operator=(state&& st) {
			std::swap(_field, st._field);
			return *this;
		}
		state(const state& st);
		state& operator =(const state& st) {
			for (size_t i = 0; i < _dimension; i++)
			{
				for (size_t j = 0; j < _dimension; j++)
				{
					 _field[i][j] = st._field[i][j];
				}
			}
		}
		~state() {
			clear();
		}
		void console_print();
		bool has_step() {
			for (size_t i = 0; i < _dimension; i++)
			{
				for (size_t j = 0; j < _dimension; j++)
				{
					if (is_valid(i, j))
					{
						return true;
					}
				}
			}
			return false;
		}
		void switch_step() {
			_current_step = !_current_step;
		}
		int make_computer_step();		
		void make_computer_step(bool);
		bool is_game_end(int& status);
		static int get_dimension() {
			return _dimension;
		}
		char get_field_value(int i, int j) {
			if (is_valid(i, j)) {
				return _available_step_simb;
			}
			return _field[i][j];
		}
		static char get_available_step_symbol() {
			return _available_step_simb;
		}
	};
}