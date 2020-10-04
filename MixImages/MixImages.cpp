#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	double alpha, beta, input;
	Mat src1, src2, dst;

	loop1:cout << "简易线性混合" << endl;
	cout << "---------------------" << endl;
	cout << "*输入 0 到 1 之间的alpha值：";
	cin >> input;

	if (input >= 0 && input <= 1)
		alpha = input;
	else
	{
		cout << "Input Error" << endl;
		cout << "Please Input Again" << endl;
		cout << endl;
		goto loop1;
	}

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

	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	imshow("Linear Blend", dst);

	waitKey(0);
	return 0;
		
}