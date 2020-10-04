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

	//����ͼƬ��С
	int m = getOptimalDFTSize(img.rows);
	int n = getOptimalDFTSize(img.cols);

	//��ͼ��߿�0ֵ
	copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;

	//ʹ��0���ӵ�����һ��������
	merge(planes, 2, complexI);

	//�������С��ԭͼ�Ǻ�
	dft(complexI, complexI);

	//��������ֵ�������ɶ����Ŀ̶�
	split(complexI, planes);

	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];
	
	//�����ɶ����Ŀ̶�
	magI += Scalar::all(1);
	log(magI, magI);

	//���Ÿ���Ҷͼ������������
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;

	//���Ϻ����¶Ե�
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//���Ϻ����¶Ե�
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//�Ը���ֵ��0��1֮�䣩ת��ͼ�񵽿ɼ���ͼ
	normalize(magI, magI, 0, 1, NORM_MINMAX);

	//show the result
	imshow("Input Image", img);
	imshow("spectrum magnitude", magI);

	waitKey(0);
	return 0;

}