#include"BinaryHeap.h"
#include"Edge.h"
#include"Disjointset.h"
#include <string>
#include <fstream>
#include"FibonacciHeap.h"
class Implementation
{
private:
	string n,n1,n2,n3,n6,n7,n8;
	string str,str1;
	char getChar[20];
	int vertexNum;
	int edgeWeight;
	int firstVertex;
	int secondVertex;
	string colorstr,fontsizestr,fontcolorstr,weightstr;
	vector<Edge> finalEdge,originalEdge;
	vector<Edge>::iterator itr1,itr2;
	Disjointset D;
	Edge e1;
	BinaryHeap<Edge> edge;
	FibonacciHeap<Edge> Fibedge;
	int compEdgeWeight(int,int,int);
public:
	Implementation();
	bool inputfile(string);
	void Kruskal();
	void FibKruskal();
	void outputfile(string);
};
Implementation::Implementation()
{
	vertexNum=0;
	edgeWeight=0;
	firstVertex=0;
	secondVertex=0;
	colorstr="color=";
	fontsizestr="fontsize=10";
	fontcolorstr="fontcolor=lightgray";
	weightstr="weight=bold";
}
int Implementation::compEdgeWeight(int n1,int n2,int n3)
{
	if(n3<58&&n3>47)
		{
			edgeWeight=(n1-48)*100+(n2-48)*10+(n3-48);
			return edgeWeight;    
		}
	if(n2<58&&n2>47)
		{
			edgeWeight=(n1-48)*10+n2-48;
			return edgeWeight;	    
		}
	else
		{
			edgeWeight=n1-48;
			return edgeWeight;
		}
	return 0;
}
bool Implementation::inputfile(string filename )
{
	ifstream file (filename,std::ios::in);
	if(file.fail())
	{
		cout << "unable to open file" << endl;
		return false;
	}	
	file>>n1;
	file>>n2;
	file>>n3;	
	vertexNum=atoi(n2.c_str());	
	D.Initialize(vertexNum);
	file>>n2;
	file>>n3;
	file>>n;	
	while(n!="}")
	{
		file>>n;
		file>>n3;
		file>>n2;
		file>>n1;
		getline(file,str);
		strcpy_s(getChar,n1.c_str());
		if(n!="}")
		{			
			firstVertex=atoi(n.c_str());
			secondVertex=atoi(n2.c_str());
			
			edgeWeight=compEdgeWeight((int)getChar[7],(int)getChar[8],
				                       (int)getChar[9]);
			Edge e(firstVertex,secondVertex,edgeWeight);
			originalEdge.push_back(e);
			Fibedge.insert(e);
			edge.insert(e);		    
		}
	}
	return true;
}
void Implementation::Kruskal()
{
	while(edge.size>1)
	{
		e1=edge.deleteMin();
		
		if(D.unionSet(e1.v,e1.w))
			finalEdge.push_back(e1);
	}
}
void Implementation::FibKruskal()
{
	while(Fibedge.getsize()>1)
	{
		e1=Fibedge.extractMin()->value;
		if(D.unionSet(e1.v,e1.w))
			finalEdge.push_back(e1);
	}
}
void Implementation::outputfile(string outfileName)
{
	ofstream output(outfileName,std::ios::out);
	if(output.fail())
	{
		cout << "unable to open file" << endl;
		return ;
	}
	output<< "//" <<" "<<D.getNumber() <<" "<<  "vertices"  <<endl;
	output<<"graph"<< " " << "G" <<" "<<"{"<<endl;
	for(itr1=originalEdge.begin();itr1!=originalEdge.end();itr1++)
	{
		bool b=true;
		for(itr2=finalEdge.begin();itr2!=finalEdge.end();itr2++)
		{
			if(((*itr1).v==(*itr2).v)&&((*itr1).w==(*itr2).w)&&
				((*itr1).weight==(*itr2).weight))
			{
				output<<"   "<<(*itr2).v<<" "<<"--"<<" "<<(*itr2).w<<" "
					<<"[label="<<(*itr2).weight<<", "<<colorstr<<"indigo, "
					<<weightstr<<"];"<<endl;
				    b=false;
					break;
			}
		}
		if(b)
		{
			output<<"   "<<(*itr1).v<<" "<<"--"<<" "<<(*itr1).w<<" "
				<<"[label="<<(*itr1).weight<<", "<<colorstr<<"lightgray, "
				<<fontsizestr<<", "<<fontcolorstr<<"];"<<endl;
		}
	}
	output<<"}"<<endl;

 }