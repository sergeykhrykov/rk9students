#include <iostream>
#include <vector>

#include "common/PolyModel.h"
#include "ModelEdges.h"

using namespace std;
using namespace rk9;

int main(int argc, char* argv[])
{
	PolyModel model;
	
	model.ReadFromSTLFile(argv[1]);      //���������� ������ STL �� �����

	ModelEdges edges;					     //������� ����� ���� ������

	auto hl = edges.FindErrors(model);			 //���� ������  hl �������� �����, �� ���� ������ ����; ���� ����, ������ ������ �� �������� ���

	return 0;
}

