#pragma once
#include <math.h>
#include <cmath>

namespace rk9 {

	class Conform_Transformation {

	public:
		virtual Point Transform() {
			return {0,0,0};
		};
	};

	class Cylindric_Transformation : public Conform_Transformation {

	public:
		Point Transform(Point p, double R, double Dir, int i) {
			
			//представление декартовых координат в виде соответствующих цилиндрических
			//перевод координат Х в Фи
			double Phi = p.X/R;
			//перевод координат Y в Ро
			double Ro = R + (Dir * p.Y);
			//перевод координат Z
			double Z = p.Z;

			//переход от цилиндрических координат в декартовые
			p.X = Ro * cos(Phi);
			p.Y = Ro * sin(Phi);
			p.Z = Z;

			return p;
		}
	};

	class Spheric_Transformation : public Conform_Transformation {

	public:
		Point Transform(Point p, double R, double Dir) {

			//представление декартовых координат в виде соответствующих сферических
			//перевод координат Х в Фи
			double Phi = p.X / R;
			//перевод координат Y в Ро
			double Ro = R + (Dir * p.Y);
			//перевод координат Z
			double Theta = p.Z / (2*R);

			//переход от цилиндрических координат в декартовые
			p.X = Ro * sin(Theta) * cos(Phi);
			p.Y = Ro * sin(Theta) * sin(Phi);
			p.Z = Ro * cos(Theta);

			return p;
		}
	};
}