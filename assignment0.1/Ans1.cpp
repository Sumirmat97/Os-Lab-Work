#include<iostream>
#include<fstream>
#include<strings.h>

using namespace std;

int main(int argc,char *argv[])
{
	if(argc == 2)
	{
		cout<<"Number of inputs is incorrect"<<endl;	
	}

	if(argc > 3)
	{
		cout<<"Number of inputs given is more than expected\n";
		return 0;
	}

	if(argc == 1)
	{
		cout<<endl;
		ifstream fp;
		string s1;
		int pos,count=0,time=0,hours=0,min=0;
		
		fp.open("/proc/cpuinfo",ios::in);
		while(count++<=4)
		{
			getline(fp,s1);
		}
		pos = s1.find(':');
		s1 = s1.substr(pos+2);
		cout<<"Processor type: "<<s1<<endl;
		fp.close();

		fp.open("/proc/version",ios::in);
	
		getline(fp,s1);
		pos = s1.find('(');
		s1.erase(s1.begin()+pos,s1.end());
		cout<<"Kernel version: "<<s1<<endl;
		fp.close();


		fp.open("/proc/meminfo",ios::in);
		getline(fp,s1);
		pos = s1.find(':');
		s1 = s1.substr(pos+7);
		cout<<"Amount of memory in system: "<<s1<<endl;
		fp.close();

		fp.open("/proc/uptime");
		fp>>time;
		min = time/60;
		hours = min/60;
		if(hours)
		{
			min = min/60;
			cout<<"Amount of time since last boot: "<<hours<<" hour "<<min<<" min"<<endl;
		}
		else
			cout<<"Amount of time since last boot: "<<min<<" min"<<endl;
		
	}
	
	else if(argc == 3)
	{
				
	}

 return 0;
}
