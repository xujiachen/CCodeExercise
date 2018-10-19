#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> letterCombinations(string digits) {
	vector<string> R;
	if (digits.empty()) return R;
	string a[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	int n = digits.size();
	vector<int> v(n, 0);

	string S = "";
	for (int i = 0; i < n; i++) {
		S += a[digits[i] - '0' - 2][0];
	}

	while (true) {
		R.push_back(S);
		int j = n - 1;
		v[j]++;
		while (j > 0 && v[j] == a[digits[j] - '0' - 2].size()) {
			v[j] = 0;
			S[j] = a[digits[j] - '0' - 2][0];
			v[--j]++;
		}

		if (v[0] == a[digits[0] - '0' - 2].size()) break;
		else S[0] = a[digits[0] - '0' - 2][v[0]];

		S[j] = a[digits[j] - '0' - 2][v[j]];
	}
	return R;
}

int main() {
	string s;
	getline(cin, s);
	vector<string> v = letterCombinations(s);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	return 0;
}

