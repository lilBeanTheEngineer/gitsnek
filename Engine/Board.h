#pragma once
#include "Graphics.h"
#include "Location.h"


class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBoarder();
	const int GetW() const;
	const int GetH() const;
	bool IsInsideBoard(const Location& loc) const;
private:

	static constexpr Color boarderColor = Colors::Magenta;
	static constexpr int dimension = 20;
	static constexpr int padding = 1;
	static constexpr int width = ( Graphics::ScreenWidth / dimension )  - 1;
	static constexpr int height = ( Graphics::ScreenHeight / dimension ) - 1;
	static constexpr int bx0 = dimension;
	static constexpr int by0 = dimension;
	Graphics& gfx;
};