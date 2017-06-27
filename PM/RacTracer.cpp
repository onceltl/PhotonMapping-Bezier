#include"RacTracer.h"
#include "Material.h"
#include"lodepng.h"
#include"Dcmp.h"
double Pow(double x, int k)
{
	if (k == 0) return 1;
	double ans = Pow(x, k / 2);
	ans = ans*ans;
	if (k % 2) ans = ans*x;
	return ans;
}
Point3 Camera::getdir(int x, int y)
{
	Point3 b;
	b.z = watch.z - Len + ((double)2 * Len*x / (H - 1));
	b.x = watch.x - Len + ((double)2 * Len*y / (W - 1));
	b.y = Y;
	return b - watch;
}
RayTracer::RayTracer()
{
	Lighttot = 0;
	lights.clear();
	WEIGHT = 0.01;
}
void RayTracer::Addlight(const Light &a)
{
	Lighttot++;
	lights.push_back(a);
}
void RayTracer::SetCamera(int h, int w, double y, double len, Point3 watch)
{
	camera.H = h;
	camera.W = w;
	camera.Y = y;
	camera.Len = len;
	camera.watch = watch;
}
void RayTracer::SetGraphset(const Graphset &myset)
{
	graphset = myset;
}
Color RayTracer::RayTracing(Point3 start, Point3 dir, double weight, int step)
{
	Color color;
	if (Dcmp::dcmp(weight, WEIGHT) < 0) return color;
	Material material;
	Point3 inter;
	double dissqr;
	Point3 N, N2;
	Point3 V = Point3::ToOne(dir*(-1));
	if (graphset.Findfirst(start, dir, material, inter, dissqr, N))
	{
		N = Point3::ToOne(N);
		for (int i = 0;i < Lighttot;i++)
		{
			double Dis;
			Point3 inter2;
			Material material2;
			Point3 L = Point3::ToOne(lights[i].o - inter);
			Point3 R = N * 2 * Point3::dot(N, L) - L;
			if (graphset.Findfirst(inter, L, material2, inter2, Dis, N2))
			{
				//phone模型
				if (Dcmp::dcmp(Point3::Dissqr(lights[i].o - inter), Dis) < 0)
				{
					if (Dcmp::dcmp(Point3::dot(L, N))>0)   color = color + lights[i].color*(material.Kds*(Point3::dot(L, N)))*0.1;
					if (Dcmp::dcmp(Point3::dot(R, V)) > 0) color = color + lights[i].color*(material.Ks*Pow(Point3::dot(R, V), material.ns));
					//color = color + lights[i].color*(material.Kds*(Point3::dot(L, N)) + material.Ks*Pow(Point3::dot(R, V), material.ns));
					//color = color + lights[i].color*(material.Kdt*(Point3::dot(N*(-1), L)) + material.Kt*Pow(Point3::dot(R, V), material.nt));

				}
			}
			else {

				if (Dcmp::dcmp(Point3::dot(L, N))>0)   color = color + lights[i].color*(material.Kds*(Point3::dot(L, N)))*0.1;
				if (Dcmp::dcmp(Point3::dot(R, V)) > 0) color = color + lights[i].color*(material.Ks*Pow(Point3::dot(R, V), material.ns));
				//color = color + lights[i].color*(material.Kds*(Point3::dot(L, N)) + material.Ks*Pow(Point3::dot(R, V), material.ns));
				//color = color + lights[i].color*(material.Kdt*(Point3::dot(N*(-1), L)) + material.Kt*Pow(Point3::dot(R, V), material.nt));
			}

		}
		
		color = color + material.Ka*Roundcolor;//环境光
		color=color+kdtree.Getcolor(inter);//光子图K邻近
		//递归跟踪
		if (step > 0)
		{

			if (Dcmp::dcmp(material.refl) != 0)//反射
			{
				Point3 Ldir = Point3::ToOne(dir*(-1));
				Point3 R = N * 2 * Point3::dot(N, Ldir) - Ldir;
				color = color + material.Ks*RayTracing(inter, R, weight*material.refl, step - 1);
			}
			if (Dcmp::dcmp(material.refr) != 0)//折射
			{

				Point3 I = Point3::ToOne(dir*(-1));
				double rindex = 1 / material.rindex;
				if (Dcmp::dcmp(Point3::dot(I, N)) < 0)//内部
				{
					rindex = material.rindex;
					N = N*(-1);
				}
				double cosI = Point3::dot(I, N);
				double cosT = 1 - rindex*rindex*(1 - cosI*cosI);
				if (Dcmp::dcmp(cosT) < 0)return color;
				cosT = sqrt(cosT);
				Point3 T = I*(-rindex) - N*(cosT - rindex*cosI);
				color = color + material.Kt*RayTracing(inter, T, weight*material.refr, step - 1);;
			}
		}
	}
	//printf("color%lf %lf %lf\n",color);
	return color;
}
void RayTracer::Emit(const Point3 &start, const Point3 &dir, const Color &color, int step)
{
	if (kdtree.n >= photontot) return;
	if (step == 0) return;
	Material material;
	Point3 inter;
	double dissqr;
	Point3 N;
	Point3 V = Point3::ToOne(dir*(-1));
	if (graphset.Findfirst(start, dir, material, inter, dissqr, N))
	{
		N = Point3::ToOne(N);
		Color newcolor = color*material.color;
		double energy = (newcolor.r+newcolor.g+newcolor.b)/3;
		if (Dcmp::dcmp(energy) != 0) newcolor = newcolor / energy;
		double probability = double(rand() % 101);
		probability /= 100;
		if (Dcmp::dcmp(probability,material.refl) <0)//反射
		{
			Point3 Ldir = Point3::ToOne(dir*(-1));
			Point3 R = N * 2 * Point3::dot(N, Ldir) - Ldir;
			Emit(inter,R,newcolor,step-1);
			return;
		}
		if (Dcmp::dcmp(probability, material.refl+material.refr) < 0)//折射
		{

			Point3 I = Point3::ToOne(dir*(-1));
			double rindex = 1 / material.rindex;
			if (Dcmp::dcmp(Point3::dot(I, N)) < 0)//内部
			{
				rindex = material.rindex;
				N = N*(-1);
			}
			double cosI = Point3::dot(I, N);
			double cosT = 1 - rindex*rindex*(1 - cosI*cosI);
			if (Dcmp::dcmp(cosT) < 0)return ;
			cosT = sqrt(cosT);
			Point3 T = I*(-rindex) - N*(cosT - rindex*cosI);
			Emit(inter, T, newcolor, step - 1);
			return;
		}
		
		if (Dcmp::dcmp(probability, material.refl + material.refr+material.diff) < 0)//漫反射
		{
			kdtree.Add(inter,newcolor);
			Point3 newdir = Point3::RandomP();
			while (Dcmp::dcmp(Point3::dot(newdir, N)) <= 0)newdir = Point3::RandomP();
			Emit(inter, newdir, newcolor, step - 1);
			return;
		}
		
	}
}
void RayTracer::Run()
{

	Point3 dir = Point3::RandomP();
	//发射光子建立光子图
	photontot = 10000000;
	kdtree.SetMax(photontot);
	while (kdtree.n < photontot)
	{
		Point3 dir = Point3::RandomP();
		for (int i = 0;i < lights.size();i++)
			Emit(lights[i].o, dir, lights[i].color, 5);
	}
	printf("%d\n",kdtree.n);
	kdtree.build(0,kdtree.n-1);
	
	//跟踪视线采集光子
	for (int i = 0;i < camera.H;i++)
	{
		for (int j = 0;j < camera.W;j++)
		{
			pix[i][j] = RayTracing(camera.watch, camera.getdir(camera.H - 1 - i, j), 1, 5);
			//	printf("%d %d %lf %lf %lf\n", i, j,pix[i][j]);
		}
		if (i%10==0)printf("%d\n",i);
	}
}
void RayTracer::encodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned width, unsigned height)
{
	unsigned error = lodepng::encode(filename, image, width, height);
}
void RayTracer::Draw(const char *filename)
{
	image.clear();
	image.resize(camera.H*camera.W * 4);
	for (int i = 0;i < camera.H;i++)
		for (int j = 0;j < camera.W;j++)
		{
			pix[i][j].confi();
			image[4 * camera.W * i + 4 * j + 0] = pix[i][j].r * 255;
			image[4 * camera.W * i + 4 * j + 1] = pix[i][j].g * 255;
			image[4 * camera.W * i + 4 * j + 2] = pix[i][j].b * 255;
			image[4 * camera.W * i + 4 * j + 3] = 255;
		}
	encodeOneStep(filename, image, camera.W, camera.H);
}