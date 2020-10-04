#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat image1, image2, image3;

	image1 = imread("C:\\images\\lake.jpg");
	image2 = imread("C:\\images\\rain.jpg");

	if (!image1.data)
	{
		cout << "��ȡͼƬ1����" << endl;
		return-1;
	}
	if (!image2.data)
	{
		cout << "��ȡͼƬ2����" << endl;
		return-1;
	}

	resize(image2, image3, image1.size());

	namedWindow("Image 1");
	imshow("Image 1", image1);

	namedWindow("Image 3");
	imshow("Image 3", image3);

	Mat result;

	image3 = image3 * 0.3;
	image1 = image1 * 0.9;
	add(image1, image3, result);

	namedWindow("result");
	imshow("result", result);

	waitKey(0);
	return 0;

}