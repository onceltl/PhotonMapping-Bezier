#include"Graph.h"
#include"Dcmp.h"
#include"lodepng.h"
const double inf = 1000000000;
void Graph::Loadtexture(const char *filename)
{
	texture.clear();
	unsigned error = lodepng::decode(texture, width, heigh, filename);
	lodepng::encode("debug.png", texture, width, heigh);
}

void Graph_Bezier::Loadtexture(const char *filename)
{
	unsigned error = lodepng::decode(texture, width, heigh, filename);
}
Color Graph_Bezier::intercolor(double x, double y)
{
	if (texture.size() == 0)return material.color;
	int X = (1 - x)*heigh, Y = y*width;
	X %= heigh;
	Y %= width;
	Color ans;
	double e = (double)texture[4 * width * X + 4 * Y + 4] / 255;
	ans.r = (double)texture[4 * width * X + 4 * Y + 0] / 255;
	ans.g = (double)texture[4 * width * X + 4 * Y + 1] / 255;
	ans.b = (double)texture[4 * width * X + 4 * Y + 2] / 255;
	ans = ans*e;
	return ans;
}
Color Graph_Plane::intercolor(const Point3 &inter)
{
	if (texture.size() == 0)return material.color;
	double x = inter.x, y = inter.y;
	if (N.x != 0)
	{
		x = inter.z;
	}
	if (N.y != 0)
	{
		y = inter.z;
	}
	int X = x + 200, Y = y + 200;
	X %= heigh;
	Y %= width;
	Color ans;
	double e = (double)texture[4 * width * X + 4 * Y + 4] / 255;
	ans.r = (double)texture[4 * width * X + 4 * Y + 0] / 255;
	ans.g = (double)texture[4 * width * X + 4 * Y + 1] / 255;
	ans.b = (double)texture[4 * width * X + 4 * Y + 2] / 255;
	ans = ans*e;
	return ans;
}
bool Graph_Plane::GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n)
{
	dissqr = inf;
	double t = -(D + Point3::dot(N, start)) / Point3::dot(N, dir);
	if (Dcmp::dcmp(t) <= 0) return 0;
	inter = start + dir*t;
	dissqr = Point3::Dissqr(inter - start);
	n = N;
	return 1;
};
bool Graph_Ball::GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n)
{
	dissqr = inf;
	Point3 Rd = Point3::ToOne(dir);
	Point3 L = P - start;
	double tp = Point3::dot(L, Rd);
	double d2 = Point3::Dissqr(L) - tp*tp;
	if (Dcmp::dcmp(d2, R*R) >= 0) return 0;
	double t1 = tp + sqrt(R*R - d2);
	double t2 = tp - sqrt(R*R - d2);
	if (Dcmp::dcmp(t1) <= 0 && Dcmp::dcmp(t2) <= 0) return 0;
	double t = inf;
	if (Dcmp::dcmp(t1) > 0 && Dcmp::dcmp(t1, t) < 0) t = t1;
	if (Dcmp::dcmp(t2) > 0 && Dcmp::dcmp(t2, t) < 0) t = t2;
	inter = start + Rd*t;
	dissqr = t*t;
	n = inter - P;
	return 1;
};
bool Graph_Box::GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n)
{
	bool ok = 0;
	dissqr = inf;
	double t = (Xmin - start.x) / dir.x;
	if (Dcmp::dcmp(dir.x) == 0) t = inf;
	if (Dcmp::dcmp(t) > 0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.y, Ymin) >= 0 && Dcmp::dcmp(stop.y, Ymax) <= 0 && Dcmp::dcmp(stop.z, Zmin) >= 0 && Dcmp::dcmp(stop.z, Zmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(-1, 0, 0);
		}
	}

	t = (Xmax - start.x) / dir.x;
	if (Dcmp::dcmp(dir.x) == 0) t = inf;
	if (Dcmp::dcmp(t) > 0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.y, Ymin) >= 0 && Dcmp::dcmp(stop.y, Ymax) <= 0 && Dcmp::dcmp(stop.z, Zmin) >= 0 && Dcmp::dcmp(stop.z, Zmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(1, 0, 0);
		}
	}

	t = (Ymin - start.y) / dir.y;
	if (Dcmp::dcmp(dir.y) == 0) t = inf;
	if (Dcmp::dcmp(t) >0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.x, Xmin) >= 0 && Dcmp::dcmp(stop.x, Xmax) <= 0 && Dcmp::dcmp(stop.z, Zmin) >= 0 && Dcmp::dcmp(stop.z, Zmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(0, -1, 0);
		}
	}

	t = (Ymax - start.y) / dir.y;
	if (Dcmp::dcmp(dir.y) == 0) t = inf;

	if (Dcmp::dcmp(t) >0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.x, Xmin) >= 0 && Dcmp::dcmp(stop.x, Xmax) <= 0 && Dcmp::dcmp(stop.z, Zmin) >= 0 && Dcmp::dcmp(stop.z, Zmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(0, 1, 0);
		}
	}
	t = (Zmin - start.z) / dir.z;
	if (Dcmp::dcmp(dir.z) == 0) t = inf;

	if (Dcmp::dcmp(t) >0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.y, Ymin) >= 0 && Dcmp::dcmp(stop.y, Ymax) <= 0 && Dcmp::dcmp(stop.x, Xmin) >= 0 && Dcmp::dcmp(stop.x, Xmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(0, 0, -1);
		}
	}


	t = (Zmax - start.z) / dir.z;
	if (Dcmp::dcmp(dir.z) == 0) t = inf;

	if (Dcmp::dcmp(t) > 0)
	{
		double now = Point3::Dissqr(dir*t);
		Point3 stop = start + dir*t;
		if (Dcmp::dcmp(now, dissqr) <= 0 && Dcmp::dcmp(stop.y, Ymin) >= 0 && Dcmp::dcmp(stop.y, Ymax) <= 0 && Dcmp::dcmp(stop.x, Xmin) >= 0 && Dcmp::dcmp(stop.x, Xmax) <= 0)
		{
			ok = 1;
			dissqr = now;
			inter = start + dir*t;
			n = Point3(0, 0, 1);
		}
	}
	return ok;
};
Graphset::Graphset()
{
	Boxes.clear();
	planes.clear();
}
void Graphset::AddBox(const Graph_Box &box)
{
	Boxes.push_back(box);
}
void Graphset::AddPlane(const Graph_Plane &plane)
{
	planes.push_back(plane);
}
void Graphset::AddBall(const Graph_Ball &ball)
{
	balls.push_back(ball);
}
void Graphset::AddBezier(const Graph_Bezier &Bezier)
{
	Beziers.push_back(Bezier);
}
bool Graphset::Findfirst(const Point3 &start, const Point3 &dir, Material &material, Point3 &inter, double &dissqr, Point3 &N)
{
	dissqr = inf;
	Point3 newinter, newN;
	double newdissqr;
	int n = planes.size();
	bool ok = 0;
	for (int i = 0;i < n;i++)
		if (planes[i].GetInter(start, dir, newinter, newdissqr, newN) && Dcmp::dcmp(newdissqr, dissqr)<0)
		{
			dissqr = newdissqr;
			inter = newinter;
			N = newN;
			ok = 1;
			material = planes[i].material;
			Color newcolor = planes[i].intercolor(inter);
			material.changecolor(newcolor);
		}
	n = Boxes.size();
	for (int i = 0;i < n;i++)
		if (Boxes[i].GetInter(start, dir, newinter, newdissqr, newN) && Dcmp::dcmp(newdissqr, dissqr)<0)
		{
			dissqr = newdissqr;
			inter = newinter;
			N = newN;
			ok = 1;
			material = Boxes[i].material;
		}
	n = Beziers.size();
	Point3 info;
	for (int i = 0;i < n;i++)
		if (Beziers[i].GetInter(start, dir, newinter, newdissqr, newN, info) && Dcmp::dcmp(newdissqr, dissqr)<0)
		{
			dissqr = newdissqr;
			inter = newinter;
			N = newN;
			ok = 1;
			material = Beziers[i].material;
			Color color = Beziers[i].intercolor(info.y, info.z);
			material.changecolor(color);
		}
	n = balls.size();
	for (int i = 0;i < n;i++)
		if (balls[i].GetInter(start, dir, newinter, newdissqr, newN) && Dcmp::dcmp(newdissqr, dissqr)<0)
		{
			dissqr = newdissqr;
			inter = newinter;
			N = newN;
			ok = 1;
			material = balls[i].material;
		}
	return ok;
}