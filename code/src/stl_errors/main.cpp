#include <iostream>
#include <vector>

#include "common/PolyModel.h"
#include "ModelEdges.h"

using namespace std;
using namespace rk9;

int main(int argc, char* argv[])
{
	PolyModel model;
	
	model.ReadFromSTLFile(argv[1]);      //считывание модели STL из файла

	ModelEdges edges;					     //создаем ветор рёбер модели

	auto hl = edges.FindErrors(model);			 //если вектор  hl содержит ребра, на этих ребрах дыры; если пуст, значит модель не содержит дыр

	return 0;
}

