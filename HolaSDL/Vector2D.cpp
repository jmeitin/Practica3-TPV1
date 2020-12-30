#include "Vector2D.h"

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int ancho, int alto) {
	x = ancho;
	y = alto;
}

int Vector2D::getX() const{
	return x;
}

int Vector2D::getY() const{
	return y;
}
void Vector2D::setX(int num) {
	x = num;
}
void Vector2D::setY(int num) {
	y = num;
}

void Vector2D::setDir(int x1,int x2) {
	 x =  x1;
	 y = x2;
}


Vector2D Vector2D::operator+(Vector2D v2) const {	
	return Vector2D(v2.getX() + x, v2.getY() + y);
}
void Vector2D::operator-(Vector2D v2) {
	x = v2.getX() - x;
	y = v2.getY() - y;
}
bool Vector2D::operator==(Vector2D v2) const {
	return (x == v2.getX() && y == v2.getY());
}
bool Vector2D::operator!=(Vector2D v2) const {
	return (x != v2.getX() || y != v2.getY());
}
int Vector2D::operator*(Vector2D v2) {
	return (x * v2.getX() + y * v2.getY() ); //si da 0 son perpendiculares
}
void Vector2D::operator*(const int escalar) {
	x = x * escalar;
	y = y * escalar;
}
void Vector2D::operator=(Vector2D v2){
	x = v2.getX();
	y = v2.getY();
	//return Vector2D(x, y);
}

bool Vector2D::operator!=(int num) {
	return (x != num && y != num);
	//return Vector2D(x, y);
}

ostream& operator<<(ostream& in, Vector2D vec) {
	in << vec.x <<" "<< vec.y;
	return in;
}

istream& operator>>(istream& in, Vector2D& vec) {
	in >> vec.x  >>vec.y;
	return in;
}