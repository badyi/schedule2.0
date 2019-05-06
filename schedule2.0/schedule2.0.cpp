#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int Weeks = 16;

class hours {
public:

	vector <int> typeof_cab;
	vector <int> typeof_sub;
	vector <int> limits_for_d;
	vector <float> limits_for_w;

	hours() {
	}

	void add(int tc, int ts, int m) {


		typeof_cab[ts] = tc;
		typeof_sub[ts] = m;

	}

	void expand_space(int k) {

		if (typeof_sub.size() == 0) {
			for (int i = 0; i < k; i++) {
				typeof_sub.push_back(-1);
				typeof_cab.push_back(-1);
				limits_for_d.push_back(1);
				limits_for_w.push_back(0);
			}
		}

		else {
			for (int i = typeof_sub.size(); i < k; i++) {

				typeof_sub.push_back(-1);
				typeof_cab.push_back(-1);
				limits_for_d.push_back(1);
				limits_for_w.push_back(0);

			}
		}
	}

	void memory_control(int k) {
		k += 1;
		if (k >= typeof_sub.size()) {
			expand_space(k);
		}
	}
};

class group {

	string name;
	int quantity;
	int LessonFlag;
	int flow;

public:

	int tempy;

	vector <int> cab;
	vector <int> sub;
	vector <int> hm_times_used_d; // day
	vector <int> hm_times_used_w; // week
	vector <int> limits_for_d;
	vector <float> limits_for_w;
	vector <bool> used;

	group(string n, int q, int f) {
		name = n;
		quantity = q;
		flow = f;
		LessonFlag = 0;
		tempy = 0;
	}

	string get_name() {
		return name;
	}
	int get_q() {
		return quantity;
	}
	int get_flow() {
		return flow;
	}
	int get_LF() {
		return LessonFlag;
	}
	void LF_change(int k) {
		LessonFlag = k;
	}

};

class cabinet {

	string number;
	int occupied;
	int checked;
	int quantity;
	int type;

public:
	cabinet(string n, int q, int t) {
		number = n;
		quantity = q;
		type = t;
		occupied = 0;
		checked = 0;
	}
	string get_number() {
		return number;
	}
	int get_q() {
		return quantity;
	}
	int get_type() {
		return type;
	}
	void change_state(int k) {
		occupied = k;
	}
	void check(int k) {
		checked = k;
	}
	int check_ornot() {
		return checked;
	}
	int state() {
		return occupied;
	}
};

vector <group*> groups;
vector <cabinet*> cabinets;
vector <char> flows;
vector <hours*> hours_flows;

void print_g() {

	for (int i = 0; i < groups.size(); i++) {
		cout << groups[i]->get_name() << "  q: " << groups[i]->get_q() << "  f: " << groups[i]->get_flow() << " lf: " << groups[i]->get_LF() << endl;
	}

}

void print_c() {
	for (int i = 0; i < cabinets.size(); i++) {
		cout << cabinets[i]->get_number() << "  q: " << cabinets[i]->get_q() << " type: " << cabinets[i]->get_type() << " check: " << cabinets[i]->check_ornot() << " state: " << cabinets[i]->state() << endl;
	}
}

int recognize_flow(string buf) {

	if (flows.size() == 0)
		flows.push_back(buf[0]);

	for (int i = 0; i < flows.size(); i++) {
		if (buf[0] == flows[i])
			return i;
	}

	flows.push_back(buf[0]);
	return recognize_flow(buf);

}

void load_groups() {

	string buf1;
	string buf2;

	int t;

	ifstream fin("groups.txt");

	while (true) {

		int k = -1;

		fin >> buf1;
		fin >> buf2;

		k = recognize_flow(buf1);
		t = atoi(buf2.c_str());

		group* G = new group(buf1, t, k);
		groups.push_back(G);

		if (fin.eof()) {
			fin.close();
			break;
		}
	}
}

void load_cab() {

	string buf1;
	string buf2;
	string buf3;

	int t, q;

	ifstream fin("cabinets.txt");

	while (true) {

		fin >> buf1;
		fin >> buf2;
		fin >> buf3;

		q = atoi(buf2.c_str());
		t = atoi(buf3.c_str());

		cabinet* C = new cabinet(buf1, q, t);
		cabinets.push_back(C);

		if (fin.eof())
			break;
	}
}

string get_typeof_class(int k) {

	switch (k)
	{
	case(0):
		return "unidentified";
	case(1):
		return "lecture";
	case (2):
		return "practice";
	case(3):
		return "lab";
	default:
		return "unidentified";
		break;
	}
}

