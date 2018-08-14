//
//  Calculate.cpp
//  Gomoku
//
//  Created by 顾婷瑄 on 2018/5/1.
//  Copyright © 2018年 顾婷瑄. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Gomoku.h"
using namespace std;


int ChessBoard::gen()
{
    int k = 0;
    for (int i = 0; i < 225; i++)
    {
        move[i][0] = -1;
        move[i][1] = -1;
    }
    for (int x = 0; x < 15; x++)
    {
        for (int y = 0; y < 15; y++)
        {
            if (board[x][y] == -1)
            {
                for (int i = 1; i <= 8; i++)
                {
                    if ( getLine(x, y, i, 1) == 0 || getLine(x, y, i, 1) == 1
                        || getLine(x, y, i, 2) == 0 || getLine(x, y, i, 2) == 1)
                    {
                        move[k][0] = x;
                        move[k][1] = y;
                        k++;
                        break;
                    }
                }
            }
        }
    }
    return k;
}
void ChessBoard::nextPosition()
{
    int maxA = 0, maxD = 0;    //最大进攻值和防守值
    int x1 = 0, y1 = 0; ;    //进攻点
    int x2 = 0, y2 = 0;        //防守点
    int k = gen();
    for (int i = 0; i<k; i++)
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
    }
    else if (maxD > maxA)
    {
        board[x2][y2] = choice;
    }
}

int ChessBoard::MaxMin(int player, int deep)
{
    if (Winning() != -1 || deep <= 0)
        return evaluate();
    int best=0, val=0;
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
                    if (getLine(x, y, i, 1) == 0 || getLine(x, y, i, 1) == 1 || (x == 7 && y == 7))
                    {
                        if(EvaluateA(x,y,choice)>=20000||EvaluateA(x,y,1-choice)>=20000)
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
    }
    if (player == choice)
    {
        best = -50000000;
        for (int i = 0; i<k; i++)
        {
            board[move1[i][0]][move1[i][1]] = choice;
            val = MaxMin(1-player,deep - 1);
            board[move1[i][0]][move1[i][1]] = -1;
            if (val > best)
            {
                best = val;
                if (deep == 4)
                {
                    lastx = move1[i][0];
                    lasty = move1[i][1];
                }
            }
        }
    }
    else
    {
        best = 50000000;
        for (int i = 0; i<k; i++)
        {
            board[move1[i][0]][move1[i][1]] = 1 - choice;
            val = MaxMin(player, deep - 1);
            board[move1[i][0]][move1[i][1]] = -1;
            if (val < best)
            {
                best = val;
            }
        }
    }
    return best;
}

void ChessBoard::UseMaxMin()
{
    MaxMin(choice, 2);
    board[lastx][lasty] = choice;
}

int ChessBoard::AlphaBeta(int deep, int alpha, int beta)
{
    if (deep <= 0)
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
    InitScore();
    int a[k];
    for(int i=0;i<k;i++)
    {
        if(EvaluateA(move1[i][0],move1[i][1],choice)>EvaluateD(move1[i][0],move1[i][1],1-choice))
            a[i]=score2[move1[i][0]][move1[i][1]];
        else a[i]=score1[move1[i][0]][move1[i][1]];
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
        if(count++ >= 45)   break;
    }
    return alpha;
}

void ChessBoard::UseAlphaBeta()
{
    AlphaBeta(4,-10000000,10000000);
    board[lastx][lasty] = choice;
}
