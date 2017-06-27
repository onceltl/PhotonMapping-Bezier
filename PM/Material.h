#ifndef MATERIAL_H
#define MATERIAL_H
#include"Color.h"
class Material
{
public:
	Color Ka, Ks, Kt, Kds;//环境，反射，折射，漫反射，漫折射系数
	Color color;
	int nt, ns;
	double rindex;//折射率
	double refl, refr, diff;//反射，折射，漫反射
	void load(Color color, double refl, double refr, double diff, double rindex, int ns, int nt);//设置
	void Material::changecolor(const Color &newcolor);//颜色改变
};
#endif // MATERIAL_H
