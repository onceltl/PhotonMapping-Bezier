#include"Material.h"
#include<cstdio>
void Material::load(Color incolor, double inrefl, double inrefr, double indiff, double inrindex, int inns, int innt)
{
	color = incolor;
	refl = inrefl;
	refr = inrefr;
	diff = indiff;
	rindex = inrindex;
	ns = inns;
	nt = innt;
	Ka = Color(0, 0, 0);
	Ks = color*refl;
	Kds = color*diff;
	Kt = color*refr;
}
void Material::changecolor(const Color &newcolor)
{
	color = newcolor;
	Ks = color*refl;
	Kds = color*diff;
	Kt = color*refr;
}