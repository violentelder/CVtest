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
	//开放以避免隐式转换
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

	//写入
	{
		cout << endl << "写入开始：" << endl;
		Mat R = Mat_<uchar>::eye(3, 3),
			T = Mat_<double>::zeros(3, 1);
		Mydata m(1)
			;

		FileStorage fs(filename, FileStorage::WRITE);

		fs << "iterationNr" << 100;

		//字符串开始
		fs << "strings" << "[";
		fs << "C:\\images\\lake.jpg" << "Awesomeness"
			<< "C:\\images\\baboon.jpg";
		//字符串结束
		fs << "]";

		//字符串匹配（mapping）
		fs << "mapping";
		fs << "{" << "one" << 1;
		fs << "Two" << 2 << "}";

		//CV::MAT
		fs << "R" << R;
		fs << "T" << T;

		//数据结构
		fs << "Mydata" << m;

		//释放fs内存
		fs.release();
		cout << "写入完成" << endl;

	}

	//读取
	{
		cout << endl << "读取开始：" << endl;
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

		//读取字符串并获得节点
		FileNode n = fs["strings"];
		if (n.type() != FileNode::SEQ)
		{
			cerr << "错误，字符串不是循序的！" << endl;
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

		//读取自己的数据结构
		fs["Mydata"] >> m;

		cout << endl
			<< "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "Mydata = " << endl << m << endl << endl;

		//对不存在的节点显示基本特性
		cout << "尝试读取不存在的";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
	}

	cout << endl
		<< "提醒：请使用文本编辑器打开存储的文件" << filename << endl;

	getchar();

	waitKey(0);
	return 0;

}
