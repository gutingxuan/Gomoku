//
//  Evaluate.cpp
//  Gomoku
//
//  Created by 顾婷瑄 on 2018/5/1.
//  Copyright © 2018年 顾婷瑄. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include "Gomoku.h"
using namespace std;

int ChessBoard::Winning()
{
    InitScore();
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

void ChessBoard::InitScore()
{
    for (int i = 0; i < 15; i++)
    {
        score1[0][i] = 0;
        score1[14][i] = 0;
        score1[i][0] = 0;
        score1[i][14] = 0;
        score2[0][i] = 0;
        score2[14][i] = 0;
        score2[i][0] = 0;
        score2[i][14] = 0;
    }
    for (int i = 1; i < 14; i++)
    {
        score1[1][i] = 1;
        score1[13][i] = 1;
        score1[i][1] = 1;
        score1[i][13] = 1;
        score2[1][i] = 1;
        score2[13][i] = 1;
        score2[i][1] = 1;
        score2[i][13] = 1;
    }
    for (int i = 2; i < 13; i++)
    {
        score1[2][i] = 2;
        score1[12][i] = 2;
        score1[i][2] = 2;
        score1[i][12] = 2;
        score2[2][i] = 2;
        score2[12][i] = 2;
        score2[i][2] = 2;
        score2[i][12] = 2;
    }
    for (int i = 3; i < 12; i++)
    {
        score1[3][i] = 3;
        score1[11][i] = 3;
        score1[i][3] = 3;
        score1[i][11] = 3;
        score2[3][i] = 3;
        score2[11][i] = 3;
        score2[i][3] = 3;
        score2[i][11] = 3;
    }
    for (int i = 4; i < 11; i++)
    {
        score1[4][i] = 4;
        score1[10][i] = 4;
        score1[i][4] = 4;
        score1[i][10] = 4;
        score2[4][i] = 4;
        score2[10][i] = 4;
        score2[i][4] = 4;
        score2[i][10] = 4;
    }
    for (int i = 5; i < 10; i++)
    {
        score1[5][i] = 5;
        score1[9][i] = 5;
        score1[i][5] = 5;
        score1[i][9] = 5;
        score2[5][i] = 5;
        score2[9][i] = 5;
        score2[i][5] = 5;
        score2[i][9] = 5;
    }
    for (int i = 6; i < 9; i++)
    {
        score1[6][i] = 6;
        score1[8][i] = 6;
        score1[i][6] = 6;
        score1[i][8] = 6;
        score2[6][i] = 6;
        score2[8][i] = 6;
        score2[i][6] = 6;
        score2[i][8] = 6;
    }
    score1[7][7] = 100;
    score2[7][7] = 100;
}


/*
 *: 当前空位置
 0：其他空位置
 1：当前player
 2：对手
 */

int ChessBoard::EvaluateD(int x, int y, int choice)
{
    int numoftwo = 0;
    for (int i = 1; i <= 8; i++)
    {
        //连五
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
        {
            score1[x][y] += 5000000;
        }
        
        //活四 01111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            score1[x][y] += 400000;
        
        //冲四A 21111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) != -1)
            score1[x][y] += 150000;
        
        //冲四B  1*111
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice)
            score1[x][y] += 150000;
        
        //冲四C  11*11
        if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice)
            score1[x][y] += 75000;
        
        
        //活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
            score1[x][y] += 20000;
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            score1[x][y] += 20000;
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            score1[x][y] += 10000;
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            score1[x][y] += 10000;
        
        //眠三A-1 2111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score1[x][y] += 500;
        
        //眠三A-2 21110*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score1[x][y] += 350;
        
        //眠三B-1 211*10
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == choice
            && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
            score1[x][y] += 500;
        
        //眠三B-2 21101*
        if (getLine(x, y, i, -1) == 1 - choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score1[x][y] += 380;
        
        //眠三C-1  21*110
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice)
            score1[x][y] += 500;
        
        //眠三C-2  21011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score1[x][y] += 380;
        
        //眠三D-1  211*01
        if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
            score1[x][y] += 360;
        
        //眠三D-2  2110*1
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score1[x][y] += 360;
        
        //眠三E    21*101
        if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
            score1[x][y] += 355;
        
        //活二A-1  0*0110
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
        {
            score1[x][y] += 65;
            numoftwo++;
        }
        
        //活二A-2  0*110
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == -1)
        {
            score1[x][y] += 300;
            numoftwo++;
        }
        
        //活二B-1  0*1010
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1
            && getLine(x, y, i, 3) == choice && getLine(x, y, i, 4) == -1)
        {
            score1[x][y] += 65;
            numoftwo++;
        }
        
        //活二B-2  01*10
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == -1)
        {
            score1[x][y] += 150;
            numoftwo++;
        }
        
        //活二C-1  01*010
        if (getLine(x, y, i, -2) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
        {
            score1[x][y] += 65;
            numoftwo++;
        }
        
        //活二C-2  *10010
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
        {
            score1[x][y] += 65;
        }
        
        //眠二A-1  211*00
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice
            && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == -1)
            score1[x][y] += 15;
        
        //眠二A-2  2110*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score1[x][y] += 15;
        
        //眠二A-3  21100*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score1[x][y] += 15;
        
        //眠二B-1  21*100
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1)
            score1[x][y] += 25;
        
        //眠二B-2  2101*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score1[x][y] += 25;
        
        //眠二B-3  21010*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score1[x][y] += 25;
        
        //眠二C-1  21*010
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            score1[x][y] += 20;
        
        //眠二C-2  210*10
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == -1
            && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
            score1[x][y] += 20;
        
        //眠二C-3  21001*
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score1[x][y] += 20;
        
        //眠二D-1  21*001
        if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice)
            score1[x][y] += 10;
        
        //眠二D-2  210*01
        if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice)
            score1[x][y] += 10;
    }
    if (numoftwo >= 2) score1[x][y] += 2000;
    return score1[x][y];
}

