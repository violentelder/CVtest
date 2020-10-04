#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	const char* filename = "C:\\images\\lake.jpg";
	Mat img = imread(filename, IMREAD_GRAYSCALE);
	if (img.empty())
		return -1;
	Mat padded;

	//扩张图片大小
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols);

	//在图像边框补0值
	copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;

	//使用0增加到另外一个扩增面
	merge(planes, 2, complexI);

	//将结果大小与原图吻合
	dft(complexI, complexI);

	//计算扩增值并更换成对数的刻度
	split(complexI, planes);

	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];
	
	//更换成对数的刻度
	magI += Scalar::all(1);
	log(magI, magI);

	//安排傅里叶图的四象限区块
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;

	//左上和右下对调
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//右上和左下对调
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//以浮点值（0到1之间）转换图像到可见的图
	normalize(magI, magI, 0, 1, NORM_MINMAX);

	//show the result
	imshow("Input Image", img);
	imshow("spectrum magnitude", magI);

	waitKey(0);
	return 0;

}