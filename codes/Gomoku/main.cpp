//
//  main.cpp
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

int main()
{
    Player player;
    ChessBoard game;
    cout << "请玩家决定执黑子还是白子，0为黑子，1为白子：";
    cin >> player.choice;
    game.choice = 1 - player.choice;
    if (player.choice == 1)
    {
        game.board[7][7] = 0;
    }
    game.print();
    while (1)
    {
        cout << "请输入落子位置(例：4 5)：";
        cin >> player.x >> player.y;
        while (game.board[player.x - 1][player.y - 1] != -1)
        {
            cout << "该位置已有棋子，请选择另一个落子位置：";
            cin >> player.x >> player.y;
        }
        game.board[player.x - 1][player.y - 1] = player.choice;
        //game.nextPosition();
        //game.UseMaxMin();
        game.UseAlphaBeta();
        game.print();
        if (game.Winning() == 0)
        {
            cout << "恭喜玩家获胜！\n";
            break;
        }
        else if (game.Winning() == 1)
        {
            cout << "抱歉您失败了！\n";
            break;
        }
    }
    system("pause");
    return 0;
}
