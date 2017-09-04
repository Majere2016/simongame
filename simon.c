/**********************************************************
 * Copyright (C) 2017 All rights reserved.
 * \file simon.c
 * \brief
 * \note	注意事项：
 *
 *\version 1.0
 ** \author Allen.L
 ** \date 2017-09-04
 ** \last modified 2017-09-04 22:04:10
**********************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	char another_game = 'Y';
	const unsigned int DELAY = 1;
	bool correct = true;
	unsigned int tries = 0;
	unsigned int digits = 0;
	time_t seed = 0;
	unsigned int number = 0;
	time_t wait_start = 0;
	clock_t start_time = 0;
	unsigned int score = 0;
	unsigned int total_digits = 0;
	unsigned int game_time = 0;
	printf("\n来玩一个简单的西蒙游戏, ");
	printf("看屏幕上的数字");
	printf("\n看仔细了，数字只显示一遍"
			"for %u s %s",DELAY,DELAY >1?"S!":"!");
	printf("\n我们将会删除它们，并且开始测试你");
	printf("to enter the same sequence");
	printf("\n当你做的时候，你必须把空间放在两个数字中.\n");
	printf("\n好运！\n按回车继续\n");
	scanf("%c",&another_game);

	do
	{
		correct = true;
		tries = 0;
		digits = 2;
		start_time = clock();
		while(correct){
			/*Statments to play game*/
			++tries;
			wait_start = clock();
			srand(time(&seed));
			for(unsigned int i = 1; i <= digits; ++i)
				printf("%d",rand() % 10);
			for(;clock()-wait_start < DELAY * CLOCKS_PER_SEC;)
				printf("\r");
			for(unsigned int i =1; i <= digits; ++i)
				printf(" ");
			if(tries ==1)
				printf("\n Now you enter the sequence - don't forget"
						"the spaces\n");
			else
				printf("\r");

			srand(seed);
			for(unsigned int i = 1;i <= digits;++i)
			{
				scanf("%u",&number);
				if(number != rand() % 10)
				{
					correct = false;
					break;
				}
			}
			if(correct && ((tries % 3)== 0))
				++digits;
			printf("%s\n",correct?"对的":"错的");
		}
		score = 10 * (digits - ((tries % 3)== 1));
		total_digits = digits *(((tries % 3)==0)? 3: tries % 3);
		if(digits > 2)
			total_digits += 3 * ((digits - 1)*(digits -2)/2 -1);
		game_time = (clock()- start_time)/CLOCKS_PER_SEC - tries * DELAY;
		if(total_digits > game_time)
			score += 10 * (game_time - total_digits);
		printf("\n\nGame time was %u s. your score is %u",game_time,score);
		fflush(stdin);

		printf("\n你想再玩一次这个游戏吗（y/n）?");
		scanf("%c",&another_game);
	}while(toupper(another_game)=='Y');
	return 0;
}
