#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	char* imageName = "C:\\images\\lena.jpg";

	Mat image = imread(imageName, 1);

	Mat gray_image;

	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	imwrite("C:\\images\\process\\lena.jpg", gray_image);

	namedWindow("Color Image", WINDOW_AUTOSIZE);
	namedWindow("Gray Image", WINDOW_AUTOSIZE);

	imshow("Color Image", image);
	imshow("Gray Image", gray_image);

	waitKey(0);
	return 0;

}