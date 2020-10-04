#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace cv;
using namespace std;

class Mydata
{
public:
	int A;
	double X;
	string id;

	Mydata() :A(0), X(0), id()
	{}
	//�����Ա�����ʽת��
	explicit Mydata(int) : A(97), X(CV_PI), id("mydata1234")
	{}

	void write(FileStorage& fs) const
	{
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}

	void read(const FileNode& node)
	{
		A = (int)node["A"];
		X = (double)node["X"];
		id = (String)node["id"];
	}

};

static void write(FileStorage& fs, const std::string&, const Mydata& x)
{
	x.write(fs);
}

static void read(const FileNode& node, Mydata& x,
	const Mydata& default_value = Mydata())
{
	if (node.empty())
		x = default_value;
	else
		x.read(node);
}

static ostream& operator<<(ostream& out, const Mydata& m)
{
	out << "{ id = " << m.id << ",";
	out << "X = " << m.X << ",";
	out << "A = " << m.A << "}";
	return out;
}

int main(int ac, char** av)
{
	string filename = "C:\\images\\outputfile.yml";

	//д��
	{
		cout << endl << "д�뿪ʼ��" << endl;
		Mat R = Mat_<uchar>::eye(3, 3),
			T = Mat_<double>::zeros(3, 1);
		Mydata m(1)
			;

		FileStorage fs(filename, FileStorage::WRITE);

		fs << "iterationNr" << 100;

		//�ַ�����ʼ
		fs << "strings" << "[";
		fs << "C:\\images\\lake.jpg" << "Awesomeness"
			<< "C:\\images\\baboon.jpg";
		//�ַ�������
		fs << "]";

		//�ַ���ƥ�䣨mapping��
		fs << "mapping";
		fs << "{" << "one" << 1;
		fs << "Two" << 2 << "}";

		//CV::MAT
		fs << "R" << R;
		fs << "T" << T;

		//���ݽṹ
		fs << "Mydata" << m;

		//�ͷ�fs�ڴ�
		fs.release();
		cout << "д�����" << endl;

	}

	//��ȡ
	{
		cout << endl << "��ȡ��ʼ��" << endl;
		FileStorage fs;
		fs.open(filename, FileStorage::READ);
		
		int itNr;
		itNr = (int)fs["iterationNr"];
		cout << itNr << endl;
		if (!fs.isOpened())
		{
			cerr << "Failed to open" << filename << endl;
			return 1;

		}

		//��ȡ�ַ�������ýڵ�
		FileNode n = fs["strings"];
		if (n.type() != FileNode::SEQ)
		{
			cerr << "�����ַ�������ѭ��ģ�" << endl;
			return 1;
		}

		//go through the node
		FileNodeIterator it = n.begin(), it_end = n.end();
		for (; it != it_end; it++)
			cout << (string)*it << endl;

		Mydata m;
		Mat R, T;

		//Read cv::Mat
		fs["R"] >> R;
		fs["T"] >> T;

		//��ȡ�Լ������ݽṹ
		fs["Mydata"] >> m;

		cout << endl
			<< "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "Mydata = " << endl << m << endl << endl;

		//�Բ����ڵĽڵ���ʾ��������
		cout << "���Զ�ȡ�����ڵ�";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
	}

	cout << endl
		<< "���ѣ���ʹ���ı��༭���򿪴洢���ļ�" << filename << endl;

	getchar();

	waitKey(0);
	return 0;

}
