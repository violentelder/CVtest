#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
bool match(int m, int n) {
	string str1 = to_string(m);
	string str2 = to_string(n);
	int pos = str2.find(str1);
	if (pos != -1)
		return true;
	else
		return false;
}

int main() {
	int N;
	while (cin >> N) {
		vector<int> arrI;
		vector<int> arrR;
		int temp;
		for (int i = 0; i < N; i++) {
			cin >> temp;
			arrI.push_back(temp);
		}
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			arrR.push_back(temp);
		}
		sort(arrR.begin(), arrR.end());
		arrR.erase(unique(arrR.begin(), arrR.end()), arrR.end());
		int count = 0;
		vector<int> RI;
		vector<int> co;
		vector<int> index;
		vector<int> II;
		for (int i = 0; i < arrR.size(); i++) {
			int temp2 = 0, flag = 0;
			for (int j = 0; j < arrI.size(); j++) {
				if (match(arrR[i], arrI[j])) {
					temp2++;
					flag = 1;
					index.push_back(j);
					II.push_back(arrI[j]);
					count += 2;
				}
			}
			if (flag) {
				RI.push_back(arrR[i]);
				co.push_back(temp2);
				count += 2;
			}
		}
		cout << count;
		for (int i = 0; i < RI.size(); i++) {
			cout << RI[i] << co[i];
			for (int j = 0; j < index.size(); j++) {
				cout << index[j] << II[j];
			}
		}
		cout << endl;

	}
	return 0;
}