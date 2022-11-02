#include "pch.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
    ::srand(static_cast<unsigned>(time(nullptr)));
    board.Init(25, &player);
    player.Init(&board);



    uint64 lastTick = 0;
    // 고정프레임 설정
    int32 fixFrame = 5;
    uint64 FrameTick = 10;
    uint64 tick = 0;
    uint64 loopPerFrame = 0;

    uint64 UpdateTick = 0;
    while (true)
    {
#pragma region 프레임 관리
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - lastTick;
        lastTick = currentTick;
        loopPerFrame++;
        // 고정프레임 설정
        if (tick >= FrameTick)
        {
            ConsoleHelper::SetCursorColor(ConsoleColor::WHITE);

            cout << "loopPerFrame: " << loopPerFrame << endl;
            cout << "spf: " << tick << "ms" << endl;
            tick = 0;
            loopPerFrame = 0;
        }
        else
        {
            tick += deltaTick;
        }
#pragma endregion

        // 입력


        // 로직
        player.Update(deltaTick);


        // 렌더링
        board.Render();
        
    }



}
