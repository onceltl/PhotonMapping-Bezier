#ifndef CAMERA_H
#define CAMERA_H
#include"Point3.h"
class Camera
{
public:
	Point3 rayo;
	int H, W, Y;
	void Setsize(int h, int w) { H = h;W = w; }
	void Setdis(int y) { Y = y; }
};
#endif // !CAMERA_H
