
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
using namespace std;

int n = 0;
int k = 0;

class vectors_magazine {

public:
	vector <string> name;
	vector <int> value;
	vector <char> sequence;
	vectors_magazine(string a) {
		name.push_back(a);
	}
	void sequence_vectors(char c) {
		sequence.push_back(c);
	}
	void value_vectors(int d) {
		value.push_back(d);
	}
};
vector <vectors_magazine> vectorsss;

class vertices {
public:
	int nr_seq;
	int position;
	int id;
	bool end_seq = 0;
	string window;
	string deletion;

	vertices() {}
	void add_nr(int a) {
		nr_seq = a;
	}
	void add_posi(int b) {
		position = b;
	}
	void add_id(int c) {
		id = c;
	}
	void add_window(string d) {
		window = d;
	}
	void add_deletion(string e) {
		deletion = e;
	}
	void add_end(bool f) {
		end_seq = f;
	}

};
vector<vertices>graph;

class theme {

public:
	vector <string> local;
	vector <int> sequence;
	vector <int> position_end;
	vector <int>  position;
	theme() {}
	void add_theme(string a) {
		local.push_back(a);
	}
	void add_position(int b) {
		position.push_back(b);
	}
	void add_end(int c) {
		position_end.push_back(c);
	}
	void add_seq(int d) {
		sequence.push_back(d);
	}

};
vector<theme>metoda;

void write() {

	string line;
	ifstream file;
	char character;
	int number;
	int i = 0;
	file.open("plik1.txt", std::ios::in);
	if (file.good() == false)
		cout << "Unable to open first file!" << endl;
	else {
		while (file.good()) {
			getline(file, line);
			vectors_magazine *objekt = new vectors_magazine(line);
			file >> character;
			while (character != '>') {
				objekt->sequence_vectors(character);
				file >> character;
				if (character == '>' || character == ';') break;
			}
			vectorsss.push_back(*objekt);
			if (character == ';')
				break;
		}
		cout << " First file successfully loaded:! " << endl;
		file.close();
	}

	file.open("plik2.txt", std::ios::in);
	if (file.good() == false)
		cout << "Unable to open second file!" << endl;
	else {
		getline(file, line);
		while (file.good()) {
			file >> number;
			while (number != 0) {
				vectorsss[i].value_vectors(number);
				file >> number;
				if (number == 0)
					break;
			}
			getline(file, line);
			getline(file, line);
			i++;
		}
		cout << "Second file successfully loaded:!" << endl;
		file.close();
	}
}

void creating_vertices() {

	int counter;
	int help_me;
	int a;

	string deletion;
	string seq;
	for (int i = 0; i < vectorsss.size(); i++) {
		for (int j = 0; j <= vectorsss[i].sequence.size() - n; j++) {
			counter = 0;
			help_me = j;
			a = 1;
			seq = "\0";
			deletion = "\0";
			vertices *obiekt = new vertices;
			obiekt->add_nr(i);
			obiekt->add_posi(j);
			while (counter < n) {
				seq += vectorsss[i].sequence[help_me];

				if (vectorsss[i].value[help_me] < k && a != 0) {
					if (n == 4 || n == 5) {
						deletion += "?";
						a = 0;
					}
					if (n == 6 || n == 7) {
						deletion += "?";
						a++;
					}
				}
				else
					deletion += vectorsss[i].sequence[help_me];
				if (a == 2)
					a = 0;
				help_me++;
				counter++;
			}
			obiekt->add_window(seq);
			obiekt->add_deletion(deletion);
			graph.push_back(*obiekt);
		}
		
	}

	int temp = 0;

	for (int i = 0; i < 7; i++) {
		temp += vectorsss[i].sequence.size() - n;
		graph[temp].add_end(1);
	}


	for (int i = 0; i < graph.size(); i++)
		graph[i].add_id(i);

}

void graph_matrix(bool **macierz) {

	char seq1[8];
	char seq2[8];
	int counter;
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			if (graph[i].window == graph[j].window)
				macierz[i][j] = 1;
		}
	}
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			counter = 0;
			strcpy_s(seq1, graph[i].deletion.c_str());
			strcpy_s(seq2, graph[j].deletion.c_str());
			for (int z = 0; z < n; z++) {
				if (seq1[z] == seq2[z])
					counter++;
				if (seq1[z] == '?')
					counter++;
				if (seq2[z] == '?')
					counter++;
			}
			if (counter == n)
				macierz[i][j] = 1;
		}
	}
}

