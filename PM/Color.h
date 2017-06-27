#ifndef COLOR_H
#define COLOR_H
class Color
{
public:
	double r, g, b;
	Color(double R = 0, double G = 0, double B = 0) :r(R), g(G), b(B) {};
	~Color() {};
	friend Color operator +(const Color &a, const Color &b);
	friend Color operator -(const Color &a, const Color &b);
	friend Color operator *(const Color &a, const Color &b);
	friend Color operator /(const Color &a, double b);
	friend Color operator *(const Color &a, double b);
	void confi();
};
#endif // COLOR_H
