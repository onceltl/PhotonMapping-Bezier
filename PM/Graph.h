#ifndef GRAPH_H
#define GRAPH_H
#include"Material.h"
#include"Point3.h"
#include"Bezier.h"
#include<vector>
class Graph
{
public:
	unsigned width, heigh;
	Material material;
	std::vector<unsigned char> texture;
	void Loadtexture(const char *filename);//‘ÿ»ÎŒ∆¿Ì
};
class Graph_Plane :public Graph
{
public:
	Point3 N;
	double D;
	bool GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n);
	Color intercolor(const Point3 &inter);
};
class Graph_Box :public Graph
{
public:
	double Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
	Graph_Box(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax) :Xmin(xmin), Xmax(xmax), Ymin(ymin), Ymax(ymax), Zmin(zmin), Zmax(zmax)
	{
	};
	bool GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n);
};
class Graph_Ball :public Graph
{
public:
	double R;
	Point3 P;
	bool GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &n);
};
class Graph_Bezier :public Bezier
{
public:
	Material material;
	unsigned width, heigh;
	std::vector<unsigned char> texture;
	void Loadtexture(const char *filename);
	Color intercolor(double t, double angle);
};
class Graphset
{
public:
	std::vector<Graph_Plane> planes;
	std::vector<Graph_Box> Boxes;
	std::vector<Graph_Bezier> Beziers;
	std::vector<Graph_Ball> balls;
	Graphset();
	~Graphset() {};
	void AddPlane(const Graph_Plane &plane);
	void AddBox(const Graph_Box &box);
	void AddBall(const Graph_Ball &Ball);
	void AddBezier(const Graph_Bezier &Bezier);
	bool Findfirst(const Point3 &start, const Point3 &dir, Material &material, Point3 &inter, double &dissqr, Point3 &N);

};
#endif // !GRAPHSET_H
