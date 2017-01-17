#include<iostream>
#include<fstream>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

int makeNum(string s)
{
	unsigned int num=0,count=0;
	while(count<s.size())
	{
		if(isdigit(s[count]))
			num = num + (s[count]-48)*(int)(pow(10,s.size()-count-1));
		else
			return -1;  	
		
		count++;	
	}
	return num;
}

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
		cout<<"\n";
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
		cout<<"\n";
	}
	
	else if(argc == 3)
	{	

		int readRate = makeNum(argv[1]);
		int outRate = makeNum(argv[2]);				

		if(readRate == -1 || outRate == -1)
			{
				cout<<"Entered value is not an integer\n";
				return 0;		
			}	
		while(1)
		{
			
			ifstream fp;
			string s1;
			string remove,name;
			float x=0,userMode=0,systemMode=0,idleMode=0,totalTime=0,memTotal=0,memFree=0,avgMem=0,processCreateRate=0,contextSwitRate=0,processDiff=0,contextSwitDiff=0;
			float reads=0,writes=0;				
			int time=0,k=0,i=0;
			
			int processes[100]={0},contextSwitches[100]={0};
			
			fp.open("/proc/meminfo",ios::in);
			fp>>remove;	//remove the name from the stream
			fp>>memTotal;
			fp.close();	
						
			while(time<outRate)
			{
				//Percentage of time in idle, system, and user Mode also the context switches and rate of process creation			
				fp.open("/proc/stat",ios::in);
				fp>>remove; //remove the name cpu from the stream			
				fp>>x;
				userMode += x;
				totalTime += x;

				fp>>x;totalTime += x;
				fp>>x;totalTime += x;
			
				systemMode+=x;
				fp>>x;
				idleMode+=x;
				totalTime += x;
			
				fp>>x;totalTime += x;
				fp>>x;totalTime += x;
				fp>>x;totalTime += x;
				fp>>x;totalTime += x;
				fp>>x;totalTime += x;
				fp>>x;totalTime += x;					
				
				getline(fp,remove);
				getline(fp,remove);				
				getline(fp,remove);
				getline(fp,remove);
				getline(fp,remove);
				getline(fp,remove);
				
				fp>>remove; //remove the word 'ctxt'
				
				fp>>contextSwitches[k];

				getline(fp,remove); //remove two lines from the stream
				getline(fp,remove);
			
				fp>>remove; //remove the word 'processes'

				fp>>processes[k]; 

				fp.close();
				
				//amount and percentage of free memeory in system
				fp.open("/proc/meminfo",ios::in);
				
				getline(fp,remove);	//remove the first line from the stream
				fp>>remove;		//remove the name MemFree from the stream
				fp>>x;
				memFree+=x;

				fp.close();
				
				//Rate of disk read and write in the system
				fp.open("/proc/diskstats",ios::in);				
				while(!fp.eof())
				{
					fp>>remove>>remove>>name; //remove the first 2 values from the stream
					if(name == "sda")
						break;	
					else
						getline(fp,remove);	// if the not sda the remove the whole line from the stream
				}	
		
				fp>>x;
				reads += x;
				fp>>x>>x>>x>>x;
				writes += x;
				fp.close();

				k++;				
				sleep(readRate);							
				time+=readRate;
		
			}
			cout<<"\n";
			avgMem = memFree/(outRate/readRate);
			for(i=1;i<k;i++)
			{
				contextSwitDiff += contextSwitches[i] - contextSwitches[i-1];
				processDiff += processes[i] - processes[i-1];
		
			}
				
			processCreateRate = processDiff/(outRate/readRate);
			contextSwitRate = contextSwitDiff/(outRate/readRate);

			cout<<"The percentage of time the computer is in User Mode: "<<(userMode/totalTime)*100<<"%"<<endl;						
			cout<<"The percentage of time the computer is in System Mode: "<<(systemMode/totalTime)*100<<"%"<<endl;						
			cout<<"The percentage of time the computer is in Idle Mode: "<<(idleMode/totalTime)*100<<"%"<<endl;			
			printf("The amount of average free memory in the system:  %.1f kB\n",avgMem);
			cout<<"The percentage of free memory in the system:  "<<(avgMem/memTotal)*100<<"%"<<endl;
			printf("The rate of disk read is: %0.1f blocks\n",(reads/(outRate/readRate)));			
			printf("The rate of disk write is: %0.1f blocks	\n",(writes/(outRate/readRate)));				
			printf("The rate of context switches in kernel: %.1f \n",contextSwitRate);
			printf("The rate of process creation is: %f\n",processCreateRate);	
				
		}			
	}	

 return 0;
}
