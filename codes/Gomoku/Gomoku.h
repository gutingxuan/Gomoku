//
//  Gomoku.h
//  Gomoku
//
//  Created by 顾婷瑄 on 2018/5/1.
//  Copyright © 2018年 顾婷瑄. All rights reserved.
//

#ifndef Gomoku_h
#define Gomoku_h
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Player
{
public:
    int choice;                //玩家决定为黑子还是白子，0为黑子，1为白子
    int x, y;                //玩家当前落子位置
};

class ChessBoard
{
public:
    int choice;                //电脑执子
    int board[15][15];        //棋盘
    int record[15][15];
    int score1[15][15];        //每个空位防守得分
    int score2[15][15];     //每个空位攻击得分
    int move[225][2];        //可移动的空位
    int lastx, lasty;
    
    int Winning();
    void InitScore();
    int Evaluate3(int x, int y, int choice);
    int Evaluate4(int x, int y, int choice);
    int Evaluate(int x, int y, int choice);    
    int EvaluateA(int x, int y, int choice);    //攻击估值函数
    int EvaluateD(int x, int y, int choice);    //防守估值函数
    int evaluate();                                //静态估值函数
    int getLine(int x, int y, int i, int j);    //不同方向不同距离
    int getRecord(int x, int y, int i, int j);
    void setRecord(int x,int y,int i,int j);
    int gen();                                    //只选择有邻居的空位
    void nextPosition();                        //静态估值计算下一个落子位置
    
    
    ChessBoard()            //棋盘初始化，空子处为-1，黑子为0，白子为1
    {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++)
                board[i][j] = -1;
        for (int i = 0; i < 225; i++)
        {
            move[i][0] = -1;
            move[i][1] = -1;
        }
    }
    
    
    void print()
    {
        //打印当前棋盘
        cout << "   ";
        for (int i = 0; i < 15; i++)
            cout << setw(3) << i + 1;
        cout << endl;
        for (int i = 0; i < 15; i++)
        {
            cout << setw(3) << i + 1;
            for (int j = 0; j < 15; j++)
            {
                if (board[i][j] == -1)    cout << setw(3) << '*';
                else cout << setw(3) << board[i][j];
            }
            cout << endl;
        }
    }
    
    int MaxMin(int player, int deep);            //极大极小搜索函数
    void UseMaxMin();
    int AlphaBeta(int deep, int alpha, int beta);
    void UseAlphaBeta();
};

#endif /* Gomoku_h */
