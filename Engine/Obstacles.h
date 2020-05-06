#pragma once
#include "Snake.h"
#include "Board.h"
#include "Goal.h"
#include <random>

class Obstacles
{

private:
	class Obstacle
	{
	public:
		void InitObstacle(const Location& in_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;

	private:
		Location loc;
		Color c;

	};


public:
	Obstacles(std::mt19937& rng, const Board& brd, const Snake& snake, const Goal& goal);
	void Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const Goal& goal);
	void Draw(Board& brd) const;
	bool IsInObst(const Location& gLoc) const;

	

private:
	static constexpr Color c = Colors::LightGray;
	static constexpr int nObstMax = 5;
	Obstacle obstacles[nObstMax];
	int nObstacles = 0;

};