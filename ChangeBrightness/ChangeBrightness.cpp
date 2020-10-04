#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


double alpha;			//对比度控制
int beta;				//明亮度控制

int main(int argc, char** argv)
{

	Mat image = imread("C:\\images\\lena.jpg");
	if (!image.data)
	{
		cout << "无法打开" << std::endl;
		return -1;
	}

	Mat new_image = Mat::zeros(image.size(), image.type());

	//初始化参数设置
	loop1:cout << " 基本线性变换 " << endl;
	cout << "-------------------------- " << endl;
	cout << " * 输入alpha值[1.0 - 3.0] :" ;
	cin >> alpha;
	cout << " * 输入beta值[0 - 100] :";
	cin >> beta;

	if ((alpha > 3.0 || alpha < 1.0) || (beta > 100 || beta < 0))
	{
		cout << "Input Error" << endl;
		cout << "Please Input Again" << endl;
		cout << endl;
		goto loop1;

	}

	//转换公式 new_image（i, j） = alpha * image(i, j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				//对每个像素做转换
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
			}

		}

	}

	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	imshow("Original Image", image);
	imshow("New Image", new_image);

	waitKey(0);

	return 0;
}

