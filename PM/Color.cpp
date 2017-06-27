#include"Color.h"
#include"Dcmp.h"
Color operator +(const Color &a, const Color &b)
{
	Color ans;
	ans.r = a.r + b.r;
	ans.g = a.g + b.g;
	ans.b = a.b + b.b;
	return ans;
}
Color operator -(const Color &a, const Color &b)
{
	Color ans;
	ans.r = a.r - b.r;
	ans.g = a.g - b.g;
	ans.b = a.b - b.b;
	return ans;
}
Color operator *(const Color &a, double b)
{
	Color ans;
	ans.r = a.r * b;
	ans.g = a.g * b;
	ans.b = a.b * b;
	return ans;
}

Color operator /(const Color &a, double b)
{
	Color ans;
	ans.r = a.r / b;
	ans.g = a.g / b;
	ans.b = a.b / b;
	return ans;
}

Color operator *(const Color &a, const Color &b)
{
	Color ans;
	ans.r = a.r*b.r;
	ans.g = a.g*b.g;
	ans.b = a.b*b.b;
	return ans;
}
void Color::confi()
{
	if (Dcmp::dcmp(r, 1) > 0) r = 1;

	if (Dcmp::dcmp(g, 1) > 0) g = 1;

	if (Dcmp::dcmp(b, 1) > 0) b = 1;
}