int ChessBoard::EvaluateA(int x, int y, int choice)
{
    int numoftwo = 0;
    for (int i = 1; i <= 8; i++)
    {
        //连五
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == choice)
        {
            score2[x][y] += 5000000;
        }
        
        //活四 01111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            score2[x][y] += 400000;
        
        //冲四A 21111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) != -1)
            score2[x][y] += 400000;
        
        //冲四B     1*111
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice)
            score2[x][y] += 400000;
        
        //冲四C     11*11
        if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice)
            score2[x][y] += 200000;
        
        
        //活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
            score2[x][y] += 30000;
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            score2[x][y] += 30000;
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            score2[x][y] += 20000;
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            score2[x][y] += 20000;
        
        //眠三A-1 2111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score2[x][y] += 600;
        
        //眠三A-2 21110*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score2[x][y] += 450;
        
        //眠三B-1 211*10
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == choice
            && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
            score2[x][y] += 600;
        
        //眠三B-2 21101*
        if (getLine(x, y, i, -1) == 1 - choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score2[x][y] += 480;
        
        //眠三C-1  21*110
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice)
            score2[x][y] += 600;
        
        //眠三C-2  21011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score2[x][y] += 480;
        
        
        //眠三D-1  211*01
        if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == choice)
            score2[x][y] += 460;
        
        //眠三D-2  2110*1
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score2[x][y] += 460;
        
        //眠三E    21*101
        if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1
            && getLine(x, y, i, 3) == choice)
            score2[x][y] += 455;
        
        //活二A-1  0*0110
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == -1)
        {
            score2[x][y] += 165;
            numoftwo++;
        }
        
        //活二A-2  0*110
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == -1)
        {
            score2[x][y] += 200;
            numoftwo++;
        }
        
        //活二B-1  0*1010
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == -1)
        {
            score2[x][y] += 165;
            numoftwo++;
        }
        
        //活二B-2  01*10
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == -1)
        {
            score2[x][y] += 400;
            numoftwo++;
        }
        
        //活二C-1  01*010
        if (getLine(x, y, i, -2) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
        {
            score2[x][y] += 165;
            numoftwo++;
        }
        
        //活二C-2  *10010
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1 && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
        {
            score2[x][y] += 165;
        }
        
        //眠二A-1  211*00
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice
            && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == -1)
            score2[x][y] += 115;
        
        //眠二A-2  2110*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score2[x][y] += 115;
        
        //眠二A-3  21100*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == -1 && getLine(x, y, i, -3) == choice
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score2[x][y] += 115;
        
        //眠二B-1  21*100
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == -1)
            score2[x][y] += 125;
        
        //眠二B-2  2101*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score2[x][y] += 125;
        
        //眠二B-3  21010*
        if (getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == 1 - choice)
            score2[x][y] += 125;
        
        //眠二C-1  21*010
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            score2[x][y] += 120;
        
        //眠二C-2  210*10
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, -1) == -1
            && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == 1 - choice)
            score2[x][y] += 120;
        
        //眠二C-3  21001*
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == 1 - choice)
            score2[x][y] += 120;
        
        //眠二D-1  21*001
        if (getLine(x, y, i, -2) == 1 - choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == -1 && getLine(x, y, i, 2) == -1
            && getLine(x, y, i, 3) == choice)
            score2[x][y] += 110;
        
        //眠二D-2  210*01
        if (getLine(x, y, i, -3) == 1 - choice && getLine(x, y, i, -1) == -1 && getLine(x, y, i, -2) == choice && getLine(x, y, i, 1) == -1
            && getLine(x, y, i, 2) == choice)
            score2[x][y] += 110;
    }
    if (numoftwo >= 2) score2[x][y] += 3000;
    return score2[x][y];
}

