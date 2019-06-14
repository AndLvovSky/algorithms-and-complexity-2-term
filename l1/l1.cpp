#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

// â íàçâàõ ï³äðîçä³ë³â òà ³ìåíàõ ïðàö³âíèê³â
// äîçâîëåí³ ëèøå ìàëåíüê³ ë³òåðè ëàòèíñüêîãî
// àëôàâ³òó òà öèôðè
const int PRIME = 41,
 		  DIV_SIZE = 15,
		  EMP_SIZE = 30;

// ï³äðîçä³ë êîìïàí³¿
struct CompanyDivision {
	string name;
	vector <string> employees;
};

// ôóíêö³ÿ äëÿ îá÷èñëåííÿ ÷èñëîâîãî ïðåäñòàâëåííÿ ðÿäêà
uint hashCode(string s) {
	uint hc = 0, pow = 1;
	for (int i = 0; i < s.size(); i++) {
		hc += s[i] * pow;
		pow *= PRIME;
	}
	return hc;
}

// ñïèñîê ï³äðîçä³ë³â êîìïàí³¿
vector <CompanyDivision> compDivs;
// ìàñèâè ñïèñê³â, äå ³íäåêñîì â ìàñèâ³ º õåø
// â îäíîìó ñïèñêó çáåð³ãàþòüñÿ åëåìåíòè ç îäíàêîâèì õåøåì 
vector <string> compDivH[DIV_SIZE], empH[EMP_SIZE], empDivH[EMP_SIZE];

void read() {
	int divN;
	cin >> divN;
	for (int i = 0; i < divN; i++) {
		CompanyDivision compDiv;
		cin >> compDiv.name;
		int empNum;
		cin >> empNum;
		for (int i = 0; i < empNum; i++) {
			string empName;
			cin >> empName;
			compDiv.employees.push_back(empName);
		}
		compDivs.push_back(compDiv);
	}
}

// îá÷èñëåííÿ õåø³â äëÿ íàçâ ï³äðîçä³ë³â,
// ³ìåí ïðàö³âíèê³â òà ïàð <ïðàö³âíèê><ï³äðîçä³ë>
void makeHash() {
	for (auto compDiv: compDivs) {
		int dhc = hashCode(compDiv.name) % DIV_SIZE;
		compDivH[dhc].push_back(compDiv.name);
		for (auto emp: compDiv.employees) {
			int ehc = hashCode(emp) % EMP_SIZE;
			empH[ehc].push_back(emp);
			string ed = emp + compDiv.name;
			int edhc = hashCode(ed) % EMP_SIZE;
			empDivH[edhc].push_back(ed);
		}
	}
}

// âèâåäåííÿ îá÷èñëåíèõ õåø³â
void showHashStructure() {
	cout << "Company divisions structure:" << endl;
	cout << "{hash | are elements}: {[company divisions]}" << endl;
	for (int i = 0; i < DIV_SIZE; i++) {
		if (!compDivH[i].empty()) {
			cout << i << ":";
			for (auto divName: compDivH[i]) {
				cout << "- " << divName;
			}
			cout << endl;
		}
	}
	cout << "Employees structure:" << endl;
	cout << "{hash | are elements}: {[employees]}" << endl;
	for (int i = 0; i < EMP_SIZE; i++) {
		if (!empH[i].empty()) {
			cout << i << ":";
			for (auto emp: empH[i]) {
				cout << " -" << emp;
			}
			cout << endl;
		}
	}
	cout << "Employee's work structure:" << endl;
	cout << "{hash | are elements}: {[employee + company divisions]}" << endl;
	for (int i = 0; i < EMP_SIZE; i++) {
		if (!empDivH[i].empty()) {
			cout << i << ":";
			for (auto ed: empDivH[i]) {
				cout << " -" << ed;
			}
			cout << endl;
		}
	}
}

void runRequestInterface() {
	char op = ' ';
	while (op != '4') {
		cout << "Choose request:" << endl;
		cout << "1 - the employee exists" << endl;
		cout << "2 - the company division exists" << endl;
		cout << "3 - the employee works for the company division" << endl;
		cout << "4 - exit" << endl;
		cin >> op;
		switch (op) {
			case '1' : {
				string reqEmp;
				cout << "Empoyee name: ";
				cin >> reqEmp; 
				int ehc = hashCode(reqEmp) % EMP_SIZE;
				bool flag = false;
				if (!empH[ehc].empty()) {
					for (auto emp: empH[ehc]) {
						if (emp == reqEmp) {
							cout << "Yes" << endl;
							flag = true;
							break;
						}
					}
				}
				if (!flag) {
					cout << "No" << endl;	
				}
				break;
			}
			case '2' : {
				string reqDiv;
				cout << "Company division name: ";
				cin >> reqDiv;
				int dhc = hashCode(reqDiv) % DIV_SIZE;
				bool flag = false;
				if (!compDivH[dhc].empty()) {
					for (auto div: compDivH[dhc]) {
						if (div == reqDiv) {
							cout << "Yes" << endl;
							flag = true;
							break;
						}
					}
				}
				if (!flag) {
					cout << "No" << endl;	
				} 
				break;
			}
			case '3' : {
				string reqEmp, reqDiv, reqED;
				cout << "Empoyee name: ";
				cin >> reqEmp; 
				cout << "Company division name: ";
				cin >> reqDiv;
				reqED = reqEmp + reqDiv;
				int edhc = hashCode(reqED) % EMP_SIZE;
				bool flag = false;
				if (!empDivH[edhc].empty()) {
					for (auto ed: empDivH[edhc]) {
						if (ed == reqED) {
							int dhc = hashCode(reqDiv) % DIV_SIZE;
							bool flag2 = false;
							for (auto div: compDivH[dhc]) {
								if (div == reqDiv) {
									flag2 = true;
									break;
								}
							}
							if (!flag2) continue;
							flag2 = false;
							int ehc = hashCode(reqEmp) % EMP_SIZE;
							for (auto emp: empH[ehc]) {
								if (emp == reqEmp) {
									flag2 = true;
									break;
								}
							}
							cout << "Yes" << endl;
							flag = true;
							break;
						}
					}
				}
				if (!flag) {
					cout << "No" << endl;	
				}
				break;
			}
			case '4' : {
				break;
			}
		}
	}
}

int main() {
	read();
	makeHash();
	showHashStructure();
	runRequestInterface();
}
