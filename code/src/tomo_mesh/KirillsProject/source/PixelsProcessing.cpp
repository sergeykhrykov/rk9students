// STL includes
#include <iostream>
#include <string>

#include <conio.h>
#include <fstream>

// DCMTK includes
#include "dcmtk/config/osconfig.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcpxitem.h"
#include "dcmtk/dcmdata/dctagkey.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimage/diregist.h"
#include "dcmtk/dcmimgle/dcmimage.h"

// Boost includes
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[]) { // �������� ������� ���������

	Uint16 rows;
	Uint16 columns;

	int image_num = 0; //���������� �������

	bool first_file = true; // ������� ����� ����������� true, ��������� - false
	bool second_file = false;
	ofstream DataPixels("DataPixels.txt");

	for (fs::recursive_directory_iterator it(argv[1]), end; it != end;
		it++) { // ��������� ������ �� ���� ������ �����������
				// ���� ������ ����, ��

		DcmFileFormat fileformat;
		string name_of_file;
		name_of_file =
			it->path().string(); //� ���� ��������� name_of_file ��� ����������

		OFCondition status = fileformat.loadFile(
			name_of_file.c_str()); // ���������, ���������� �� ����

		if (first_file) {
			first_file = false;
			second_file = true;

			if (status.good()) {

				if (fileformat.getDataset()->findAndGetUint16(DCM_Rows, rows).good()) {
					std::cout << "Rows: " << "image" << rows << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_Columns, columns)
					.good()) {
					std::cout << "Columns: " << columns << endl;
				}
			}
		}

			// ���������� pixel data, ������ �� ������:
			// http://forum.dcmtk.org/viewtopic.php?f=1&t=4001

			unsigned long numByte = 0; // ���������� ���

									   // short* pixelData = NULL; // ������� ������ pixel data
			DicomImage *img = new DicomImage(name_of_file.c_str());

			if (img->getStatus() == EIS_Normal) // ���������, ��������� ��
			{
				const DiPixel *inter =
					img->getInterData(); // ��������� ���������� ������
				if (inter != NULL) {
					numByte = inter->getCount(); // ������� ���������� ���

					short *raw_pixel_data = (short *)inter->getData();
					if (raw_pixel_data == nullptr) { // ���� ��������� ������ - ������
						std::cout << "Couldn't acces pixel data!\n";
						return (1);
					}

					vector<short> pixel_data(
						raw_pixel_data,
						raw_pixel_data + rows * columns); // ������ �������� � pixel data,
														  // ��� ������ �������� � �������
														  // - ��������� �� ������ �������
														  // �������, � ������ �������� -
														  // �� ��������� ������� �������
					vector<vector<short>> slice;
					for (int i = 0; i < rows; i++) {
						slice.resize(slice.size() + 1);
						slice[i].resize(columns);
						for (int j = 0; j < columns; j++) {
							slice[i][j] = pixel_data[i*columns + j];
							DataPixels << slice[i][j] << " ";
						}
					}

					image_num++;
				}
			}
		}
	DataPixels.close();
	std::cout << "Images was processed: " << image_num <<"\n";
	getch();
	return 0;
	} /*
	  if (!first_file && second_file) {
	  if (fileformat.getDataset()
	  ->findAndGetFloat64(DCM_SliceLocation,
	  sliceLocation2)
	  .good()) {
	  cout << "Slice Location from the second
	  image: " << sliceLocation2 << endl;
	  sliceLocation = sliceLocation2 -
	  sliceLocation1;
	  cout << "Real Slice Location: " <<
	  sliceLocation << endl;
	  }
	  second_file = false;
	  }*/