string get_nameof_sub(int k) {

	switch (k)
	{
	case(0):
		return "Math"; // lecture
	case(1):
		return "Math"; // practice
	case(2):
		return "Xp-programming"; // lecture
	case(3):
		return "Xp-programming"; // practice
	case(4):
		return "Algebra"; // lecture
	case(5):
		return "Algebra"; // practice
	case(6):
		return "Physics"; // lecture
	case(7):
		return "Physics"; // practice
	case(8):
		return "Physics"; // lab
	default:
		return "unidentified";
		break;
	}

}

void print_hours() {

	for (int i = 0; i < hours_flows.size(); i++) {

		hours* cur = hours_flows[i];
		cout << endl << " FLOW: " << i << endl;

		for (int j = 0; j < cur->typeof_sub.size(); j++) {

			if (cur->typeof_sub[j] > 0) {
				cout << "   " << get_nameof_sub(j) << "    " << cur->typeof_sub[j] << " minutes. type:" << get_typeof_class(cur->typeof_cab[j]) << endl;
			}

		}

		cout << "-----------------";

	}

}

void load_hours() {

	string buf;
	string buf1;
	string buf2;
	string buf3;
	int fl;

	ifstream fin("hours.txt");

	fin >> buf;

	while (true) {

		if (buf[0] == '~')
			break;

		vector <string> s;

		int fl = recognize_flow(buf);

		hours* h = new hours();

		while (true) {
			fin >> buf;

			if (buf[0] == '-') {
				break;
			}

			s.push_back(buf);
		}

		while (!s.empty()) {

			buf3 = s.back();
			s.pop_back();
			buf2 = s.back();
			s.pop_back();

			h->memory_control(atoi(buf2.c_str()));
			buf1 = s.back();
			s.pop_back();
			h->add(atoi(buf1.c_str()), atoi(buf2.c_str()), atoi(buf3.c_str()));

		}

		if (hours_flows.size() != flows.size())
			for (int i = 0; i < flows.size(); i++)
				hours_flows.push_back(nullptr);


		hours_flows[fl] = h;

		fin >> buf;

	}
	fin.close();
}

void combine_groups_hours() {

	for (int i = 0; i < groups.size(); i++) {

		hours* buf = hours_flows[groups[i]->get_flow()];

		for (int j = 0; j < buf->typeof_sub.size(); j++) {

			groups[i]->cab.push_back(buf->typeof_cab[j]);
			groups[i]->sub.push_back(buf->typeof_sub[j]);
			groups[i]->hm_times_used_d.push_back(0);
			groups[i]->hm_times_used_w.push_back(0);
			groups[i]->used.push_back(false);
			groups[i]->limits_for_d.push_back(buf->limits_for_d[j]);
			groups[i]->limits_for_w.push_back(buf->limits_for_w[j]);

		}

	}
}

void set_limits() {

	for (int i = 0; i < hours_flows.size(); i++) {

		hours* cur = hours_flows[i];
		for (int j = 0; j < cur->typeof_sub.size(); j++) {

			if (cur->typeof_sub[j] > 0) {
				float limits = cur->typeof_sub[j] / 90 / 16.0;
				cur->limits_for_w[j] = limits;
			}

		}

		cout << "-----------------";

	}
}

bool flag = true;
bool flag2 = true;

void save(int lesson, group* G, cabinet* C, int S, int day, int week) {

	int type = C->get_type();

	ofstream fout("Result.txt", ios::app);
	if (flag2) {
		fout << "week: " << week << " day: " << day << "\n";
		flag2 = false;
	}
	if (flag) {

		fout << "    lesson:" << lesson << '\n';
		flag = false;
		fout << "   |      Name:|" << "quantity:|" << "flows|" << "Cabinet|" << "Type" << '\n';
	}
	fout << "    " << G->get_name() << " \t " << G->get_q() << " \t  " << G->get_flow() << " \t " << C->get_number() << " \t" << get_typeof_class(type) << "\t" << get_nameof_sub(S) << '\n';
	fout.close();


	fout.close();
}

void DELETETHISFUNC() {
	cout << endl;

	for (int i = 0; i < groups.size(); i++) {
		group* g = groups[i];
		cout << g->get_name() << " f: " << g->get_flow() << endl;
		for (int j = 0; j < g->sub.size(); j++) {
			cout << "  " << j << "  " << get_nameof_sub(j) << "     " << get_typeof_class(g->cab[j]) << "  " << g->sub[j] << endl;
		}
	}

}

void cabinets_ch_clear() {

	for (int i = 0; i < cabinets.size(); i++) {
		cabinets[i]->check(0);
	}

}

