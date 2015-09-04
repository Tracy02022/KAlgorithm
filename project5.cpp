// project5.cpp : Defines the entry point for the console application.
//Dongyu Li

#include "stdafx.h"
#include"Implementation.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Implementation image;
	cout<<"Enter the input file name"<<endl;
	string filename;
	cin>>filename;
	if(image.inputfile(filename))
	{
	cout<<"Want another heap to implement the MST. Y/N"<<endl;
	char n;
	cin>>n;
	if(n=='y'||n=='Y')
	{
		image.FibKruskal();
		cout<<"Enter the output file name(FibonacciHeap)"<<endl;
		cin>>filename;
		image.outputfile(filename);
		return 0;
	}
	else
	{
		image.Kruskal();
		cout<<"Enter the output file name"<<endl;
		cin>>filename;
		image.outputfile(filename);
		return 0;
	}
	}
}

