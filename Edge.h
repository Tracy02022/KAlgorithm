//Dongyu Li
//store the edge information
class Edge
{
public:
	
	int v,w,weight;
	bool operator < (Edge &);
	Edge():v(0),w(0),weight(0){}
	Edge(int firstVertex,int secondVertex,int edgeWeight)
	{
		v=firstVertex;
		w=secondVertex;
		weight=edgeWeight;
	}
};

bool Edge:: operator < ( Edge & e)
{
	if(this->weight<e.weight)
		return true;
	else
		return false;
}