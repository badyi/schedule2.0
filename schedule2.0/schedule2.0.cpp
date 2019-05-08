#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int Weeks = 16; //Warning. before change ordinary value(16), calculate all details

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

}; //  //class for 

class group {

private:

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
	vector <int> used;

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
private:
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

class flow : public group {

	using group::group;

};

vector<flow*> FLOWS;
vector <group*> groups;
vector <cabinet*> cabinets;
vector <char> flows;
vector <hours*> hours_flows;

void print_g() { // print groups

	cout << "---------------Groups----------------\n" << endl;

	for (int i = 0; i < groups.size(); i++) {
		cout << groups[i]->get_name() << "  q: " << groups[i]->get_q() << "  f: " << groups[i]->get_flow() << " lf: " << groups[i]->get_LF() << endl;
	}

}

void print_c() { //print cabinets

	cout << endl << "---------------Cabinets---------------\n" << endl;

	for (int i = 0; i < cabinets.size(); i++) {
		cout << cabinets[i]->get_number() << "  q: " << cabinets[i]->get_q() << " type: " << cabinets[i]->get_type() << " check: " << cabinets[i]->check_ornot() << " state: " << cabinets[i]->state() << endl;
	}

	cout << endl;
}

int recognize_flow(string buf) { // defines flows

	if (flows.size() == 0)
		flows.push_back(buf[0]);

	for (int i = 0; i < flows.size(); i++) {
		if (buf[0] == flows[i])
			return i;
	}

	flows.push_back(buf[0]);
	return recognize_flow(buf);

}

void load_groups() { // load groups from txt file "groups.txt"

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
		cout << '.';
		if (fin.eof()) {
			fin.close();
			break;
		}
	}

	cout << " Groups loaded" << endl << endl;
}

void load_cab() { // load data about cabinets from txt file "cabinets"

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

string get_typeof_class(int k) { //returns <string> name of type of cabinet or subject

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

string get_nameof_sub(int k) { // returns <string> name of subject

	switch (k)
	{
	case(0):
		return "Math"; // lecture
	case(1):
		return "Math"; // practice
	case(2):
		return "Algebra"; // lecture
	case(3):
		return "Algebra"; // practice
	case(4):
		return "Xp-programming"; // lecture
	case(5):
		return "Xp-programming"; // practice
	case(6):
		return "Physics"; // lecture
	case(7):
		return "Physics"; // practice
	case(8):
		return "Physics"; // lab
	case(9):
		return "Foreign language"; // practice
	case(10):
		return "Physical education"; // practice
	case(11):
		return "Programming"; // lecture
	case(12):
		return "Programming"; // practice
	case(13):
		return "Programming"; // lab
	case(14):
		return "Math logic"; // lecture
	case(15):
		return "Math logic"; // practice
	case(16):
		return "Math logic"; // lab
	case(17):
		return "discrete math"; // lecture
	case(18):
		return "discrete math"; // practice
	case(19):
		return "Economics"; // lecture
	case(20):
		return "Economics"; // practice
	case(21):
		return "Computer System Organization"; // lecture
	case(22):
		return "Computer System Organization"; // prectice
	default:
		return "unidentified";
		break;
	}

}

void print_hours() { //~

	cout << "\n" << "--------------------Hours-----------------" << "\n";
	for (int i = 0; i < hours_flows.size(); i++) {

		hours* cur = hours_flows[i];
		cout << endl << " flow: " << i << endl;

		for (int j = 0; j < cur->typeof_sub.size(); j++) {

			if (cur->typeof_sub[j] > 0) {
				cout << "   " << get_nameof_sub(j) << "    " << cur->typeof_sub[j] << " minutes. type:" << get_typeof_class(cur->typeof_cab[j]) << endl;
			}

		}

		cout << "-----------------";

	}

}

void load_hours() { // load data about hours for each flow from txt file "heours.txt"

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
			cout << '.';
		}

		if (hours_flows.size() != flows.size())
			for (int i = 0; i < flows.size(); i++)
				hours_flows.push_back(nullptr);


		hours_flows[fl] = h;

		fin >> buf;

	}
	cout << " hours loaded" << endl;
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
			groups[i]->limits_for_d.push_back(buf->limits_for_d[j]);
			groups[i]->limits_for_w.push_back(buf->limits_for_w[j]);

			if (buf->limits_for_w[j] < 1.0 && buf->limits_for_w[j] > 0.0) {
				float t = 1;
				float us = buf->limits_for_w[j];

				while (us * t != 1.0) {
					t++;
					if (t > 16) {
						t = 4;
						break;
					}
				}
				groups[i]->used.push_back(t);
			}
			else if (buf->limits_for_w[j] >= 1.0)
				groups[i]->used.push_back(buf->limits_for_w[j]);
			else
				groups[i]->used.push_back(0);
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
				cout << '.';
			}

		}

	}
	cout << " limits set" << endl;
}

