#include "jsoncpp/json.h" 
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int board[15][15];
int choice=-1;
int lastx,lasty;


int getLine(int x, int y, int i, int j)
{
	int current;
	//i:方向 j:相对位置
	switch (i)
	{
	case 1://左
		x = x - j;
		break;
	case 2://右
		x = x + j;
		break;
	case 3://上
		y = y + j;
		break;
	case 4://下
		y = y - j;
		break;
	case 5://右上
		x = x + j;
		y = y + j;
		break;
	case 6://右下
		x = x + j;
		y = y - j;
		break;
	case 7://左上
		x = x - j;
		y = y + j;
		break;
	case 8://左下
		x = x - j;
		y = y - j;
		break;
	}
	if (x < 0 || y < 0 || x > 14 || y > 14)	return -2;
	current = board[x][y];
	return current;
}

/*
*: 当前空位置
0：其他空位置
1：当前player
2：对手
*/

int EvaluateD(int x, int y, int choice)
{
    int score=0;
	int numoftwo = 0;
	for (int i = 1; i <= 8; i++)
	{
		//连五
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
			score += 5000000;

		//活四 01111*
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
			score += 400000;

		//冲四A 21111*
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && (getLine(x, y, i, 5) == 1-choice||getLine(x,y,i,5)==-2))
			score += 300000;

		//冲四B	 1*111
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
			&& getLine(x, y, i, 3) == choice)
			score += 300000;

		//冲四C	 11*11
		if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == choice)
			score += 150000;

		//活三A-1 0111*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
			score += 30000;

		//活三B-1  01*110
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
			score += 30000;

		//活三B-2  *10110
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
			score += 25000;

		//活三B-3  01011*
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
			score += 25000;

		//眠三A-1 2111*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 2000;

		//眠三A-2 21110*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 1350;

		//眠三B-1 211*10
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == choice
			&& getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
			score += 2000;

		//眠三B-2 21101*
		if (getLine(x, y, i, -1) == 1 - choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 1380;

		//眠三C-1  21*110
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice)
			score += 1500;

		//眠三C-2  21011*
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 1380;

		//眠三D-1  211*01
		if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
			score += 1360;

		//眠三D-2  2110*1
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice 
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 1360;

		//眠三E    21*101
		if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice 
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
			score += 1355;

		//活二A-1  0*0110
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice 
			&& getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
		{
			score += 165;
			numoftwo++;
		}

		//活二A-2  0*110
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
			&& getLine(x, y, i, 3) == -1)
		{
			score += 200;
			numoftwo++;
		}

		//活二B-1  0*1010
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 
			&& getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
		{
			score += 165;
			numoftwo++;
		}

		//活二B-2  01*10
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == -1)
		{
			score += 250;
			numoftwo++;
		}

		//活二C-1  01*010
		if (getLine(x, y, i, -2) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
		{
			score += 165;
			numoftwo++;
		}

		//活二C-2  *10010
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1 
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
		{
			score += 65;
		}

		//眠二A-1  211*00
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == -1)
			score += 75;

		//眠二A-2  2110*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 55;

		//眠二A-3  21100*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 15;

		//眠二B-1  21*100
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1)
			score += 25;

		//眠二B-2  2101*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 25;

		//眠二B-3  21010*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 25;

		//眠二C-1  21*010
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == -1
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
			score += 20;

		//眠二C-2  210*10
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == -1
			&& getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
			score += 20;

		//眠二C-3  21001*
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 20;

		//眠二D-1  21*001
		if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1 
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
			score += 10;

		//眠二D-2  210*01
		if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
			score += 10;
	
	if (getLine(x, y, i, 1) == choice||getLine(x,y,i,1)==1-choice)
			score += 10;
	}
	if (numoftwo >= 2) score += 2000;
	return score;
}

