#pragma once

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{	
	int type;
	int map;
	int node;
	int weight[100];
} Quiz;

void initQuiz(Quiz* q, int m, int n, int t);

void showmap(int n);
#endif