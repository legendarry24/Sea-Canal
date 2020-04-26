#pragma once
using namespace System;
using namespace System::Drawing;

ref class Ship
{
private:
	const int _width = 160;
	const int _height = 40;
	// coordinates
	int _x;
	int _y;
	// direction
	bool _moveRight;

	Brush^ _hullColor;

public:
	Ship(int x, int y);
	int GetX();
	void Move(int dx);
	void ChangeDirection();
	void Draw(Graphics^ g);
	static Brush^ GetColor();
	bool IsReadyToEnterTheCanal(int canalX, int canalWidth);
};