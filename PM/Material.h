#ifndef MATERIAL_H
#define MATERIAL_H
#include"Color.h"
class Material
{
public:
	Color Ka, Ks, Kt, Kds;//���������䣬���䣬�����䣬������ϵ��
	Color color;
	int nt, ns;
	double rindex;//������
	double refl, refr, diff;//���䣬���䣬������
	void load(Color color, double refl, double refr, double diff, double rindex, int ns, int nt);//����
	void Material::changecolor(const Color &newcolor);//��ɫ�ı�
};
#endif // MATERIAL_H
