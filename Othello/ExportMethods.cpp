#include "pch.h"
#include "ExportMethods.h"
#include "State.h"
void* create_state(bool current_state)
{
    return (void*)new othello_state::state(current_state);
}

void* init_state(bool current_state)
{
    return (void*) othello_state::state::init_dynamic_state(current_state);
}

ALPHABETA_API char get_state_field(void* p, int i, int j)
{
    othello_state::state* st = (othello_state::state*)p;
    char k = st->get_field_value(i, j);
    return k;
}

ALPHABETA_API int get_dimension()
{
    return othello_state::state::get_dimension();
}

ALPHABETA_API bool is_valid_step(void* p, int i, int j)
{
    othello_state::state* st = (othello_state::state*)p;
    return st->is_valid(i,j,false);
}

ALPHABETA_API void make_step(void* p , int i, int j)
{
    othello_state::state* st = (othello_state::state*)p;
    st->make_step(i, j);
}

ALPHABETA_API int make_computer_step(void* p)
{
    othello_state::state* st = (othello_state::state*)p;
    return st->make_computer_step();
}

ALPHABETA_API int is_game_end(void* p)
{
    othello_state::state* st = (othello_state::state*)p;
    int status;
    st->is_game_end(status);
    return status;
}

ALPHABETA_API char get_available_symbol()
{
    return othello_state::state::get_available_step_symbol();
}

ALPHABETA_API int sum_test(int a, int b)
{
    return a + b;
}
