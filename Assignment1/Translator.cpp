#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
	ofstream outfile;
	ifstream infile;
	int pushl=0,movl=0;
	infile.open("bit32.asm");
	outfile.open("bit64.asm");
	string readLine;
	int line=0;
	while(getline(infile,readLine)){
		int flag=0;
		if(pushl==2 && readLine.find("pushl")!=string::npos){
			flag=1;
			outfile<<"	movl	%esi, -24(%rbp)";
			pushl=3;
		}
		if(pushl==1 && readLine.find("pushl")!=string::npos){
			flag=1;
			outfile<<"	movl	%edi, -20(%rbp)";
			pushl=2;
		}
		if(readLine.find("addl")!=string::npos){
			flag=1;
			outfile<<readLine;
		}	
		if(readLine.find("pushl")!=string::npos && pushl==0){
			flag=1;
			pushl=1;
			int l=readLine.length();
			for(int i=0;i<l;i++){
				if(readLine[i]=='l')readLine[i]='q';
				else if(readLine[i]=='e')readLine[i]='r';
			}
			outfile<<readLine;
		}
		if(movl==3 && readLine.find("movl")!=string::npos){
			flag=1;
			int l=readLine.length();
			for(int i=0;i<l;i++){
				if(readLine[i]=='e' && readLine[i+2]=='p')readLine[i]='r';
			}
			outfile<<readLine;
		}
		if(movl==2 && readLine.find("movl")!=string::npos){
			flag=1;
			movl=3;
			outfile<<"	movl	-24(%rbp), %ecx";
		}
		if(movl==1 && readLine.find("movl")!=string::npos){
			flag=1;
			movl=2;
			outfile<<"	movl	-20(%rbp), %ebx";
		}
		if(movl==0 && readLine.find("movl")!=string::npos){
			flag=1;
			movl=1;
			int l=readLine.length();
			for(int i=0;i<l;i++){
				if(readLine[i]=='l')readLine[i]='q';
				else if(readLine[i]=='e')readLine[i]='r';
			}
			outfile<<readLine;
		}
		if(readLine.find("popl")!=string::npos){
			flag=1;
			int l=readLine.length();
			for(int i=0;i<l;i++){
				if(readLine[i]=='l')readLine[i]='q';
				else if(readLine[i]=='e')readLine[i]='r';
			}
			outfile<<readLine;
		}
		if(!flag)outfile<<readLine;
		outfile<<endl;
	}
	
	outfile.close();
	infile.close();
	return  0;
}
