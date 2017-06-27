#ifndef BEZIER_H
#define BEZIER_H
#include"Point3.h"
#include<vector>
struct BoundingBox
{
	double Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
};
class Bezier//由Bezier曲线旋转构成的平面
{
protected:
	double Ber(int x, int y);
	double Yextremumt1, Yextremumt2;//Y方向极值处的t
	double Xextremumt1, Xextremumt2;
	double inf;
	void RotateToM(int ttot, int angletot);//平面曲线绕Y轴转动获得三角面片
	void GetExtremumY(double &extremumt1, double &extremumt2);
	void GetExtremumX(double &extremumt1, double &extremumt2);
	void  GetBernstein(double t);//求B矩阵
	Point3 Pt2(double t);//2阶导数
	Point3 Pt1(double t);//1阶导数
	bool GetPt2Zero(double &t);//2阶导数零点
	bool GetPt1Zero(double L, double R, double &t);//1阶导数零点
	double Maxt[10];
	int Maxa[10];
	int root;//4叉树树根
	int top;//树的个数
	BoundingBox boundingBoxs[2000000];//每个节点代表的包围盒
	int Treeson[2000000][4];//每个节点的儿子
	int TreeT, Treeangle;//树的大小
	BoundingBox GetBoindingBox(int lt, int rt, int langle, int rangle);//通过曲面面片得到长方体包围盒

	bool RayInterBox(const BoundingBox &Box, const Point3 &start, const Point3 &dir, double &dissqr, double &nt);//光线与包围盒
	bool RayIntersection(const Point3 &start, const Point3 &dir, const Point3 &info, Point3 &inter, Point3 &N, Point3 &interinfo);//牛顿迭代
	void Build(int &node, int lt, int rt, int langle, int rangle);//建树
	bool Findins(int node, int lt, int rt, int langle, int rangle, const Point3 &start, const Point3 &dir, Point3 &inter, Point3 &N);//求4分树交点
public:
	int n;
	Point3	position;
	Point3 Minter, MinNdir, Mininfo;
	//int angletot, ttot;//XY平面角度个数，Z方向点的个数
	double B[5][5];//Bernstein矩阵
	std::vector<Point3> P;//特征多边形
	std::vector<Point3> points;//曲面上的点
	int pointstot;
	std::vector<int> meshes;//网格点
	void setall(std::vector<Point3> &POINT, int N);//特征多边形  
	~Bezier() {};
	Point3 Pt(double t, int x, int k);//当参数为t时候坐标
	void Draw(char *s, int ttot, int angletot);//画出OBJ格式到S文件
	bool GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &N, Point3 &interinfo);
};
#endif // !BEZIER_H
