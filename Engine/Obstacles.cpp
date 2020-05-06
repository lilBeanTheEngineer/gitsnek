#include "Obstacles.h"

Obstacles::Obstacles(std::mt19937& rng, const Board& brd, const Snake& snake, const Goal& goal)
{
	Spawn(rng, brd, snake, goal);
}

void Obstacles::Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const Goal& goal)
{
	if (nObstacles < nObstMax)
	{
		std::uniform_int_distribution<int> xDist(1, brd.GetW() - 1);
		std::uniform_int_distribution<int> yDist(1, brd.GetH() - 1);

		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (snake.IsInTile(newLoc) || newLoc == goal.GetLocation() || IsInObst(newLoc));



		obstacles[nObstacles].InitObstacle(newLoc);
		nObstacles++;

	}
}


void Obstacles::Draw(Board& brd) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		obstacles[i].Draw(brd);
	}
}

bool Obstacles::IsInObst(const Location& gLoc) const
{
	for (int i = 0; i < nObstacles; i++)
	{
		if (obstacles[i].GetLocation() == gLoc)
		{
			return true;
		}

	}
	return false;
}



void Obstacles::Obstacle::InitObstacle(const Location& in_loc)
{
	c = Obstacles::c;
	loc = in_loc;
}

void Obstacles::Obstacle::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Obstacles::Obstacle::GetLocation() const
{
	return loc;
}
