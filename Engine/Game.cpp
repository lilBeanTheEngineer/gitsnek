/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    brd(gfx),
    rng(std::random_device()()),
    snek({ 2,2 }),
    goal( rng, brd, snek ),
    obstacles( rng, brd, snek, goal )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
    
}

void Game::UpdateModel()
{

    if (!gameStart)
    {
        if (wnd.kbd.KeyIsPressed(VK_RETURN))
        {
            gameStart = true;
        }
    }
    else {
        if (!gameIsOver)
        {

            if (wnd.kbd.KeyIsPressed(VK_UP))
            {
                delta_loc = { 0,-1 };
            }
            else if (wnd.kbd.KeyIsPressed(VK_DOWN))
            {
                delta_loc = { 0,1 };
            }
            else if (wnd.kbd.KeyIsPressed(VK_LEFT))
            {
                delta_loc = { -1,0 };
            }
            else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
            {
                delta_loc = { 1,0 };
            }

            ++snekMoveCounter;
            if (snekMoveCounter >= snekMovePeriod)
            {   
                
                snekMoveCounter = 0;
                const Location next = snek.GetNextHeadLocation(delta_loc);
                if (!brd.IsInsideBoard(next) ||
                    snek.IsInTileExceptEnd(next) || obstacles.IsInObst( next ) )
                {
                    gameIsOver = true;
                }
                else
                {
                    const bool eating = next == goal.GetLocation();
                    if (eating)
                    {
                        
                        snek.Grow(ci);
                        ci++;
                        if (ci > 2)
                        {
                            ci = 0;
                        }

                        if ( snekMovePeriod != 1)
                        {
                            speedCount++;
                            if (speedCount == speedCountMax)
                            {
                                snekMovePeriod -= 2;
                                speedCountMax++;
                                speedCount = 0;
                            }
                        }

                    }
                    snek.MoveBy(delta_loc);
                    if (eating)
                    {
                        goal.Respawn(rng, brd, snek);
                        obstacles.Spawn(rng, brd, snek, goal);
                  
                    }

                }
            }
        }
    }
}

void Game::ComposeFrame()
{
    brd.DrawBoarder();
    if (!gameStart)
    {
        SpriteCodex::DrawTitle( 290, 225, gfx);
    }
    else
    {
        
        snek.Draw(brd);
        goal.Draw(brd);
        obstacles.Draw(brd);
        if (gameIsOver)
        {
            SpriteCodex::DrawGameOver( 350, 265 , gfx);
        }
    }
}
