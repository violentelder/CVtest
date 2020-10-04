#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

Mat src1;
Mat src2;
Mat dst;

static void on_treckbar(int, void*)
{
	alpha = (double)alpha_slider / alpha_slider_max;
	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);
}

int main(void)
{
	src1 = imread("C:\\images\\LinuxLogo.jpg");
	src2 = imread("C:\\images\\WindowsLogo.jpg");
	if (!src1.data)
	{
		cout << "读取图片1错误" << endl;
		return-1;
	}
	if (!src2.data)
	{
		cout << "读取图片2错误" << endl;
		return-1;
	}

	//起始值
	alpha_slider = 0;

	//建立窗口

	int a = 100;
	namedWindow("Linear Blend", 1);
	imshow("Linear Blend", src2);
	char TrackbarName[50];
	sprintf_s(TrackbarName, "Alpha  %d", alpha_slider_max);

	//产生滑块回复函数
	createTrackbar(TrackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_treckbar);

	waitKey(0);
	return 0;


}