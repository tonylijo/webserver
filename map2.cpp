#include<map>
#include<iostream>
using namespace std;
int main()
{
	map<string,string> tony;
	tony["tony"] = "a";
	tony["lijo"] = "b";
	tony["jose"] = "c";
	cout << tony["abc"] << endl;
}
