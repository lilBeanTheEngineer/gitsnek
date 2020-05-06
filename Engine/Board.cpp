#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)

{
}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim( (loc.x * dimension) + padding , (loc.y * dimension) + padding,
		dimension - padding , dimension - padding, c);
}

void Board::DrawBoarder()
{
	
	for (int x = bx0; x < width  * dimension; x++) 
	{
		gfx.PutPixel(x, by0, boarderColor);
		gfx.PutPixel(x, height * dimension, boarderColor);
	}

	for (int y = by0; y < height * dimension; y++)
	{
		gfx.PutPixel(bx0, y, boarderColor);
		gfx.PutPixel(width * dimension, y, boarderColor);
	}
	
}

const int Board::GetW() const
{
	return width;
}

const int Board::GetH() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= 1 && loc.x < width &&
		loc.y >= 1 && loc.y < height;
}


