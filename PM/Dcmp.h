#ifndef DCMP_H
#define DCMP_H
#include<cstdio>
const double eps = 1e-8;
class Dcmp
{
public:
	static int dcmp(double a, double b = 0)
	{
		if (a - b > eps) return 1;
		if (b - a > eps) return -1;
		return 0;
	}
};
#endif // !DCMP_H
