#include <iostream>
#include <fstream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "GrayRatio.h"
#include "cmdline.h"
#include "common.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cerr << "This is a cmdline tool to change image to html or character graph" << endl;
	}
	cmdline::parser cmd;
	cmd.add<string>("source", 's', "the name of the photo", true, "");
	cmd.add<int>("scalex", 'x', "the column size of the photo", true, 1);
	cmd.add<int>("scaley", 'y', "the row size of the photo", true, 1);
	cmd.add<int>("type", 't', "the desired form of the photo", true, 0);
	cmd.add<int>("color", 'c', "the color of the html output", 0, 0);
	cmd.add<string>("output", 'o', "the output path", false, "output.txt");

	cmd.parse_check(argc, argv);
	string source = cmd.get<string>("source");
	int scalex = cmd.get<int>("scalex");
	int scaley = cmd.get<int>("scaley");
	int type = cmd.get<int>("type");
	int color = cmd.get<int>("color");
	string output = cmd.get<string>("output");

	//Prepare for the next steps.

	auto Original = ReadFile(source);
	PixelBlockSize pbs;
	pbs.Row = scaley; pbs.Col = scalex;
	auto r = CalcPixelBlockAverageRGB(Original, pbs);
	if (type == 0)
	{
		ofstream ofs(output);
		if (ofs.is_open())
		{
			ofs << ToText(r);
			ofs.close();
		}
	}
	else if (type == 1)
	{
		cout << ToText(r);
	}
    return 0;
}
