#ifndef RACTRACER_H
#define RACTRACER_H
#include"Point3.h"
#include"Color.h"
#include"Graph.h"
#include"Kdtree.h"
#include<vector>
class Camera
{
public:
	int H, W;
	double Y;
	double Len;
	Point3 watch;
	Camera(int h = 0, int w = 0, double y = 0, double len = 0) :H(h), W(w), Y(y), Len(len) {};
	Point3 getdir(int x, int y);
};
class Light
{
public:
	Point3 o;
	Color color;
};
class RayTracer
{
	Camera camera;//���
	int Lighttot;//��Դ����
	std::vector<Light> lights;//��Դ
	Color pix[7000][7000];//����
	std::vector<unsigned char> image;//ͼƬ
	double WEIGHT;
	int photontot;//�����Ӹ���
	Kdtree kdtree;//kdtree����Ĺ���ͼ
	Color  RayTracing(Point3 start, Point3 dir, double weight, int step);//�ݹ�׷�ٹ���
	Color Roundcolor;//������
	void encodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned width, unsigned height);//����Ϊpng���
	void RayTracer::Emit(const Point3 &start, const Point3 &dir, const Color &color, int step);//�������
	int all;
public:
	RayTracer();
	Graphset graphset;//��Ʒ����
	void Addlight(const Light &a);//��ӹ�Դ
	void SetCamera(int h, int w, double y, double len, Point3 watch);//�����ӽ�
	void SetGraphset(const Graphset &myset);
	void Run();//��Ⱦ
	void Draw(const char *filename);
};
#endif // !RACTRACER_H