int find_sub(group* cur_g, cabinet* cur_c) {

	for (int i = 0; i < cur_g->sub.size(); i++) {
		if (cur_c->get_type() == cur_g->cab[i] && cur_g->sub[i] > 0) {

			cur_g->sub[i] = cur_g->sub[i] - 90;
			//cout << "    -----{  " << i;
			return i;

		}
	}

	return -1;
}

vector <group*> del;

void check_sub_empty() {

	bool f = true;

	for (int j = 0; j < groups.size(); j++) {

		group* current = groups[j];
		for (int i = 0; i < current->sub.size(); i++) {

			if (current->sub[i] > 0)
				f = false;

		}

		if (f)
			del.push_back(groups[j]);
	}

}

int tempy = 0;

bool check_limits(group* current, int j) {

	bool f = false;

	if (current->hm_times_used_w[j] < current->limits_for_w[j] && current->limits_for_w[j] >= 1.0) {
		f = true;
	}
	else if (current->hm_times_used_w[j] < current->limits_for_w[j] && current->limits_for_w[j] < 1.0) {

		if (current->used[j] == false) {
			f = true;
		}
	}
	return f;
}

void distribute(int Lesson, int day, int weeks) {

	for (int i = 0; i < groups.size(); i++) {

		int min = 99999;
		int g = -1;
		int c = -1;
		int s = -1;


		for (int j = 0; j < groups[i]->sub.size(); j++) {

			if (groups[i]->sub[j] > 0 && check_limits(groups[i], j)) {

				for (int k = 0; k < cabinets.size(); k++) {

					if (cabinets[k]->state() == 0 && cabinets[k]->get_type() == groups[i]->cab[j]) {

						if (groups[i]->sub[j] > 0 && groups[i]->get_LF() == 0) {

							save(Lesson, groups[i], cabinets[k], j, day, weeks);

							groups[i]->sub[j] = groups[i]->sub[j] - 90;
							groups[i]->hm_times_used_w[j] += 1;
							groups[i]->hm_times_used_d[j] += 1;
							cabinets[k]->change_state(1);
							groups[i]->LF_change(1);
							groups[i]->used[j] = true;
						}
					}
				}
			}
		}
	}

}

void delete_used_g() {

	for (int i = 0; i < del.size(); i++) {
		for (int j = 0; j < groups.size(); j++) {
			if (del.back() == groups[j]) {
				groups.erase(groups.begin() + j);
				del.pop_back();
				delete_used_g();
				break;
			}
		}
	}
}

void clean_states() {

	for (int i = 0; i < groups.size(); i++)
		groups[i]->LF_change(0);
	for (int i = 0; i < cabinets.size(); i++)
		cabinets[i]->change_state(0);

}

void distribute() {

	int Lesson = 1;
	int day = 1;
	int weeks = 0;

	while (!groups.empty()) {

		while (true) {

			//for (int i = 0; i < groups.size() ; i++)
			distribute(Lesson, day, weeks);

			clean_states();
			check_sub_empty();
			delete_used_g();

			Lesson++;
			flag = true;

			if (Lesson == 6) {
				break;
			}
		}

		Lesson = 1;
		day += 1;
		flag2 = true;

		if (day % 7 == 0) {
			if (weeks % 14 == 0)
				for (int ttt = 0; ttt < groups.size(); ttt++) {
					for (int jjj = 0; jjj < groups[ttt]->used.size(); jjj++)
						groups[ttt]->used[jjj] = false;
				}

			for (int ttt = 0; ttt < groups.size(); ttt++) {
				for (int jjj = 0; jjj < groups[ttt]->hm_times_used_w.size(); jjj++)
					groups[ttt]->hm_times_used_w[jjj] = 0;
			}

			weeks += 1;
		}
		if (day == 21) {
			break;
		}
	}

}

void print_limits() {

	cout << endl;
	for (int i = 0; i < hours_flows.size(); i++) {

		hours* cur = hours_flows[i];

		for (int j = 0; j < cur->typeof_sub.size(); j++) {

			if (cur->typeof_sub[j] > 0) {
				cout << "   " << get_nameof_sub(j) << "    " << cur->limits_for_w[j] << endl;
			}
		}

		cout << "-----------------";
	}
}

int main() {

	ofstream fout("Result.txt", ios::trunc);
	fout.close();

	load_groups();
	print_g();

	load_cab();
	cout << endl;
	print_c();

	load_hours();
	set_limits();
	//print_limits();

	cout << endl;
	print_hours();
	combine_groups_hours();

	DELETETHISFUNC();
	cout << endl;

	distribute();

	print_g();

	return 0;
}