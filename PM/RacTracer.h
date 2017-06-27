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
	Camera camera;//相机
	int Lighttot;//光源个数
	std::vector<Light> lights;//光源
	Color pix[7000][7000];//像素
	std::vector<unsigned char> image;//图片
	double WEIGHT;
	int photontot;//最大光子个数
	Kdtree kdtree;//kdtree储存的光子图
	Color  RayTracing(Point3 start, Point3 dir, double weight, int step);//递归追踪光线
	Color Roundcolor;//环境光
	void encodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned width, unsigned height);//编码为png输出
	void RayTracer::Emit(const Point3 &start, const Point3 &dir, const Color &color, int step);//发射光子
	int all;
public:
	RayTracer();
	Graphset graphset;//物品集合
	void Addlight(const Light &a);//添加光源
	void SetCamera(int h, int w, double y, double len, Point3 watch);//设置视角
	void SetGraphset(const Graphset &myset);
	void Run();//渲染
	void Draw(const char *filename);
};
#endif // !RACTRACER_H