bool flag = true;
bool flag2 = true;
bool flag3 = true;

void save(int lesson, group* G, cabinet* C, int S, int day, int week) {

	int type = C->get_type();

	ofstream fout("Result.txt", ios::app);
	if (flag3) {
		fout << "\nWeek: " << week << "\n";
		flag3 = false;
	}
	if (flag2) {
		fout << endl << "   day: " << day << "\n\n";
		flag2 = false;
		fout << "   |        Name:|" << "  quantity:|" << "  flows|" << "  Cabinet|" << "Type" << '\n';
	}
	if (flag) {

		fout << "    ---------------------------------------Lesson: " << lesson << " -----------------------------------------" << '\n';
		flag = false;

	}

	fout << "    " << G->get_name() << "     \t " << G->get_q() << " \t  " << G->get_flow() << " \t " << C->get_number() << " \t" << get_typeof_class(type) << "\t" << get_nameof_sub(S) << '\n';
	fout.close();


	fout.close();
}

void print_hours_of_each_g() {

	cout << endl << endl;
	cout << "------------Hours of each group-------------" << endl << endl;

	for (int i = 0; i < groups.size(); i++) {

		group* g = groups[i];

		cout << g->get_name() << " flow: " << g->get_flow() << endl;

		for (int j = 0; j < g->sub.size(); j++) {
			cout << "  " << j << "  " << get_nameof_sub(j) << "     " << get_typeof_class(g->cab[j]) << "  " << g->sub[j] << endl;
		}

	}

}

