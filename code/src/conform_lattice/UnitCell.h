#pragma once
#include <math.h>
#include <cmath>

namespace rk9 {

	class UnitCell {

	public:
		virtual double Eval() {
			return 0.0;
		};
	};


	class Schwarz_Primitive : public UnitCell {

	public:
		double Eval(double x, double y, double z) {
			return (cos(x) + cos(y) + cos(z) - 1);
		}
	};


	class Schwarz_Primitive_pinched : public UnitCell {

	public:
		double Eval(double x, double y, double z) {
			return (-(2.25*(cos(x) + cos(y) + cos(z)) + 1.25*(cos(x)*cos(y) + cos(y)*cos(z) + cos(z)*cos(x))));
		}
	};


	class Schoen_Gyroid : public UnitCell {

	public:
		double Eval(double x, double y, double z) {
			return (10 * (cos(x)*sin(y) + cos(y)*sin(z) + cos(z)*sin(x))
				- 0.5*(cos(2 * x)*cos(2 * y) + cos(2 * y)*cos(2 * z) + cos(2 * z)*cos(2 * x)));
		}
	};


	class Schwarz_W : public UnitCell {

	public:
		double Eval(double x, double y, double z) {
			return (10 * (cos(x)*cos(y) + cos(y)*cos(z) + cos(z)*cos(x))
				- 5 * (cos(2 * x) + cos(2 * y) + cos(2 * z)) - 14);
		}
	};

	class Neovius_Surface : public UnitCell {

	public:
		double Eval(double x, double y, double z) {
			return (-(-sin(x)*sin(y)*sin(z) + sin(2 * x)*sin(y) + sin(2 * y)*sin(z) + sin(x)*sin(2 * z)
				- cos(x)*cos(y)*cos(z) + sin(2 * x)*cos(z) + cos(x)*sin(2 * y) + cos(y)*sin(2 * z)));
		}
	};
}