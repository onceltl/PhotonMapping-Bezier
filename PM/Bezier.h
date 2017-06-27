#ifndef BEZIER_H
#define BEZIER_H
#include"Point3.h"
#include<vector>
struct BoundingBox
{
	double Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
};
class Bezier//��Bezier������ת���ɵ�ƽ��
{
protected:
	double Ber(int x, int y);
	double Yextremumt1, Yextremumt2;//Y����ֵ����t
	double Xextremumt1, Xextremumt2;
	double inf;
	void RotateToM(int ttot, int angletot);//ƽ��������Y��ת�����������Ƭ
	void GetExtremumY(double &extremumt1, double &extremumt2);
	void GetExtremumX(double &extremumt1, double &extremumt2);
	void  GetBernstein(double t);//��B����
	Point3 Pt2(double t);//2�׵���
	Point3 Pt1(double t);//1�׵���
	bool GetPt2Zero(double &t);//2�׵������
	bool GetPt1Zero(double L, double R, double &t);//1�׵������
	double Maxt[10];
	int Maxa[10];
	int root;//4��������
	int top;//���ĸ���
	BoundingBox boundingBoxs[2000000];//ÿ���ڵ����İ�Χ��
	int Treeson[2000000][4];//ÿ���ڵ�Ķ���
	int TreeT, Treeangle;//���Ĵ�С
	BoundingBox GetBoindingBox(int lt, int rt, int langle, int rangle);//ͨ��������Ƭ�õ��������Χ��

	bool RayInterBox(const BoundingBox &Box, const Point3 &start, const Point3 &dir, double &dissqr, double &nt);//�������Χ��
	bool RayIntersection(const Point3 &start, const Point3 &dir, const Point3 &info, Point3 &inter, Point3 &N, Point3 &interinfo);//ţ�ٵ���
	void Build(int &node, int lt, int rt, int langle, int rangle);//����
	bool Findins(int node, int lt, int rt, int langle, int rangle, const Point3 &start, const Point3 &dir, Point3 &inter, Point3 &N);//��4��������
public:
	int n;
	Point3	position;
	Point3 Minter, MinNdir, Mininfo;
	//int angletot, ttot;//XYƽ��Ƕȸ�����Z�����ĸ���
	double B[5][5];//Bernstein����
	std::vector<Point3> P;//���������
	std::vector<Point3> points;//�����ϵĵ�
	int pointstot;
	std::vector<int> meshes;//�����
	void setall(std::vector<Point3> &POINT, int N);//���������  
	~Bezier() {};
	Point3 Pt(double t, int x, int k);//������Ϊtʱ������
	void Draw(char *s, int ttot, int angletot);//����OBJ��ʽ��S�ļ�
	bool GetInter(const Point3 &start, const Point3 &dir, Point3 &inter, double &dissqr, Point3 &N, Point3 &interinfo);
};
#endif // !BEZIER_H
