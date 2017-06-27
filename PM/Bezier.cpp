#include"Bezier.h"
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include"Dcmp.h"
void Bezier::GetBernstein(double t)
{
	memset(B, sizeof(B), 0);
	B[0][0] = 1;
	for (int j = 1;j <= n;j++)
	{
		B[0][j] = B[0][j - 1] * (1 - t);
		for (int i = 1;i < j;i++)
			B[i][j] = (1 - t)*B[i][j - 1] + t*B[i - 1][j - 1];
		B[j][j] = t*B[j - 1][j - 1];
	}
}
double Bezier::Ber(int x, int y)
{
	if (x > y) return 0;
	return B[x][y];
}
Point3 Bezier::Pt2(double t)
{
	GetBernstein(t);
	Point3 ans;
	for (int i = 0;i <= n - 2;i++)
		ans = ans + (P[i + 2] - P[i + 1] * 2 + P[i])*Ber(i, n - 2);
	ans = ans*(n*(n - 1));
	return ans;
}
Point3 Bezier::Pt1(double t)
{
	GetBernstein(t);

	Point3 ans;
	for (int i = 0;i <= n;i++)
	{
		ans = ans + P[i] * (Ber(i - 1, n - 1) - Ber(i, n - 1));
	}
	ans = ans*n;
	return ans;
}
Point3 Bezier::Pt(double t, int x, int k)
{
	if (k == 0)
	{
		return P[x];
	}
	Point3 ans;
	ans = Pt(t, x, k - 1)*(1 - t) + Pt(t, x + 1, k - 1)*t;
	return ans;
}
bool Bezier::GetPt2Zero(double &t)
{
	double l = 0, r = 1;
	double Y1 = Pt2(l).y, Y2 = Pt2(r).y;
	if (Dcmp::dcmp(Y1) > 0 && Dcmp::dcmp(Y2) > 0) return 0;
	if (Dcmp::dcmp(Y1) < 0 && Dcmp::dcmp(Y2) < 0) return 0;
	if (Dcmp::dcmp(Y1,Y2)<0)
	{
		while (Dcmp::dcmp(l, r) != 0)
		{
			double mid = (l + r) / 2;
			double ansy=Pt2(mid).y;
			if (Dcmp::dcmp(ansy) < 0)l = mid;
				else r = mid;
		}
	} else
	{
		while (Dcmp::dcmp(l, r) != 0)
		{
			double mid = (l + r) / 2;
			double ansy = Pt2(mid).y;
			if (Dcmp::dcmp(ansy) < 0)r = mid;
				else l = mid;
		}
	}
	t = l;
	return 1;
}
bool Bezier::GetPt1Zero(double L, double R, double &t)
{
	double l = L, r = R;
	double Y1 = Pt1(l).y;
	double Y2 = Pt1(r).y;

	if (Dcmp::dcmp(Y1) > 0 && Dcmp::dcmp(Y2) > 0) return 0;
	if (Dcmp::dcmp(Y1) < 0 && Dcmp::dcmp(Y2) < 0) return 0;
	if (Dcmp::dcmp(Y1, Y2)<0)
	{
		while (r - l>1e-8)
		{
			double mid = (l + r) / 2;
			double ansy = Pt1(mid).y;
			if (Dcmp::dcmp(ansy) < 0)l = mid;
			else r = mid;
		}
	}
	else
	{
		while (r - l>1e-8)
		{
			double mid = (l + r) / 2;
			double ansy = Pt1(mid).y;
			if (Dcmp::dcmp(ansy) < 0)r = mid;
			else l = mid;
		}
	}
	t = (l + r) / 2;
	return 1;
}
void Bezier::GetExtremumY(double &extremumt1, double &extremumt2)
{
	extremumt1 = extremumt2 = 1;
	double Pt2Zero = -1;
	double Pt1Zero1 = -1;
	double Pt1Zero2 = -1;

	if (GetPt2Zero(Pt2Zero))//一阶导有波峰或者波谷
	{
	if (GetPt1Zero(0, Pt2Zero,Pt1Zero1))
	{
	extremumt1 = Pt1Zero1;
	if (GetPt1Zero(Pt2Zero, 1,Pt1Zero2))
	extremumt2 = Pt1Zero2;
	}
	else
	{
	if (GetPt1Zero(Pt2Zero, 1, Pt1Zero2))
	extremumt1 = Pt1Zero2;
	}
	}else//没有波峰波谷
	{
		if (GetPt1Zero(0, 1, Pt1Zero1))
			extremumt1 = Pt1Zero1;
	}
}
void Bezier::GetExtremumX(double &extremumt1, double &extremumt2)
{
	for (int i = 0;i <= n;i++)
		std::swap(P[i].x, P[i].y);
	GetExtremumY(extremumt1, extremumt2);
	for (int i = 0;i <= n;i++)
		std::swap(P[i].x, P[i].y);
}
void Bezier::RotateToM(int ttot, int angletot)
{
	points.clear();
	double PI = acos(-1);
	int nangle = angletot;
	int &tot = pointstot;
	tot = 0;
	for (int t = 0;t <= ttot;t++)
	{
		Point3 NowPoint = Pt(double(t) / ttot, 0, n);
		for (int angle = 0;angle <angletot;angle++)
		{
			Point3 ChangePoint;
			ChangePoint.z = NowPoint.y;
			ChangePoint.x = NowPoint.x*cos(2 * PI*angle / angletot);
			ChangePoint.y = NowPoint.x*sin(2 * PI*angle / angletot);
			points.push_back(ChangePoint);
			if (t != 0 && angle != 0)
			{
				meshes.push_back(tot);meshes.push_back(tot - 1);meshes.push_back(tot - 1 - nangle);
				meshes.push_back(tot);meshes.push_back(tot - 1 - nangle);meshes.push_back(tot - nangle);
			}
			tot++;
		}
		if (t != 0)
		{
			meshes.push_back(tot - 1 - nangle + 1);meshes.push_back(tot - 1);meshes.push_back(tot - 1 - nangle);
			meshes.push_back(tot - 1 - nangle + 1);meshes.push_back(tot - 1 - nangle);meshes.push_back(tot - 1 - nangle + 1 - nangle);
		}
	}

}
void Bezier::Draw(char *s, int ttot, int angletot)
{
	RotateToM(ttot, angletot);
	FILE *fin = fopen(s, "w");
	for (int i = 0;i < pointstot;i++)
		fprintf(fin, "v %lf %lf %lf\n", points[i].x, points[i].y, points[i].z);
	int len = meshes.size();
	for (int i = 0;i < len;i += 3)
	{

		fprintf(fin, "f %d %d %d\n", meshes[i] + 1, meshes[i + 1] + 1, meshes[i + 2] + 1);
	}
	fclose(fin);
}
BoundingBox Bezier::GetBoindingBox(int lt, int rt, int langle, int rangle)
{
	double PI = acos(-1);
	double lT = (double)lt / TreeT, rT = (double)rt / TreeT;
	BoundingBox ans;
	ans.Xmax = ans.Ymax = ans.Zmax = -inf;
	ans.Xmin = ans.Ymin = ans.Zmin = inf;
	Maxt[1] = lT;Maxt[2] = rT;Maxt[3] = Yextremumt1;Maxt[4] = Yextremumt2;
	for (int i = 1;i <= 4;i++)
		if (Dcmp::dcmp(lT, Maxt[i]) <= 0 && Dcmp::dcmp(rT, Maxt[i]) >= 0)
		{

			ans.Zmin = std::min(ans.Zmin, Pt(Maxt[i], 0, n).y);
			ans.Zmax = std::max(ans.Zmax, Pt(Maxt[i], 0, n).y);
		}
	Maxt[1] = lT;Maxt[2] = rT;Maxt[3] = Xextremumt1;Maxt[4] = Xextremumt2;
	Maxa[1] = langle;
	Maxa[2] = rangle;
	Maxa[3] = Treeangle / 4;
	Maxa[4] = Treeangle / 2;
	Maxa[5] = Treeangle / 4 * 3;
	Maxa[6] = Treeangle;
	for (int i = 1;i <= 4;i++)
		if (Dcmp::dcmp(lT, Maxt[i]) <= 0 && Dcmp::dcmp(rT, Maxt[i]) >= 0)
			for (int j = 1;j <= 6;j++)
				if (langle <= Maxa[j] && rangle >= Maxa[j])
				{
					double jz = Pt(Maxt[i], 0, n).x;
					ans.Xmin = std::min(ans.Xmin, jz * cos((double)2 * PI*Maxa[j] / Treeangle));
					ans.Xmax = std::max(ans.Xmax, jz * cos((double)2 * PI*Maxa[j] / Treeangle));
					ans.Ymin = std::min(ans.Ymin, jz * sin((double)2 * PI*Maxa[j] / Treeangle));
					ans.Ymax = std::max(ans.Ymax, jz * sin((double)2 * PI*Maxa[j] / Treeangle));
				}
	return ans;
}
void Bezier::Build(int &node, int lt, int rt, int langle, int rangle)
{
	if (lt == rt) return;
	if (langle == rangle) return;
	node = ++top;
	boundingBoxs[node] = GetBoindingBox(lt, rt, langle, rangle);
	if (lt == rt - 1 && langle == rangle - 1) return;
	int midt = (lt + rt) / 2, midangle = (langle + rangle) / 2;
	Build(Treeson[node][0], lt, midt, langle, midangle);
	Build(Treeson[node][1], midt, rt, langle, midangle);
	Build(Treeson[node][2], lt, midt, midangle, rangle);
	Build(Treeson[node][3], midt, rt, midangle, rangle);
}
bool Bezier::RayInterBox(const BoundingBox &Box, const Point3 &start, const Point3 &dir, double &dissqr, double &nt)
{
	bool ok = 0;
	dissqr = inf;
	double Xmin = Box.Xmin, Xmax = Box.Xmax, Ymin = Box.Ymin, Ymax = Box.Ymax, Zmin = Box.Zmin, Zmax = Box.Zmax;
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
			nt = t;
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
			nt = t;
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
			nt = t;
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
			nt = t;
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
			nt = t;
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
			nt = t;
		}
	}
	return ok;
}
bool Bezier::RayIntersection(const Point3 &start, const Point3 &dir, const Point3 &info, Point3 &inter, Point3 &N, Point3 &interinfo)
{
	double t1 = info.x, t2 = info.y, angle = info.z;//x=t1,y=t2,z=angle
	Point3 bzins = Pt(t2, 0, n);
	inter.z = bzins.y;
	inter.x = bzins.x*cos(angle);
	inter.y = bzins.x*sin(angle);
	double PI = acos(-1);
	for (int i = 1;i <= 7;i++)
	{
		Point3 P1 = Pt1(t2), P = Pt(t2, 0, n);
		Point3 dsdt;
		dsdt.x = P1.x*cos(angle);
		dsdt.y = P1.x*sin(angle);
		dsdt.z = P1.y;
		Point3 dsda;
		dsda.x = P.x*(-sin(angle));
		dsda.y = P.x*cos(angle);
		dsda.z = 0;
		double D = Point3::dot(dir, Point3::det(dsdt, dsda));
		Point3 df, C, S;
		C = start + dir*t1;
		S.x = P.x*cos(angle);
		S.y = P.x*sin(angle);
		S.z = P.y;
		df = C - S;
		t1 -= Point3::dot(dsdt, Point3::det(dsda, df)) / D;
		t2 -= Point3::dot(dir, Point3::det(dsda, df)) / D;
		angle += Point3::dot(dir, Point3::det(dsdt, df)) / D;
	}
	if (Dcmp::dcmp(t1) <= 0) return 0;
	if (Dcmp::dcmp(t2)<0) return 0;
	if (Dcmp::dcmp(t2)>1) return 0;
	if (Dcmp::dcmp(angle)<0) return 0;
	if (Dcmp::dcmp(angle)>2 * PI) return 0;
	inter = start + dir*t1;
	Point3 beziertwo = Pt(t2, 0, n);
	Point3 bezierinter;
	bezierinter.z = beziertwo.y;
	bezierinter.x = beziertwo.x*cos(angle);
	bezierinter.y = beziertwo.x*sin(angle);
	if (Dcmp::dcmp(t1) == 0) return 0;
	if (Dcmp::dcmp(inter.x, bezierinter.x) != 0) return 0;
	if (Dcmp::dcmp(inter.y, bezierinter.y) != 0) return 0;
	if (Dcmp::dcmp(inter.z, bezierinter.z) != 0) return 0;
	Point3 R = Pt1(t2);
	Point3 L;
	L.x = R.y;L.y = -R.x;
	N.z = L.y;
	N.x = L.x*cos(angle);
	N.y = L.x*sin(angle);
	interinfo.x = t1;
	interinfo.y = t2;
	interinfo.z = angle;
	return 1;
}
bool Bezier::Findins(int node, int lt, int rt, int langle, int rangle, const Point3 &start, const Point3 &dir, Point3 &inter, Point3 &Ndir)
{
	if (!node) return 0;
	double dissqr = inf;
	if (lt == rt - 1 && langle == rangle - 1)
	{
		double PI = acos(-1);
		double l = (double)lt / TreeT, r = (double)rt / TreeT;
		double t = 0, dissqr = inf;
		if (!RayInterBox(boundingBoxs[node], start, dir, dissqr, t)) return 0;
		double angle1 = (double)2 * PI*langle / Treeangle, angle2 = (double)2 * PI*rangle / Treeangle;
		Point3 info = Point3(t, (l + r) / 2, (angle1 + angle2) / 2);
		Point3 newinterinfo;
		if (!RayIntersection(start, dir, info, inter, Ndir, newinterinfo)) return 0;
		if (Dcmp::dcmp(Point3::Dissqr(inter - start), Point3::Dissqr(Minter - start)) < 0)
		{
			Minter = inter;
			MinNdir = Ndir;
			Mininfo = newinterinfo;
		}
		return 1;
	}
	int midt = (lt + rt) / 2, midangle = (langle + rangle) / 2;
	double sondissqr[4];
	double nouset;
	bool ok = 0;
	int  newlt[4], newrt[4], newla[4], newra[4];
	newlt[0] = lt;newrt[0] = midt;newla[0] = langle;newra[0] = midangle;
	newlt[1] = midt;newrt[1] = rt;newla[1] = langle;newra[1] = midangle;
	newlt[2] = lt;newrt[2] = midt;newla[2] = midangle;newra[2] = rangle;
	newlt[3] = midt;newrt[3] = rt;newla[3] = midangle;newra[3] = rangle;
	for (int i = 0;i < 4;i++)
	{
		sondissqr[i] = inf;
		if (Treeson[node][i] && RayInterBox(boundingBoxs[Treeson[node][i]], start, dir, sondissqr[i], nouset)) ok = 1;
	}
	if (ok == 0) return 0;
	ok = 0;
	double sortdissqr[4];
	for (int i = 0;i < 4;i++)
		sortdissqr[i] = sondissqr[i];
	std::sort(sortdissqr, sortdissqr + 4);
	for (int i = 0;i <4;i++)
	{
		for (int j = 0;j < 4;j++)
			if (Dcmp::dcmp(sortdissqr[i], sondissqr[j]) == 0)
			{
				sondissqr[j] = -1;
				if (Findins(Treeson[node][j], newlt[j], newrt[j], newla[j], newra[j], start, dir, inter, Ndir))	ok = 1;

			}
	}
	return ok;
}
void Bezier::setall(std::vector<Point3> &POINT, int N = 0)
{
	inf = 100000000;
	n = N;
	P.clear();
	
	for (int i = 0;i <= n;i++)
		P.push_back(POINT[i]);
	GetExtremumY(Yextremumt1, Yextremumt2);
	GetExtremumX(Xextremumt1, Xextremumt2);
	TreeT = 100;Treeangle = 100;top = 0;
	Build(root, 0, TreeT, 0, Treeangle);
}
bool Bezier::GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &Ndir, Point3 &interinfo)
{
	Point3 newstart = start - position;
	Point3 newdir = dir;
	Minter.x = Minter.y = Minter.z = 100000000;
	if (!Findins(root, 0, TreeT, 0, Treeangle, newstart, newdir, inter, Ndir)) return 0;//包围盒建成的四分树
	inter = Minter + position;
	Ndir = MinNdir;
	interinfo = Mininfo;
	dissqr = Point3::Dissqr(inter - start);
	return 1;
}