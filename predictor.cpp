#ifdef _MSC_VER
#include<__msvc_all_public_headers.hpp>
#else
#include<bits/stdc++.h>
#endif
#include<windows.h>
using namespace std;
struct JsonParser{
	string json;
	void init(string data){
		json=data;
	}
	JsonParser(string data=""){
		init(data);
	}
	bool havelable(int point,string s){
		if(point+s.size()>json.size())
			return false;
		if(json.substr(point,s.size())==s)
			return true;
		return false;
	}
	int getint(int point){
		int cur=0;
		for(int i=point;i<json.size();i++){
			if(!isdigit(json[i])) break;
			cur=(cur*10)+json[i]-'0';
		}
		return cur;
	}
	string getstring(int point){
		string cur="";
		for(int i=point;i<json.size();i++){
			if(json[i]=='\"') break;
			cur=cur+json[i];
		}
		return cur;
	}
	int getintvar(int point,string s){
		for(int i=point;i<json.size();i++)
			if(havelable(i,s))
				return getint(i+s.size()+2);
		return -1;
	}
	string getstringvar(int point,string s){
		for(int i=point;i<json.size();i++)
			if(havelable(i,s))
				return getstring(i+s.size()+3);
		return "-1";
	}
};
int strtoint(string s){
	int res=0;
	for(int i=0;i<s.size();i++) res=(res*10+s[i]-'0');
	return res;
}
string inttostr(int x){
	string res="";
	if(x<0){
		res+="-";
		x=-x;
	}
	while(x){
		res+=(char)(x%10+'0');
		x/=10;
	}
	reverse(res.begin(),res.end());
	return res;
}
struct JsonScanner{
	JsonParser parser;
	string url;
	int scanner;
	void fetch(string js){
		parser.json=js;
		scanner=0;
	}
	int scangetnextintvar(string s){
		int val=parser.getintvar(scanner,s);
		if(val==-1) return -1;
		string sval=inttostr(val);
		for(int i=scanner;i<parser.json.size();i++)
			if(parser.havelable(i,s)){
				scanner=i+s.size()+2+sval.size();
				return val;
			}
		return -1;
	}
	string scangetnextstringvar(string s){
		string val=parser.getstringvar(scanner,s);
		if(val=="-1") return "-1";
		for(int i=scanner;i<parser.json.size();i++)
			if(parser.havelable(i,s)){
				scanner=i+s.size()+4+val.size();
				return val;
			}
		return "-1";
	}
}jsscan;
int get(string url,string out){
	cout<<"[GET] : "<<url<<endl;
	string command="curl --silent "+url+" -o "+out;
	int rvl=system(command.data());
	if(rvl) cout<<"[FAILED]"<<endl;
	else cout<<"[OK]"<<endl;
	return rvl;
}
void update_ratings(string cid,vector<string> handles){
	string upd;
	system("time /T > curtime.txt");
	ifstream ffin("curtime.txt");
	ffin>>upd;
	ffin.close();
	system("del curtime.txt");
	cout<<"Refreshing..."<<endl;
	string url="http://cf-predictor-frontend.herokuapp.com/GetNextRatingServlet?contestId="+cid;
	int ret=get(url,"fetchedjson"+cid+".json");
	if(ret){
		return;
	}
	string dat,line,file;
	file="fetchedjson"+cid+".json";
	ifstream fin(file.data());
	while(getline(fin,line)) dat+=line;
	fin.close();
	string ccc="del fetchedjson"+cid+".json";
	system(ccc.data());
	jsscan.fetch(dat);
	int oldr,newr,rank,delta;
	system("cls");
	cout<<"                   Last Update:"<<upd<<endl;
	cout<<"+------+------------------------+----------+----------+-----+"<<endl;
	cout<<"| RANK |       USER NAME        |OLD RATING|NEW RATING|DELTA|"<<endl;
	cout<<"+------+------------------------+----------+----------+-----+"<<endl;
	string hand,srank,soldr,snewr,sdelta;
	while(1){
		oldr=jsscan.scangetnextintvar("oldRating");
		if(oldr==-1) break;
		newr=jsscan.scangetnextintvar("newRating");
		rank=jsscan.scangetnextintvar("rank");
		hand=jsscan.scangetnextstringvar("handle");
		delta=newr-oldr;
		srank=inttostr(rank);
		soldr=inttostr(oldr);
		snewr=inttostr(newr);
		sdelta=inttostr(delta);
		if(delta>0) sdelta="+"+sdelta;
		int x;
		x=(6-srank.size())/2;
		for(int i=1;i<=x;i++) srank=" "+srank;
		while(srank.size()<6) srank+=" ";
		x=(10-soldr.size())/2;
		for(int i=1;i<=x;i++) soldr=" "+soldr;
		while(soldr.size()<10) soldr+=" ";
		x=(10-snewr.size())/2;
		for(int i=1;i<=x;i++) snewr=" "+snewr;
		while(snewr.size()<10) snewr+=" ";
		x=(5-sdelta.size())/2;
		for(int i=1;i<=x;i++) sdelta=" "+sdelta;
		while(sdelta.size()<5) sdelta+=" ";
		for(int i=0;i<handles.size();i++){
			if(handles[i]==hand){
				x=(24-hand.size())/2;
				for(int i=1;i<=x;i++) hand=" "+hand;
				while(hand.size()<24) hand+=" ";
				cout<<"|"<<srank<<"|"<<hand<<"|"<<soldr<<"|"<<snewr<<"|"<<sdelta<<"|"<<endl;
			}
		}
	}
	cout<<"+------+------------------------+----------+----------+-----+"<<endl;
}
int main(int argc,char** argv){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	vector<string> hand;
	string cc,dd;
	cc=argv[1];
	for(int i=2;i<argc;i++){
		dd=argv[i];
		hand.push_back(dd);
	}
	while(1){
		int ss=clock();
		update_ratings(cc,hand);
		ss=clock()-ss;
		Sleep(120*1000-ss);
	}
	return 0;
}


