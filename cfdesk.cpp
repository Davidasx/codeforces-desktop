#ifdef _MSC_VER
#include<__msvc_all_public_headers.hpp>
#else
#include<bits/stdc++.h>
#endif
#include<conio.h>
using namespace std;
string ver="0.1.0";
string build_time="August 29th,2021 10:07 UTC+8:00";
string codeforces="https://codeforces.com";
vector<pair<string,string> > events;
int get(string url,string out){
	cout<<"[GET] : "<<url<<endl;
	string command="curl --silent "+url+" -o "+out;
	int rvl=system(command.data());
	if(rvl) cout<<"[FAILED]"<<endl;
	else cout<<"[OK]"<<endl;
	return rvl;
}
void viewproblem();
void opencontest();
void downloadgym();
void submit_code();
void addschedule();
void cfpredictor();
void printevents(string ss);
void welcome(){
	system("cls");
	system("time /t > curtime.txt");
	ifstream fin("curtime.txt");
	string ss;
	fin>>ss;
	fin.close();
	system("del curtime.txt");
	string systime="Current Time is "+ss+".";
	cout<<"+------------------------------------+"<<endl;
	cout<<"|Welcome to Codeforces Desktop "<<ver<<".|"<<endl;
	cout<<"|       "<<systime<<"       |"<<endl;
	printevents(ss);
	cout<<"+--+---------------------------------+"<<endl;
	cout<<"|1 | View a problem.                 |"<<endl;
	cout<<"|2 | Open a contest.                 |"<<endl;
	cout<<"|3 | Download a gym attachement.     |"<<endl;
	cout<<"|4 | Submit(requires cf-tool).       |"<<endl;
	cout<<"|5 | Schedule an event.              |"<<endl;
	cout<<"|6 | Predict contest ratings.        |"<<endl;
	cout<<"|7 | About this tool.                |"<<endl;
	cout<<"|0 | Exit.                           |"<<endl;
	cout<<"+--+---------------------------------+"<<endl;
	int x;
	x=getch();
	x-='0';
	if(x==1) viewproblem();
	if(x==2) opencontest();
	if(x==3) downloadgym();
	if(x==4) submit_code();
	if(x==5) addschedule();
	if(x==6) cfpredictor();
	if(x==7){
		cout<<"Codeforces Desktop "<<ver<<"."<<endl;
		cout<<"Built at "<<build_time<<"."<<endl;
		system("pause");
	}
	if(x==0){cout<<"Exit."<<endl;exit(0);}
}
void viewproblem(){
	cout<<"Please enter problem ID(e.g.123A etc.):"<<flush;
	string id;
	cin>>id;
	string contest,problem;
	if(isdigit(id[id.size()-1])){
		problem=id.substr(id.size()-2,2);
		contest=id.substr(0,id.size()-2);
	}
	else{
		problem=id.substr(id.size()-1,1);
		contest=id.substr(0,id.size()-1);
	}
	string command="start "+codeforces+"/contest/"+contest+"/problem/"+problem;
	system(command.data());
}
void opencontest(){
	cout<<"Contest ID(e.g.1561):"<<flush;
	string id;
	cin>>id;
	string command="start "+codeforces+"/contest/"+id;
	system(command.data());
	cout<<"Do you want to run `cf race`[Y/n]?"<<endl;
	int xx=getch();
	if(xx=='y'||xx=='Y'){
		string cc="cf race "+id;
		system(cc.data());
		system("pause");
	}
}
void downloadgym(){
	cout<<"Gym ID:"<<flush;
	string id;
	cin>>id;
	cout<<"Save to:"<<flush;
	string file;
	cin>>file;
	int xx=get(codeforces+"/gym/"+id+"/attachments","gyminfo.txt");
	if(xx){system("pause");return;}
	ifstream fin("gyminfo.txt");
	string line;
	string target="<a href=\"/gym/"+id+"/attachments/download/";
	while(getline(fin,line)){
		if(line.size()<target.size()) continue;
		if(line.substr(0,target.size())==target){
			string url=codeforces;
			url+=line.substr(9);
			for(int i=0;i<url.size()-3;i++){
				if(url[i]=='.'&&url[i+1]=='p'&&url[i+2]=='d'&&url[i+3]=='f'){
					url=url.substr(0,i+4);
					break;
				}
			}
			int xx=get(url,file);
			if(!xx){
				cout<<"Saved PDF to "<<file<<"."<<endl;
				string cmd="start "+file;
				system(cmd.data());
			}
			break;
		}
	}
	fin.close();
	system("del gyminfo.txt");
	system("pause");
}
void submit_code(){
	cout<<"Select type:"<<endl;
	cout<<"  0) Submit file."<<endl;
	cout<<"  1) Submit code."<<endl;
	int x=getch();
	if(x=='0'){
		string pid,file;
		cout<<"Problem(e.g.123A,gym100001A):"<<flush;
		cin>>pid;
		cout<<"File(e.g.123A):"<<flush;
		cin>>file;
		string command="cf submit -f "+file+" "+pid;
		system(command.data());
		system("pause");
		return;
	}
	if(x=='1'){
		string pid;
		cout<<"Problem(e.g.123A,gym100001A):"<<flush;
		cin>>pid;
		cout<<"Paste your code into the notepad."<<endl;
		cout<<"Then save and exit."<<endl;
		system("notepad submission.cpp");
		string command="cf submit -f submission.cpp "+pid;
		system(command.data());
		system("del submission.cpp");
		system("pause");
		return;
	}
}
void addschedule(){
	string tim,even;
	cout<<"Time:"<<flush;cin>>tim;
	cout<<"Event:"<<flush;getline(cin,even);getline(cin,even);
	events.push_back(make_pair(tim,even));
	cout<<"Scheduled "<<even<<" at time "<<tim<<"."<<endl;
	cout<<"There will be a notice when the time comes."<<endl;
	system("pause");
}
void printevents(string time){
	sort(events.begin(),events.end());
	while(events.size()&&events[0].first<=time){
		string ev=events[0].second;
		if(ev.size()>22){
			ev=ev.substr(0,10)+"..."+ev.substr(ev.size()-9);
		}
		string notice="Notice: Event "+ev;
		int add=(36-(int)(notice.size()))/2;
		for(int i=0;i<add;i++) notice+=" ";
		while(notice.size()<36)
			notice=" "+notice;
		cout<<"|"<<notice<<"|"<<endl;
		events.erase(events.begin());
	}
}
void cfpredictor(){
	cout<<"Contest ID:"<<flush;
	string cid;
	cin>>cid;
	int num;
	cout<<"Number of handles:"<<flush;cin>>num;
	cout<<"Target handles(one per line):"<<endl;
	string name;
	string command="start predictor "+cid;
	while(num--){
		cin>>name;
		command+=" ";
		command+=name;
	}
	cout<<"A new window will auto-refresh every 2 minutes."<<endl;
	cout<<"Close that window to stop."<<endl;
	system(command.data());
	system("pause");
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	while(1) welcome();
	return 0;
}


