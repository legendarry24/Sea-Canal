#include "Ship.h"

Ship::Ship(int x, int y)
{
	_x = x;
	_y = y;
	_moveRight = true;
	_hullColor = GetColor();
}

int Ship::GetX()
{
	return _x;
}

void Ship::Move(int dx)
{
	_x += dx;
}

void Ship::ChangeDirection()
{
	_moveRight = !_moveRight;
}

void Ship::Draw(Graphics^ g)
{
	// Draw hull
	g->FillRectangle(_hullColor, _x, _y, _width, _height);

	// Draw left deck
	array<Point>^ leftDeck = { Point(_x, _y), Point(_x, _y + _height), Point(_x - 40, _y) };
	g->FillPolygon(Brushes::Black, leftDeck);

	// Draw right deck
	array<Point>^ rightDeck = { Point(_x + _width, _y), Point(_x + _width, _y + _height), Point(_x + _width + 40, _y) };
	g->FillPolygon(Brushes::Black, rightDeck);

	// Draw left mast
	g->FillRectangle(Brushes::Goldenrod, _x + _width / 7, _y - _height * 1.15, _width / 6, _height * 1.15);

	// Draw middle mast
	g->FillRectangle(Brushes::DarkGoldenrod, _x + _width / 2.5, _y - _height * 1.5, _width / 5, _height * 1.5);

	// Draw right mast
	g->FillRectangle(Brushes::Goldenrod, _x + _width / 1.4, _y - _height * 1.15, _width / 6, _height * 1.15);
}

Brush^ Ship::GetColor()
{
	Random rand;
	array<Brush^>^ brushes = {
		Brushes::Gold, Brushes::YellowGreen, Brushes::DarkSeaGreen, Brushes::MediumOrchid, Brushes::Black
	};

	return brushes[rand.Next(brushes->Length)];
}

bool Ship::IsReadyToEnterTheCanal(int canalX, int canalWidth)
{
	return _moveRight ? _x == canalX - 200 : _x == canalX + canalWidth;
}