int ChessBoard::Evaluate(int x, int y, int choice)
{
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
        
        /*//活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
            temp += 30000;
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            temp += 30000;
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            temp += 20000;
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            temp += 20000;*/
    }
    return temp;
}

int ChessBoard::Evaluate3(int x, int y, int choice)
{
    int temp=0;
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
            temp += 450000;
        
        //冲四A 21111*
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) != -1)
            temp += 450000;
        
        //冲四B   1*111
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == choice
            && getLine(x, y, i, 3) == choice)
            temp += 450000;
        
        //冲四C   11*11
        if (getLine(x, y, i, -2) == choice && getLine(x, y, i, -1) == choice && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice)
            temp += 250000;
        
        /*//活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
            temp += 35000;
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            temp += 35000;
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            temp += 25000;
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            temp += 25000;*/
    }
    return temp;
}

int ChessBoard::Evaluate4(int x, int y, int choice)
{
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
        
        /*//活三A-1 0111*0
        if (getLine(x, y, i, 1) == -1 && getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice
            && getLine(x, y, i, -3) == choice && getLine(x, y, i, -4) == -1)
            temp += 30000;
        
        //活三B-1  01*110
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == -1 && getLine(x, y, i, 1) == choice
            && getLine(x, y, i, 2) == choice && getLine(x, y, i, 3) == -1)
            temp += 30000;
        
        //活三B-2  *10110
        if (getLine(x, y, i, 1) == choice && getLine(x, y, i, 2) == -1 && getLine(x, y, i, 3) == choice
            && getLine(x, y, i, 4) == choice && getLine(x, y, i, 5) == -1)
            temp += 20000;
        
        //活三B-3  01011*
        if (getLine(x, y, i, -1) == choice && getLine(x, y, i, -2) == choice && getLine(x, y, i, -3) == -1
            && getLine(x, y, i, -4) == choice && getLine(x, y, i, -5) == -1)
            temp += 20000;*/
    }
    return temp;
}


int ChessBoard::getLine(int x, int y, int i, int j)
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
    if (x < 0 || y < 0 || x > 14 || y > 14)   return -2;
    current = board[x][y];
    return current;
}

int ChessBoard::getRecord(int x,int y,int i,int j)
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
        case 6://左下
            x = x - j;
            y = y - j;
            break;
        case 7://右下
            x = x + j;
            y = y - j;
            break;
        case 8://左上
            x = x - j;
            y = y + j;
            break;
    }
    if (x < 0 || y < 0 || x > 14 || y > 14)   return -2;
    current = record[x][y];
    return current;
}

void ChessBoard::setRecord(int x,int y,int i,int j)
{
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
        case 6://左下
            x = x - j;
            y = y - j;
            break;
        case 7://右下
            x = x + j;
            y = y - j;
            break;
        case 8://左上
            x = x - j;
            y = y + j;
            break;
    }
    if(x>=0&&x<=14&&y>=0&&y<=14) record[x][y]=-3;
}


