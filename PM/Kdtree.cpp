#include"Kdtree.h"
int Kdtree::KDTDX = 0;
Kdtree::Kdtree()
{
	k = 3;
	n = 0;
}
void Kdtree::SetMax(int n)
{
	po.clear();
	po.resize(n);
	pt.clear();
	pt.resize(n * 4);
	son.clear();
	son.resize(n*4);
}
void Kdtree::Add(const Point3 &a,const Color &color)
{
	po[n].x[0] = a.x;
	po[n].x[1] = a.y;
	po[n].x[2] = a.z;
	po[n].color = color;
	n++;
}
Color Kdtree::Getcolor(const Point3 &inter)
{
	Color color;
	kdpoint ask;
	ask.x[0] = inter.x;
	ask.x[1] = inter.y;
	ask.x[2] = inter.z;
	int m = 1000;
	query(ask, m);
	double r2 = nestpoint.top().first;
	//double V = r2*sqrt(r2)*acos(-1) * 4 / 3;
	double V = r2;
	while (!nestpoint.empty())
	{
		color = color+nestpoint.top().second.color;
		nestpoint.pop();
	}
	color = color*3/V/m;
	return color;
}
void Kdtree::build(int l, int r, int rt , int dep )
{
	if (l>r) return;
	son[rt] = r - l;
	son[rt * 2] = son[rt * 2 + 1] = -1;
	KDTDX = dep%k;
	int mid = (l + r) / 2;
	std::nth_element(po.begin() + l, po.begin() + mid, po.begin() + r + 1,cmp);
	pt[rt] = po[mid];
	build(l, mid - 1, rt * 2, dep + 1);
	build(mid + 1, r, rt * 2 + 1, dep + 1);
}
void Kdtree::query(kdpoint p, int m, int rt , int dep )
{
	if (son[rt] == -1) return;
	tp newdis(0, pt[rt]);
	for (int i = 0;i<k;i++) newdis.first += sqr(newdis.second.x[i] - p.x[i]);
	int dim = dep%k, x = rt * 2, y = rt * 2 + 1, fg = 0;
	if (Dcmp::dcmp(p.x[dim] , pt[rt].x[dim])>0) std::swap(x, y);
	if (~son[x]) query(p, m, x, dep + 1);
	if (nestpoint.size()<m) nestpoint.push(newdis), fg = 1;
	else
	{
		if (Dcmp::dcmp(newdis.first,nestpoint.top().first)<0) nestpoint.pop(), nestpoint.push(newdis);
		if (Dcmp::dcmp(sqr(p.x[dim] - pt[rt].x[dim]),nestpoint.top().first)<0) fg = 1;
	}
	if (~son[y] && fg) query(p, m, y, dep + 1);
}