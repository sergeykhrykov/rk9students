#include <stdio.h>
#include "common/PolyModel.h"
#include "MarchingCubes.h"
#include "UnitCell.h"
#include "Transform.h"
#include <string>

using namespace rk9;
using namespace std;


bool run(MarchingCubes &mc, double Length, double Width, double Height){
					
	enum Axis { X = 0, Y = 1, Z = 2 };
	
	float rx = (Length) / (mc.size().x - 1);
	float ry = (Width) / (mc.size().y - 1);
	float rz = (Height) / (mc.size().z - 1);

	glm::vec3 min_pos(0, 0, 0);
	glm::vec3 range(rx, ry, rz);

	for (int i = 0; i < mc.size().x; i++) {
		float val[3];
		val[X] = (float)i * rx;
		for (int j = 0; j < mc.size().y; j++) {
			val[Y] = (float)j * ry;
			for (int k = 0; k < mc.size().z; k++) {
				val[Z] = (float)k * rz;

				Schoen_Gyroid Cell;
				double build_cell = Cell.Eval(val[X], val[Y], val[Z]);
				mc.set_data(build_cell, glm::ivec3(i, j, k));
			}
		}
	}

	// Run MC
	mc.SetAlgorithm(MarchingCubes::TopologicalMarchingCubes);
	mc.run();

	// Rescale positions
	for (int i = 0; i < mc.nverts(); ++i) {
		Vertex &v = mc.vertices()[i];
		v.pos = range * v.pos + min_pos;
		v.n = glm::normalize(v.n);
	}

	return true;
}


int main (int argc, char ** argv) {
	
	/*на вход принимаются параметры из командной строки:
	-тип фигуры (1-цилиндр, 0 - сфера)
	-радиус цилиндра/сферы
	-толщина слоя
	-высота цилиндра/зенитный угол сферы
	-угол сектора цилиндра/азимутальный угол сектора сферы
	-Направление наращивания 1 - положительное, 0 - отрицательное
	*/
	
	/*примеры входных данных цилиндра:
	1 10 5 30 360 1
	1 10 5 30 270 0
	*/
	
	/*примеры входных данных сферы:
	0 10 5 360 360 1
	0 10 5 180 270 0
	*/
	
	
	const double PI = 3.141592653589793;
	//множитель перевода из градусов в радианы
	double DegToRad = PI / 180;
	//Тип фигуры 
	double Type = stod(argv[1]);
	//радиус
	double R = stod(argv[2]);
	//толщина (ширина прямоугольной решетки для "оборачивания")
	double Width = stod(argv[3]);
	//высота цилиндра/длина сектора сферы по зениту (высота прямоугольной решетки для "оборачивания")
	double Height;
	//зенитный угол сектора сферы
	double Theta0;
	if (Type)
		Height = stod(argv[4]);
	else
	{
		Theta0 = stod(argv[4]) * DegToRad;
		Height = Theta0 * R;
	}	
	//угол сектора цилиндра/азимутальный угол сектора сферы
	double Phi0 = stod(argv[5]) * DegToRad;
	//длина сектора цилиндра/сектора сферы по азимуту(длина прямоугольной решетки для "оборачивания")
	double Length = Phi0 * R;
	//Направление наращивания 1 - положительное, 0 - отрицательное
	double Dir;
	if (stod(argv[6]))
		Dir = 1;
	else
		Dir = -1;
	
	MarchingCubes mc(glm::ivec3(100));
	mc.Setup();
	
	//запуск построения прямоугольной решетки
	run(mc, Length, Width, Height);

	//std vector shrink to fit
	//resize
	//shrink_to_fit

	auto verts = std::vector<glm::vec3>();
	verts.reserve(mc.ntrigs() * 3);

	rk9::PolyModel m;

	for (int i = 0; i < mc.ntrigs(); ++i) {
		auto tri = mc.trig(i);

		rk9::Point p[3];
		for (int t = 0; t < 3; ++t) {
			auto vertex = mc.vert(tri.ids[t]).pos;
			p[t].X = vertex.x;
			p[t].Y = vertex.y;
			p[t].Z = vertex.z;


			if(Type)
			{
				//запуск трасформации прямоугольной решетки в цилиндрическую
				Cylindric_Transformation Coords;
				p[t] = Coords.Transform(p[t], R, Dir, i);
			}
			else
			{ 
				//запуск трасформации прямоугольной решетки в сферическую
				Spheric_Transformation Coords;
				p[t] = Coords.Transform(p[t], R, Dir);
			}

		}

		m.AddTriangle(p[0], p[1], p[2]);
	}

	m.WriteToSTLFile("output.stl");

	return 0;
}