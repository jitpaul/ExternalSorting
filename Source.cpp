#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include  <string>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;



void sort(vector<int>& tempArray) {
	sort(tempArray.begin(), tempArray.end());
}



class Compare {
public:
	bool operator()(const pair<ifstream*, int> &a, const pair<ifstream*, int> &b) {
		return a.second > b.second;
	}
};



void merge_Files(vector<string>& fileNames, string output_file_path) {
	ofstream out_file(output_file_path);
	string t;
	vector<ifstream*> files;
	for (string tp : fileNames)
		files.push_back(new ifstream(tp));
	priority_queue<pair<ifstream*,int>, vector<pair<ifstream*, int>>, Compare> q;
	for (int i = 0; i < files.size(); i++) {
		if(getline(*files[i],t,' '))
		    q.emplace(files[i],stoi(t));
	}
	while (!q.empty()) {
		pair<ifstream*, int> tp = q.top(); q.pop();
		out_file << tp.second << " ";
		if (getline(*tp.first, t, ' '))
			q.emplace(tp.first, stoi(t));
	}
	for (ifstream* tp : files)
		delete tp;
	for (string tp : fileNames)
		remove(tp.c_str());
}



void externalSort(string input_file_path, string output_file_path, int size = 10000) {
	fstream input_file(input_file_path, ios::in);
	if (!input_file.is_open()) {
		cout << "File could not be opened" << endl; return;
	}
	string tp;
	vector<string> tempFiles;
	vector<int> tempArray;
	int count = 1;
	while (getline(input_file, tp, ' ')) {		
		tempArray.push_back(stoi(tp));
		if (tempArray.size() == size) {
			sort(tempArray);
			string name = to_string(count++);
			fstream temp(name, ios::out);
			for (int tp : tempArray)
				temp << tp << " ";
			tempFiles.push_back(name);
			tempArray.clear();
		}
	}
	if (tempArray.size() != 0) {
		sort(tempArray);
		string name = to_string(count++);
		fstream temp(name, ios::out);
		for (int tp : tempArray)
			temp << tp << " ";
		tempFiles.push_back(name);
	}
	merge_Files(tempFiles, output_file_path);
}



int main() {
	string inputFile, outputFile;
	cin >> inputFile;cin >> outputFile;
	fstream newFile(inputFile, ios::out);
	srand(time(nullptr));
	for (int i = 0; i < 100000; i++)
		newFile << rand()%10000<< " ";
	newFile.close();
	externalSort(inputFile, outputFile);
	cin.get();
	return 0;
}