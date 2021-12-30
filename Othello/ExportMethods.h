#pragma once

#define ALPHABETA_API __declspec(dllexport)

#include"pch.h"
extern "C" ALPHABETA_API void*  create_state(bool); // constructor

extern "C" ALPHABETA_API void* init_state(bool); // init state

extern "C" ALPHABETA_API char get_state_field(void*,int i, int j);

extern "C" ALPHABETA_API int get_dimension();

extern "C" ALPHABETA_API bool is_valid_step(void* ,int i,int j);

extern "C" ALPHABETA_API void make_step(void*, int i, int j);

extern "C" ALPHABETA_API int make_computer_step(void*);

extern "C" ALPHABETA_API int is_game_end(void*);

extern "C" ALPHABETA_API char get_available_symbol();