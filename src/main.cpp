#include <iostream>
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
		cerr << "This is a cmdline tool to change image to html or character graph.Usage:$ > . / image2text --source[source.jpg] --scale x : y --type[html / txt] --with - color(only type is html) --output[target.html(txt)].Or that use $ > . / image2text --help to see a detailed usage. " << endl<<"version"<< VERSION_NUM << endl;
	}
	cmdline::parser cmd;
	cmd.add<string>("source", 's', "the name of the photo", true, "");
	cmd.add<int>("scale x", 'x', "the column size of the photo", true, 1);
	cmd.add<int>("scale y", 'y', "the row size of the photo", true, 1);
	cmd.add<string>("type", 't', "the desired form of the photo", 0, "");
	cmd.add<string>("color", 'c', "the color of the html output", 0, "");
	cmd.parse_check(argc, argv);

	string source = cmd.get<string>("source");
	int scalex = cmd.get<int>("scale x");
	int scaley = cmd.get<int>("scale y");
	string type = cmd.get<string>("type");
	string color = cmd.get<string>("color");

	//Prepare for the next steps.

	auto Original = ReadFile(source);

	PixelBlockSize pbs;

	pbs.Row = scaley; pbs.Col = scalex;

	auto r = CalcPixelBlockAverageRGB(Original, pbs);

	ToText(r);

	//imshow("pyt", Original);

	waitKey(0);

	cin.get();

	return 0;
    return 0;
}
