#ifndef POINT3_H
#define POINT3_H
class Point3
{
public:
	double x, y, z;
	Point3(double X = 0, double Y = 0, double Z = 0) :x(X), y(Y), z(Z) {}
	~Point3() {}
	friend Point3 operator +(const Point3 &a, const Point3 &b);
	friend Point3 operator -(const Point3 &a, const Point3 &b);
	friend Point3 operator *(const Point3 &a, const double &b);
	friend Point3 operator /(const Point3 &a, const double &b);

	static Point3 det(const Point3 &a, const Point3 &b);

	static double dot(const Point3 &a, const Point3 &b);
	static double Dissqr(const Point3 &a);
	static double Dis(const Point3 &a);
	static Point3 ToOne(const Point3 &a);
	static Point3 RandomP();
};
#endif