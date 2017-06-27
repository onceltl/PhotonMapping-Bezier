#include<cstdio>
#include"RacTracer.h"
#include"lodepng.h"
#define DEBUG
RayTracer rayT;
Graph_Bezier bezier;
Graphset graphset;
Graph_Plane plane;
Material material;
std::vector<unsigned char > image;
void JoinGraph(RayTracer &rayT)
{
	//正面
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.Loadtexture("1.png");
	plane.material = material;
	plane.D = 200;
	plane.N = Point3(0, -1, 0);
	graphset.AddPlane(plane);
	//背面
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 210;
	plane.N = Point3(0, 1, 0);
	graphset.AddPlane(plane);
	//顶面
/*	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 210;
	plane.N = Point3(0, 0, -1);
	graphset.AddPlane(plane);*/
	//底面

	plane.Loadtexture("4.png");
	material.load(Color(1, 1, 1), 0.0, 0.0, 0.9, 1.5, 1, 1);
	plane.material = material;
	plane.D = 0;
	plane.N = Point3(0, 0, 1);
	graphset.AddPlane(plane);
	plane.Loadtexture("2.png");
	//左侧
	//plane.Loadtexture("4.png");
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 100;
	plane.N = Point3(1, 0, 0);
	graphset.AddPlane(plane);

	//右侧
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 1, 1);
	plane.material = material;
	plane.D = 100;
	plane.N = Point3(-1, 0, 0);
	graphset.AddPlane(plane);
	plane.texture.clear();



	//折射玻璃球
	Graph_Ball ball;
	ball.P = Point3(0, 40, 15);
	ball.R = 15.0;
	material.load(Color(1, 1, 1), 0.0, 0.8, 0, 1.5, 1, 1);
	ball.material = material;
	graphset.AddBall(ball);
	//反射玻璃球
	ball.P = Point3(60, 60, 40);
	ball.R = 15.0;
	material.load(Color(1, 1, 1), 0.8, 0.0, 0, 1.5, 1, 1);
	ball.material = material;
	graphset.AddBall(ball);
	//贝塞尔曲线
	std::vector<Point3> Point;
	Point.push_back(Point3(0, 0, 0));
	Point.push_back(Point3(14 * 2.5, 4 * 2.5, 0));
	Point.push_back(Point3(9 * 2.5, 20 * 2.5, 0));
	Point.push_back(Point3(0, 12 * 2.5, 0));
	bezier.setall(Point, 3);
	bezier.position = Point3(-40, 150.0, 0);
	material.load(Color(1, 1, 1), 0.0, 0.0, 0.9, 2, 1, 1);
	bezier.material = material;
	bezier.Loadtexture("3.png");
	graphset.AddBezier(bezier);
	
	
	rayT.SetGraphset(graphset);
}
int main()
{
	//设置光源相机
	Light light;
	light.color = Color(1, 1, 1);
	light.o = Point3(0, 100, 300);
	rayT.Addlight(light);
	rayT.SetCamera(500, 500, 0, 100, Point3(0, -200, 100));
	

	JoinGraph(rayT);//加入图形
	rayT.Run();//渲染

	//图形编码到指定文件
	char *filename;
	filename = "test.png";
	rayT.Draw(filename);
	
	return 0;
}