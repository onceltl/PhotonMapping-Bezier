#include"Point3.h"
#include"Dcmp.h"
#include<cmath>
#include<random>
#include<ctime>
Point3 operator +(const Point3 &a, const Point3 &b)
{
	Point3 ans;
	ans.x = a.x + b.x;
	ans.y = a.y + b.y;
	ans.z = a.z + b.z;
	return ans;
}
Point3 operator -(const Point3 &a, const Point3 &b)
{
	Point3 ans;
	ans.x = a.x - b.x;
	ans.y = a.y - b.y;
	ans.z = a.z - b.z;
	return ans;
}
Point3 operator *(const Point3 &a, const double &b)
{
	Point3 ans;
	ans.x = a.x*b;
	ans.y = a.y*b;
	ans.z = a.z*b;
	return ans;
}
Point3 operator /(const Point3 &a, const double &b)
{
	Point3 ans;
	ans.x = a.x / b;
	ans.y = a.y / b;
	ans.z = a.z / b;
	return ans;
}
Point3 Point3::det(const Point3 &a, const Point3 &b)
{
	Point3 ans;
	ans.x = a.y*b.z - a.z*b.y;
	ans.y = a.z*b.x - a.x*b.z;
	ans.z = a.x*b.y - a.y*b.x;
	return ans;
}
double Point3::dot(const Point3 &a, const Point3 &b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
double Point3::Dissqr(const Point3 &a)
{
	return a.x*a.x + a.y*a.y + a.z*a.z;
}
double Point3::Dis(const Point3 &a)
{
	return sqrt(Dissqr(a));
}
Point3 Point3::ToOne(const Point3 &a)
{
	double dis = Dis(a);
	if (dis == 0) return a;
	return a / Dis(a);
}

Point3 Point3::RandomP()
{
	Point3 ans;
	int len = 100000000;
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<> dis(0, 2*len);
	/*法线方向较多
	std::uniform_int_distribution<> dis(0, len);
	
	double u = dis(generator);
	double v = dis(generator);
	double R = 1000;
	u /= len;
	u = 2 * acos(-1)*u;
	v /= len;
	v = 2 * acos(sqrt(1 - v*v));
	ans.x = R*cos(v)*cos(u);
	ans.y = R*cos(v)*sin(u);
	ans.z = R*sin(v);
	if (dis(generator) % 2) ans.z *= -1;*/
	//平均分布
	while (1)
	{
		ans.x = dis(generator)-len;
		ans.y=  dis(generator)-len;
		ans.z = 0;
		ans = ans / len;
		double R2 = Point3::Dissqr(ans);
		if (Dcmp::dcmp(R2, 1.0) > 0) continue;
		ans.z = sqrt(1 - R2);
		if (std::rand() % 2) ans.z *= -1;
		break;
	}
	ans = ans * 1000;
	return ans;
}