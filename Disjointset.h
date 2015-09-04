//Dongyu Li
#pragma once 
#include<vector>
using namespace std;
class Disjointset
{
private:
	int num;
	vector<int> vec;
public:
	Disjointset():num(0){}
	Disjointset(int numElement)
	{
		num=numElement;
	}
	int find(int);
	bool unionSet(int,int);
	void Initialize(int );	
	int getNumber()const;
	
};
void Disjointset::Initialize(int n)
{
	num=n;
	
	for(int i=0;i<n;i++)
	{
		vec.push_back(-1);
	}
}
//given two roots of two sets, joins them to set
bool Disjointset::unionSet(int elem1,int elem2)
{
	int root1=find(elem1);
	int root2=find(elem2);
	if(root1==root2)
		return false ;
	else
	{
		vec[root2]=root1;
		return true;
	}
}
//return the root of the set 
int Disjointset::find(int element)
{
	if(vec[element]==-1)
		return element;
	else
		return find(vec[element]);
}
//return the total number of vertices
int Disjointset::getNumber() const
{
	return num;
}