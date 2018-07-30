#include <iostream>
#include "common/PolyModel.h"

using namespace rk9;

int main(int argc, char* argv[])
{
	
	PolyModel model_a, model_b;

	// A simple usage example:
	// Read a model from file,
	// Add one more triangle,
	// then write the model 
	// to another file.

	model_a.ReadFromSTLFile(argv[1]);

	for (size_t i = 0; i < model_a.GetTrianglesCount(); ++i) {
		auto t = model_a.GetTriangleVertices(i);
		t.A.X += 300; // translate points in X direction
		t.B.X += 300;
		t.C.X += 300;
		model_b.AddTriangle(t);
	}

	PolyModel* res = PolyModel::MergeModels(model_a, model_b);

	res->WriteToSTLFile("output.stl");

	return 0;
}
