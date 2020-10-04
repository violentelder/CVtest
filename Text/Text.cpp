#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(void)
{
	char text[30];
	cout << "输入一段英文文本：";
	cin.get(text, 30);

	int fontFace = FONT_HERSHEY_PLAIN;
	double fontScale = 2;
	int thickness = 3;

	Mat img(300, 900, CV_8UC3, Scalar::all(0));

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	//计算文字中间点
	Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);

	//绘制方盒
	rectangle(img,
		textOrg + Point(0, baseline),
		textOrg + Point(textSize.width, -textSize.height),
		Scalar(0, 0, 255));
	
	//绘制文字下划线
	line(img,
		textOrg + Point(0, thickness),
		textOrg + Point(textSize.width, thickness),
		Scalar(0, 0, 255));

	//放置文字
	putText(img,
		text,
		textOrg,
		fontFace,
		fontScale,
		Scalar::all(255),
		thickness,
		8);

	imshow("getText", img);

	waitKey(0);
	return 0;

}