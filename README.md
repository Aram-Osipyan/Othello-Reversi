# Othello-Reversi Game
## Using alpha-beta prunning algorithm
>Alpha–beta pruning is a search algorithm that seeks to decrease the number of nodes that are evaluated by the minimax algorithm in its search tree.  It stops evaluating a move when at least one possibility has been found that proves the move to be worse than a previously examined move. Such moves need not be evaluated further. When applied to a standard minimax tree, it returns the same move as minimax would, but prunes away branches that cannot possibly influence the final decision.

You can see the implementation of the algorithm in C++ here, and the visualization in WinForms C#.
## Algorithm 
The algorithm is implemented in '[Othello](https://github.com/Aram-Osipyan/Othello-Reversi/tree/main/Othello)' project and computed in Othello.dll library.  Main part of  [algorithm](https://github.com/Aram-Osipyan/Othello-Reversi/blob/main/Othello/State.cpp):
```c++
void othello_state::state::minimax(othello_state::state& current_state, 
    int& chosen_score, 
    int& pi, int& pj, 
    bool minmax, 
    bool alpha_beta, 
    int black_best, 
    int white_best, 
    int depth,
    bool current_step) {
	if (depth == 0)
	{
		chosen_score = current_state.heuristic(current_step);
	}
	else {
		std::vector<state*> steps = current_state.generate_steps();
		if (steps.size() == 0)
		{
			state* st = current_state.empty_step();
			minimax(*st, chosen_score, pi, pj, !minmax, alpha_beta, black_best, white_best, depth - 1, current_step);
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
```
## Visual Part 
Visual part is implemented by WinForms C# framework. The current available moves are marked in dark pink

![game](https://github.com/Aram-Osipyan/Othello-Reversi/blob/main/8Hl2sQFINpU.jpg?raw=true "game")