void cabinets_ch_clear() {  // clear states of each cabinet

	for (int i = 0; i < cabinets.size(); i++) {
		cabinets[i]->check(0);
	}

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

bool check_limits(group* current, int j, int week) {

	bool f = false;

	if (current->hm_times_used_w[j] < current->limits_for_w[j] && current->limits_for_w[j] >= 1.0) {
		f = true;
	}

	else if (current->hm_times_used_w[j] < current->limits_for_w[j] && current->limits_for_w[j] < 1.0) {
		if (current->used[j] > 0 && current->hm_times_used_d[j] < current->limits_for_w[j])
			if (week % current->used[j] == 0.0) {
				f = true;
			}
	}
	return f;
}

void distr_lecture(group* current, int j, int Lesson, int day, int week) { //distribute only lectures cause its special case. we have to check that groups isnt already used <at this lesson> and check state of cabinet and compear capacity and quatity. 
																								// then if all checks passed we have to diminish hours of that subject

	bool Flag = true;
	flow* f = FLOWS[current->get_flow()];

	for (int y = 0; y < groups.size(); y++) {

		if (groups[y]->get_flow() == current->get_flow()) {

			if (groups[y]->get_LF() == 1) {
				Flag = false;
				break;
			}

			if (!(groups[y]->hm_times_used_w[j] < groups[y]->limits_for_w[j])) {
				Flag = false;
				break;
			}

			if (groups[y]->hm_times_used_d[j] == 1) {
				Flag = false;
				break;

			}

		}

	}


	if (Flag)

		for (int k = 0; k < cabinets.size(); k++) {

			if (cabinets[k]->state() == 0 && cabinets[k]->get_type() == current->cab[j] && cabinets[k]->get_q() - f->get_q() >= 0) {
				if (current->sub[j] > 0 && current->get_LF() == 0) {

					save(Lesson, f, cabinets[k], j, day, week);

					for (int y = 0; y < groups.size(); y++) {
						if (groups[y]->get_flow() == current->get_flow())
						{

							groups[y]->sub[j] = current->sub[j] - 90;
							groups[y]->hm_times_used_w[j] += 1;
							groups[y]->hm_times_used_d[j] += 1;
							groups[y]->LF_change(1);

						}

					}
					cabinets[k]->change_state(1);

				}
			}
		}
}

void distribute(int Lesson, int day, int week) {

	for (int i = 0; i < groups.size(); i++) {

		int min = 99999;
		int g = -1;
		int c = -1;
		int s = -1;


		for (int j = 0; j < groups[i]->sub.size(); j++) {

			if (groups[i]->sub[j] > 0 && check_limits(groups[i], j, week)) {

				if (groups[i]->cab[j] == 1) {

					distr_lecture(groups[i], j, Lesson, day, week);

				}

				else
					for (int k = 0; k < cabinets.size(); k++) {

						if (cabinets[k]->state() == 0 && cabinets[k]->get_type() == groups[i]->cab[j] && cabinets[k]->get_q() - groups[i]->get_q() >= 0) {

							if (groups[i]->sub[j] > 0 && groups[i]->get_LF() == 0) {

								save(Lesson, groups[i], cabinets[k], j, day, week);

								groups[i]->sub[j] = groups[i]->sub[j] - 90;
								groups[i]->hm_times_used_w[j] += 1;
								groups[i]->hm_times_used_d[j] += 1;
								cabinets[k]->change_state(1);
								groups[i]->LF_change(1);
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

			for (int ttt = 0; ttt < groups.size(); ttt++) {
				for (int jjj = 0; jjj < groups[ttt]->hm_times_used_w.size(); jjj++)
					groups[ttt]->hm_times_used_w[jjj] = 0;
			}

			weeks += 1;
			flag3 = true;
		}
		if (day == 121) {
			break;
		}
	}

}

void print_limits() {
	cout << "\n----------Limits(<...> times a weeK)----------" << "\n\n";
	for (int i = 0; i < hours_flows.size(); i++) {

		hours* cur = hours_flows[i];

		cout << "flow-" << i << endl;

		for (int j = 0; j < cur->typeof_sub.size(); j++) {
			if (cur->typeof_sub[j] > 0) {
				cout << "   " << get_nameof_sub(j) << "    " << cur->limits_for_w[j] << "  " << get_typeof_class(cur->typeof_cab[j]) << endl;
			}
		}

	}
}

void sum_flows() { //summarize

	for (int i = 0; i < flows.size(); i++) {
		int q = 0;
		for (int j = 0; j < groups.size(); j++) {
			if (groups[j]->get_flow() == i) {
				q += groups[j]->get_q();
			}
		}

		flow* f = new flow("flow - " + to_string(i), q, i);
		FLOWS.push_back(f);
	}

}

int main() {

	ofstream fout("Result.txt", ios::trunc);
	fout.close();

	load_groups();

	print_g();

	load_cab();

	print_c();

	sum_flows();

	load_hours();

	set_limits();

	print_limits();

	print_hours();

	combine_groups_hours();

	print_hours_of_each_g();

	/*for (int i = 0; i < groups.size(); i++) {
		for (int j = 0; j < groups[i]->used.size(); j++) {
			cout<<"{" << groups[i]->used[j] << "}" << endl;
		}
	}*/

	distribute();

	return 0;
}