int EvaluateA(int x, int y, int choice)
{
    int score=0;
	int numoftwo = 0;
	for (int i = 1; i <= 8; i++)
	{
		//连五
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
			score += 5000000;

		//活四 01111*
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
			score += 500000;

		//冲四A 21111*
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && (getLine(x, y, i, 5) == 1-choice||getLine(x,y,i,5)==-2))
			score += 400000;

		//冲四B	 1*111
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
			&& getLine(x, y, i, 3) == choice)
			score += 400000;

		//冲四C	 11*11
		if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == choice)
			score += 200000;

        //活三A-1 0111*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
			score += 40000;

		//活三B-1  01*110
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
			score += 40000;

		//活三B-2  *10110
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
			score += 30000;

		//活三B-3  01011*
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
			score += 30000;
			
		//眠三A-1 2111*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 3000;

		//眠三A-2 21110*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 2700;

		//眠三B-1 211*10
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == choice
			&& getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
			score += 3000;
			
		//眠三B-2 21101*
		if (getLine(x, y, i, -1) == 1 - choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 2760;

		//眠三C-1  21*110
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice)
			score += 3000;

		//眠三C-2  21011*
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 2760;

		//眠三D-1  211*01
		if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
			score += 2720;

		//眠三D-2  2110*1
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice 
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 2720;

		//眠三E    21*101
		if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice 
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
			score += 2710;

		//活二A-1  0*0110
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice 
			&& getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
		{
			score += 1320;
			numoftwo++;
		}

		//活二A-2  0*110
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
			&& getLine(x, y, i, 3) == -1)
		{
			score += 400;
			numoftwo++;
		}

		//活二B-1  0*1010
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 
			&& getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
		{
			score += 320;
			numoftwo++;
		}

		//活二B-2  01*10
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == -1)
		{
			score += 200;
			numoftwo++;
		}

		//活二C-1  01*010
		if (getLine(x, y, i, -2) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
		{
			score += 130;
			numoftwo++;
		}

		//活二C-2  *10010
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1 
			&& getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
		{
			score += 130;
		}

		//眠二A-1  211*00
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == -1)
			score += 150;

		//眠二A-2  2110*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 110;

		//眠二A-3  21100*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 30;

		//眠二B-1  21*100
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == choice
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1)
			score += 50;

		//眠二B-2  2101*0
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 50;

		//眠二B-3  21010*
		if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
			&& getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
			score += 50;

		//眠二C-1  21*010
		if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == -1
			&& getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
			score += 40;

		//眠二C-2  210*10
		if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == -1
			&& getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
			score += 40;

		//眠二C-3  21001*
		if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
			score += 40;

		//眠二D-1  21*001
		if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1 
			&& getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
			score += 20;

		//眠二D-2  210*01
		if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
			&& getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
			score += 20;
		
		if (getLine(x, y, i, 1) == choice||getLine(x,y,i,1)==1-choice)
			score += 10;
	}
	if (numoftwo >= 2) score += 3000;
	return score;
}

int Evaluate3(int x, int y, int choice)
{
    int temp=0;
    int count=0;
    for (int i = 1; i <= 8; i++)
    {
        //连五
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
        {
            temp += 5500000;
        }
        
        //活四 01111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            temp += 500000;
        
        //冲四A 21111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
			&& getLine(x, y, i, 4) == choice && (getLine(x, y, i, 5) == 1-choice||getLine(x,y,i,5)==-2))
            temp += 450000;
        
        //冲四B   1*111
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice)
            temp += 400000;
        
        //冲四C   11*11
        if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice)
            temp += 250000;
        
        //活三A-1 0111*0
                if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
           {
               temp += 35000;
               count++;
           }
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            {
                temp += 35000;
                count++;
            }
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            {
                temp += 35000;
                count++;
            }
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            {
                temp += 35000;
                count++;
            }
    }

    if(count>=2) temp+=400000;
    return temp;
}

int Evaluate4(int x, int y, int choice)
{
    int count=0;
    int temp=0;
    for (int i = 1; i <= 8; i++)
    {
        //连五
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
        {
            temp += 5000000;
        }
        
        //活四 01111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            temp += 400000;
        
        //冲四A 21111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) != -1)
            temp += 400000;
        
        //冲四B   1*111
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice)
            temp += 400000;
        
        //冲四C   11*11
        if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice)
            temp += 200000;
        
        //活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
           {
               temp += 30000;
               count++;
           }
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            {
                temp += 30000;
                count++;
            }
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            {
                temp += 30000;
                count++;
            }
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            {
                temp += 30000;
                count++;
            }
    }
    if(count>=2) temp+=350000;
    return temp;
}

int evaluate()
{
    int valueAI=0,valueHM=0;
    int move[225][2];
    int k=0;
    for(int x=0;x<15;x++)
        for(int y=0;y<15;y++)
        {
            if(board[x][y]==-1)
            {
                for(int i=1;i<=8;i++)
                {
                    if(getLine(x,y,i,1)==0||getLine(x,y,i,1)==1)
                    {
                        move[k][0]=x;
                        move[k][1]=y;
                        k++;
                        break;
                    }
                }
            }
        }
    for(int i=0;i<k;i++)
    {
        valueAI+=Evaluate3(move[k][0],move[k][0],choice);
        valueHM+=Evaluate4(move[k][0],move[k][0],1-choice);
    }
    return valueAI - valueHM;
}

int Winning()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(board[i][j]==-1)
            {
                if(EvaluateA(i,j,1-choice)>=5000000)
                    return 0;
                else if(EvaluateA(i,j,choice)>=5000000)
                    return 1;
                
            }
        }
    }
    return -1;
}