int ChessBoard::evaluate()
{
    /*int value=0;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            record[i][j]=board[i][j];
        }
    }
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
        for(int j=1;j<=8;j++)
        {
            //*00000
            if(getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==choice&&getRecord(move[i][0],move[i][1],j,4)==choice&&getRecord(move[i][0],move[i][1],j,5)==choice)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                setRecord(move[i][0],move[i][1],j,5);
                value+=1000000;
            }
            if(getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==1-choice&&getRecord(move[i][0],move[i][1],j,4)==1-choice&&getRecord(move[i][0],move[i][1],j,5)==1-choice)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                setRecord(move[i][0],move[i][1],j,5);
                value-=1000000;
            }
            //*0000*
            if(getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==choice&&getRecord(move[i][0],move[i][1],j,4)==choice&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                value+=400000;
            }
            if(getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==1-choice&&getRecord(move[i][0],move[i][1],j,4)==1-choice&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                value-=400000;
            }
            //*00001
            if(getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==choice&&getRecord(move[i][0],move[i][1],j,4)==choice&&getRecord(move[i][0],move[i][1],j,5)!=-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                value+=400000;
            }
            if(getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==1-choice&&getRecord(move[i][0],move[i][1],j,4)==1-choice&&getRecord(move[i][0],move[i][1],j,5)!=-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                setRecord(move[i][0],move[i][1],j,4);
                value-=400000;
            }
            //00*00
            if(getRecord(move[i][0],move[i][1],j,-1)==choice&&getRecord(move[i][0],move[i][1],j,-2)==choice&&getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice)
            {
                setRecord(move[i][0],move[i][1],j,-1);
                setRecord(move[i][0],move[i][1],j,-2);
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                value+=400000;
            }
            if(getRecord(move[i][0],move[i][1],j,-1)==1-choice&&getRecord(move[i][0],move[i][1],j,-2)==1-choice&&getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice)
            {
                setRecord(move[i][0],move[i][1],j,-1);
                setRecord(move[i][0],move[i][1],j,-2);
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                value-=400000;
            }
            //0*000
            if(getRecord(move[i][0],move[i][1],j,-1)==choice&&getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==choice)
            {
                setRecord(move[i][0],move[i][1],j,-1);
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                value+=400000;
            }
            if(getRecord(move[i][0],move[i][1],j,-1)==1-choice&&getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==1-choice)
            {
                setRecord(move[i][0],move[i][1],j,-1);
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                value-=400000;
            }
            //*000**
            if(getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==choice&&getRecord(move[i][0],move[i][1],j,4)==-1&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                value+=30000;
            }
            if(getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==1-choice&&getRecord(move[i][0],move[i][1],j,4)==-1&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,3);
                value-=30000;
            }
            //*00*0*
            if(getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==-1&&getRecord(move[i][0],move[i][1],j,4)==choice&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,4);
                value+=30000;
            }
            if(getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==-1&&getRecord(move[i][0],move[i][1],j,4)==1-choice&&getRecord(move[i][0],move[i][1],j,5)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                setRecord(move[i][0],move[i][1],j,4);
                value-=30000;
            }
            //**00**
            if(getRecord(move[i][0],move[i][1],j,-1)==-1&&getRecord(move[i][0],move[i][1],j,1)==choice&&getRecord(move[i][0],move[i][1],j,2)==choice&&getRecord(move[i][0],move[i][1],j,3)==-1&&getRecord(move[i][0], move[i][1], j, 3)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                value+=120;
            }
            if(getRecord(move[i][0],move[i][1],j,-1)==-1&&getRecord(move[i][0],move[i][1],j,1)==1-choice&&getRecord(move[i][0],move[i][1],j,2)==1-choice&&getRecord(move[i][0],move[i][1],j,3)==-1&&getRecord(move[i][0], move[i][1], j, 3)==-1)
            {
                setRecord(move[i][0],move[i][1],j,1);
                setRecord(move[i][0],move[i][1],j,2);
                value-=120;
            }
            if(j%2==0)
            {
                for(int m=0;m<15;m++)
                {
                    for(int n=0;n<15;n++)
                    {
                        record[m][n]=board[m][n];
                    }
                }
            }
        }
    }
    return value;*/
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
