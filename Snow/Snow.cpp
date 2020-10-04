#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	argv[1] = "C:\\images\\\lena.jpg";
	Mat image;

	image = imread(argv[1], IMREAD_COLOR);
	if (!image.data)
	{
		cout << "无法打开" << std::endl;
		return -1;
	}

	namedWindow("原图",WINDOW_NORMAL);
	namedWindow("下雪图", WINDOW_NORMAL);

	imshow("原图", image);
	

	int n = 70;
	for (int k = 0; k < n; k++)
	{
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1)
		{ 
			//gray-level image
			image.at<uchar>(j, i) = 255;
			if (i < (int)image.cols)
				image.at<uchar>(j + 1, i) = 255;
			if (j < (int)image.rows)
				image.at<uchar>(j , i + 1) = 255;
			if (i < (int)image.cols && j < (int)image.rows)
				image.at<uchar>(j + 1, i +1) = 255;
		}

		else if (image.channels() == 3)
		{
			//color image
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
			if (i < (int)image.cols - 1)
			{
				image.at<cv::Vec3b>(j, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j, i + 1)[2] = 255;
			}

			if (i < (int)image.rows - 1)
			{
				image.at<cv::Vec3b>(j + 1, i)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i)[2] = 255;	
			}

			if (i < (int)image.cols - 1 && i < (int)image.rows - 1)
			{
				image.at<cv::Vec3b>(j + 1, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[2] = 255;
			}

		}

	}

	imshow("下雪图", image);
	waitKey(0);

	return 0;

}