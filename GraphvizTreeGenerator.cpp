#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[])
{
	string s;
	int n, i = 0, j = 0;
	
	cout << "graph g {" << endl;
	
	while (getline(cin, s))
	{
		istringstream iss(s);
		j = 0;
		
		while(iss >> n)
		{
			if (n != -1)
				cout << "\t" << i << " -- " << j << " [label=" << n << "];" << endl;
			++j;
		}
		
		++i;
	}
	
	cout << "}" << endl;

	return 0;
}