void kliki(bool **macierz) {

	vector<int>id;
	bool visited[7];
	int counter = 1;
	int iteration = 1;
	int y;
	bool h = 0;
	int temp = 0;
	int helper;
	for (int i = 0; i < 7; i++)
		visited[i] = 0;

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			if (macierz[i][j] == 1) {
				if (visited[graph[j].nr_seq] != 1) {
					if (graph[j].end_seq != 1) {
						id.push_back(j);
						visited[graph[j].nr_seq] = 1;
					}
				}
			}
			if (id.size() == 4) {
				theme *obiekt = new theme;
				for (int k = 0; k < id.size(); k++) {
					obiekt->add_position(graph[id[k]].position);
					obiekt->add_seq(graph[id[k]].nr_seq);
				}
				while (id.size() == 4) {
					obiekt->add_theme(graph[id[0] + iteration].window);
					y = id[0];

					counter = 0;
					h = 0;
					for (int g = 0; g < id.size(); g++) {
						if (id[g] + iteration > graph.size()-1) {
							h = 1;
							break;
						}
						if (i + iteration > graph.size()-1) {
							h = 1; 
							break;
						}
					}
					if (h == 1) break;

					for (int g = 0; g < id.size(); g++) {
						if (graph[i + iteration].end_seq == 1) {
							h = 1;
						}
						if (graph[id[g] + iteration].end_seq == 1)
							h = 1;
					}
					for (int x = 0; x < id.size(); x++) {
						if (macierz[i + iteration][id[x] + iteration] == 1) {
							counter++;
						}
					}
					if (counter == 4) {
						for (int g = 0; g < id.size(); g++) {
							if (graph[i + iteration].end_seq == 1) {
								h = 1;
							}
							if (graph[id[g] + iteration].end_seq == 1)
								h = 1;
						}

						if (h == 1)
							obiekt->add_theme(graph[id[0] + iteration].window);
						iteration++;
						counter = 0;


					}
					else break;

					if (h == 1) break;

				}
				iteration--;
				for (int k = 0; k < id.size(); k++)
					obiekt->add_end(graph[id[k]].position + n + iteration - 1);
				id.erase(id.begin(), id.end());
				metoda.push_back(*obiekt);
				for (int t = 0; t < 7; t++)
					visited[t] = 0;
				counter = 1;
				iteration = 1;
				if (metoda.size() == 1) {
					temp = 1;
				}
				else if (metoda[0].local.size() >= metoda[1].local.size()) {
					metoda.pop_back();
				}
				else
					metoda.erase(metoda.begin() + 0);

			}
		}

		for (int t = 0; t < 7; t++)
			visited[t] = 0;
		id.erase(id.begin(), id.end());
	}
}



int main()
{
	write();
	for (int i = 0; i < vectorsss.size(); i++)
		cout << vectorsss[i].sequence.size() << "\t" << vectorsss[i].value.size() << endl;
	cout << "Enter the window size:" << endl;
	cin >> n;
	while (n < 4 || n>7)
		cin >> n;
	cout << "Enter the lowest nucleotide value: " << endl;
	cin >> k;
	creating_vertices();
	bool **macierz = new bool*[graph.size()];
	for (int i = 0; i < graph.size(); i++)
	{
		macierz[i] = new bool[graph.size()];
		for (int j = 0; j < graph.size(); j++)
		{
			macierz[i][j] = 0;
		}
	}
	cout << endl;
	int temp = 0;
	graph_matrix(macierz);
	kliki(macierz);

	for (int i = 0; i < metoda.size(); i++) {
		cout << "Sequence number: " << endl;
		for (int j = 0; j < metoda[i].position.size(); j++) {
			cout << metoda[i].sequence[j] + 1 << ", ";
			cout << "Start: " << metoda[i].position[j] + 1 << ", ";
			cout << "End: " << metoda[i].position_end[j] + 1 << endl;
			cout << "Sequence:";
			for (int c = metoda[i].position[j]; c <= metoda[i].position_end[j]; c++) {
				cout << vectorsss[metoda[i].sequence[j]].sequence[c];
			}
			cout << endl;
		}
		cout << "Size: " << metoda[i].position_end[0] - metoda[i].position[0] + 1 << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}

	system("pause");

}