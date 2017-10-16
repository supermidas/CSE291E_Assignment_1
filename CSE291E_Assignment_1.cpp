#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class clause
{
	public:
		short len;
		short lit[10];          //literals
		bool lit_pol[10];       //literal polarities. 0 for neg, 1 for pos.
};

class Solver
{
	public:
		clause cla[30000];
		short cla_num;
		short var_num;
		bool assignment[2000];       //assignment to the literals

		void assign(int n)
		{
			for(int i = 0; i < var_num; i++)
			{
				 //assignment[i] = n % 2;
				 //n /= 2;
				assignment[i] = rand() % 2;
				//cout << assignment[i] << ' ';
			}
			//cout << endl;
		};

		bool if_SAT()
		{
			for(int i = 0; i < cla_num; i++)
			{
				bool if_cla_sat = 0;
				for(int j = 0; j < cla[i].len; j++)
				{
					if((cla[i].lit_pol[j] && assignment[cla[i].lit[j]-1]) ||  (!cla[i].lit_pol[j] && !assignment[cla[i].lit[j]-1]))
					{
						if_cla_sat = 1;
						break;
					}
				}
				//cout << if_cla_sat << ' ';
				if(!if_cla_sat)
				{
					//cout << endl;
					return 0;
				}
			}
			//cout << endl;
			return 1;
		};
};

int main()
{
	Solver sol;
	srand((unsigned int)time(0));
	//Readin all the clauses
	fstream fin("unif-k5-r21.117-v390-c8236-S7412914535193118493.cnf");     //can handle different CNFs
	string str;
	while(getline(fin,str))
	{
		if(str[0] != 'c')
			break;
	}
	int variable_num = 0;
	int clause_num = 0;
	bool if_clause_num = 0;
	for(int i = 6; i < str.length(); i++)
	{
		if(str[i] == ' ')
		{
			if_clause_num = 1;
			continue;
		}
		if(!if_clause_num)
		{
			variable_num *= 10;
			variable_num += str[i] - '0';
		}
		else
		{
			clause_num *= 10;
			clause_num += str[i] - '0';
		}
	}
	sol.var_num = variable_num;
	sol.cla_num = clause_num;
	//cout << variable_num << endl << clause_num << endl;
	
	int cur_cla_num = 0, cur_lit_num = 0;
	while(fin >> str)
	{
		if(str != "0")
		{
			int cur_lit = 0;
			if(str[0] == '-')
			{
				sol.cla[cur_cla_num].lit_pol[cur_lit_num] = 0;
			}
			else
			{
				sol.cla[cur_cla_num].lit_pol[cur_lit_num] = 1;
			}
			for(int i = 0; i < str.length();i++)
			{
				if(str[i] == '-')
					continue;
				cur_lit *= 10;
				cur_lit += str[i] - '0';
			}
			sol.cla[cur_cla_num].lit[cur_lit_num] = cur_lit;
			cur_lit_num++;
		}
		else
		{
			sol.cla[cur_cla_num].len = cur_lit_num;
			cur_lit_num = 0;
			cur_cla_num++;
		}
	}
	/*for(int i = 0; i < cur_cla_num; i++)
	{
		for(int j = 0; j < sol.cla[i].len; j++)
		{
			cout << sol.cla[i].lit[j] << ' ';
		}
		cout << endl;
	}*/
	fin.close();

	int assign_num = 0;
	bool if_sat = 0;
	//cout << pow(2.0,variable_num) << endl;
	clock_t start,end;  
	start = clock();
	while(assign_num < pow(2.0,variable_num))
	{
		sol.assign(assign_num);
		if(sol.if_SAT())
		{
			if_sat = 1;
			cout << "sat" << endl;
			for(int i = 0; i < variable_num; i++)
			{
				cout << sol.assignment[i] << ' ';
			}
			cout << endl;
			break;
		}
		end = clock();
		if(end - start >= 10000)
		{
			break;
		}
		assign_num++;
	}
	//cout << assign_num << endl;

	if(!if_sat)
	{
		if(assign_num == (int)(pow(2.0,variable_num)))
		{
			cout << "unsat" << endl;
		}
		else 
		{
			cout << "unknown" << endl;
			//cout << assign_num << endl;
			cout << "the # of assignment have been explored / total # of assignments = " << 1.0 * assign_num / pow(2.0,variable_num) << endl;
		}
	}
	system("pause");
	return 0;
}