int AlphaBeta(int deep, int alpha, int beta)
{
    int flag=0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(board[i][j]==-1) {flag=1;break;}
        }
    }
    if (flag==0||deep <= 0)
        return evaluate();
    int val;
    int move1[225][2];
    int k = 0;
    for (int i = 0; i < 225; i++)
    {
        move1[i][0] = -1;
        move1[i][1] = -1;
    }
    for (int x = 0; x < 15; x++)
    {
        for (int y = 0; y < 15; y++)
        {
            if (board[x][y] == -1)
            {
                for (int i = 1; i <= 8; i++)
                {
                    if (getLine(x, y, i, 1) == 0 || getLine(x, y, i, 1) == 1||(x == 7 && y == 7))
                    {
                            move1[k][0] = x;
                            move1[k][1] = y;
                            k++;
                            break;
                    }
                }
            }
        }
    }
    int a[k];
    for(int i=0;i<k;i++)
    {
        if(EvaluateA(move1[i][0],move1[i][1],choice)>EvaluateD(move1[i][0],move1[i][1],1-choice))
            a[i]=EvaluateA(move1[i][0],move1[i][1],choice);
        else a[i]=EvaluateD(move1[i][0],move1[i][1],1-choice);
    }
    int list[k];
    for(int i=0;i<k;i++)
    {
        int max=-1;
        int temp=0;
        for(int j=0;j<k;j++)
        {
            if(a[j]>max)
            {
                max=a[j];
                temp=j;
            }
        }
        list[i]=temp;
        a[temp]=-100;
    }
    int count = 0;
    for (int i = 0; i < k; i++)
    {
        board[move1[list[i]][0]][move1[list[i]][1]] = choice;
        val = -AlphaBeta(deep - 1, -beta, -alpha);
        board[move1[list[i]][0]][move1[list[i]][1]] = -1;
        if (val >= beta)
        {
            return beta;
        }
        if (val > alpha)
        {
            alpha = val;
            if(deep == 4)
            {
                lastx = move1[list[i]][0];
                lasty = move1[list[i]][1];
            }
        }
        if(count++>=45) break;
    }
    return alpha;
}

Json::Value UseAlphaBeta()
{
    AlphaBeta(4,-10000000,10000000);
	board[lastx][lasty] = choice;
	Json::Value action;
	action["x"] = lastx;
	action["y"] = lasty;
	return action;
}

Json::Value nextPosition()
{
    int maxA = -1, maxD = -1;    //最大进攻值和防守值
    int x1 = 0, y1 = 0; ;    //进攻点
    int x2 = 0, y2 = 0;        //防守点
    int p = 0;
    int move[225][2];
    for (int j = 0; j < 225; j++)
    {
        move[j][0] = -1;
        move[j][1] = -1;
    }
    for (int x = 0; x < 15; x++)
    {
        for (int y = 0; y < 15; y++)
        {
            if (board[x][y] == -1)
            {
                for (int i = 1; i <= 8; i++)
                {
                    if ( getLine(x, y, i, 1) == 0 || getLine(x, y, i, 1) == 1)
                    {
                        move[p][0] = x;
                        move[p][1] = y;
                        p++;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i<p; i++)
    {
        if (EvaluateA(move[i][0], move[i][1], choice) > maxA)
        {
            maxA = EvaluateA(move[i][0], move[i][1], choice);
            x1 = move[i][0];
            y1 = move[i][1];
        }
        else if (EvaluateA(move[i][0], move[i][1], choice) == maxA
                 && EvaluateD(move[i][0], move[i][1], 1 - choice) > EvaluateD(x1, y1, 1 - choice))
        {
            x1 = move[i][0];
            y1 = move[i][1];
        }
        if (EvaluateD(move[i][0], move[i][1], 1 - choice) > maxD)
        {
            maxD = EvaluateD(move[i][0], move[i][1], 1 - choice);
            x2 = move[i][0];
            y2 = move[i][1];
        }
    }
    if (maxA >= maxD)
    {
        board[x1][y1] = choice;
        Json::Value action;
	    action["x"] = x1;
	    action["y"] = y1;
	    return action;
    }
    else if (maxD > maxA)
    {
        board[x2][y2] = choice;
        Json::Value action;
	    action["x"] = x2;
	    action["y"] = y2;
	    return action;
    }
    
}

int main()
{
for(int i=0;i<15;i++)
    for(int j=0;j<15;j++)
        board[i][j]=-1;
        
	// 读入JSON
	string str;
	getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input); 
	// 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID = input["responses"].size();
	int m=0;
	choice = input["requests"][m]["x"].asInt() > 0? 1:0;
	for (int i = 0; i < turnID; i++) 
	{
		board[input["requests"][i]["x"].asInt()][input["requests"][i]["y"].asInt()]=1-choice;
		board[input["responses"][i]["x"].asInt()][input["responses"][i]["y"].asInt()]=choice;
	}
	board[input["requests"][turnID]["x"].asInt()][input["requests"][turnID]["y"].asInt()]=1-choice;
	Json::Value ret;
	
	int count=0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(board[i][j]==-1) count++;
        }
    }
    if(count>=160) ret["response"] = UseAlphaBeta();
    else ret["response"] = nextPosition();
	Json::FastWriter writer;
	cout << writer.write(ret) << endl;
	return 0;
}