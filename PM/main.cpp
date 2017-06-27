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
	//����
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.Loadtexture("1.png");
	plane.material = material;
	plane.D = 200;
	plane.N = Point3(0, -1, 0);
	graphset.AddPlane(plane);
	//����
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 210;
	plane.N = Point3(0, 1, 0);
	graphset.AddPlane(plane);
	//����
/*	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 210;
	plane.N = Point3(0, 0, -1);
	graphset.AddPlane(plane);*/
	//����

	plane.Loadtexture("4.png");
	material.load(Color(1, 1, 1), 0.0, 0.0, 0.9, 1.5, 1, 1);
	plane.material = material;
	plane.D = 0;
	plane.N = Point3(0, 0, 1);
	graphset.AddPlane(plane);
	plane.Loadtexture("2.png");
	//���
	//plane.Loadtexture("4.png");
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 2, 2);
	plane.material = material;
	plane.D = 100;
	plane.N = Point3(1, 0, 0);
	graphset.AddPlane(plane);

	//�Ҳ�
	material.load(Color((double)255 / 255, (double)218 / 255, (double)185 / 255), 0.0, 0.0, 0.9, 1.5, 1, 1);
	plane.material = material;
	plane.D = 100;
	plane.N = Point3(-1, 0, 0);
	graphset.AddPlane(plane);
	plane.texture.clear();



	//���䲣����
	Graph_Ball ball;
	ball.P = Point3(0, 40, 15);
	ball.R = 15.0;
	material.load(Color(1, 1, 1), 0.0, 0.8, 0, 1.5, 1, 1);
	ball.material = material;
	graphset.AddBall(ball);
	//���䲣����
	ball.P = Point3(60, 60, 40);
	ball.R = 15.0;
	material.load(Color(1, 1, 1), 0.8, 0.0, 0, 1.5, 1, 1);
	ball.material = material;
	graphset.AddBall(ball);
	//����������
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
	//���ù�Դ���
	Light light;
	light.color = Color(1, 1, 1);
	light.o = Point3(0, 100, 300);
	rayT.Addlight(light);
	rayT.SetCamera(500, 500, 0, 100, Point3(0, -200, 100));
	

	JoinGraph(rayT);//����ͼ��
	rayT.Run();//��Ⱦ

	//ͼ�α��뵽ָ���ļ�
	char *filename;
	filename = "test.png";
	rayT.Draw(filename);
	
	return 0;
}