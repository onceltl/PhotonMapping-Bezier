#ifndef KDTREE_H
#define KDTREE_H
#include"Dcmp.h"
#include<queue>
#include"Point3.h"
#include"Color.h"
struct kdpoint
{
	double x[3];
	Color color;
	bool operator < (const kdpoint &u) const
	{
		return Dcmp::dcmp(x[0],u.x[0])<0;
	}
};

typedef std::pair<double, kdpoint>tp;

class Kdtree
{
public:
	static int KDTDX;
	std::vector<kdpoint> pt, po;
	std::vector<int> son;
	int n,k; //k为维数,n为点数
	Kdtree();
	std::priority_queue<tp>nestpoint;
	static bool cmp(const kdpoint &a, const kdpoint &b){return a.x[KDTDX]<b.x[KDTDX];}
	double sqr(double x){return x*x;};
	void Add(const Point3 &a,const Color &color);
	void build(int l, int r, int rt = 1, int dep = 0);
	void query(kdpoint p, int m,int rt=1, int dep =0);
	Color Getcolor(const Point3 &inter);
	void SetMax(int n);
};
#endif // !KDTREE_H