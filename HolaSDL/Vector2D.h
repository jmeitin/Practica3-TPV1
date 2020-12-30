#pragma once

#include <iostream>
using namespace std;
class Vector2D
{
private:
	int x;
	int y;

public:
	Vector2D();
	Vector2D(int, int);	
	int getX()const;
	int getY()const ;
	void setDir(int,int);
	void setX(int);
	void setY(int);
	void operator=(Vector2D);
	Vector2D operator+(Vector2D v2) const;
	void operator-(Vector2D v2);
	
	bool operator!=(const Vector2D v2) const;
	bool operator==(const Vector2D v2) const;
	int operator*(const Vector2D v2);
	void operator*(const int escalar);
	bool operator!=(int num);
	friend ostream& operator<<(ostream& in, Vector2D vec);
	friend istream& operator>>(istream& in, Vector2D& vec);
};



