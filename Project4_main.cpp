#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

template<class type>
class graph{
	private: 
		struct node{
			type data = {};
			std::vector<node*> neighbours; 
			bool isVisited; 
			node(type data_, std::vector<node*> n = {}):
			data(data_), 
			neighbours(n), 
			isVisited(false){};
		};
		//make a vector of pointers 
		std::vector<node*> v;
		//check if the current node has been visited yet 
		void topologicalCaller(node* current, std::stack<node*>& s){
			current->isVisited = true;
			for(auto i:current->neighbours)
				if(!i->isVisited)
				topologicalCaller(i,s);
			s.push(current);
		} 
	public: 
	int addVertex(type data_){
		//loop through the size of the vector
		for (size_t i = 0; i < v.size(); i++)
		{
			//if the data already exists in vector, return the index
			if(v[i]->data == data_){
				return i;
			}
			
		}
		//add a new node to the end of the vector 
		v.push_back(new node(data_));
		return ((v.size())-1);
		
		//if not added return index 
	}
	void addNeighbour(int a, int b){
		//add inta as a neighbour of intb
		v[a]->neighbours.push_back(v[b]); 
	}
	std::vector<type> topologicalSort(){
		std::stack<node*> s;
		//make all visited values false as default
		for(auto i:v)
			i->isVisited = false; 
		//if the index is not visited call the topological caller and add onto the stack 
		for(auto i:v)
			if(!i->isVisited)
				topologicalCaller(i,s);
		std::vector<type> result; 
		//add top value to stack and pop 
		while(!s.empty()){
			result.push_back(s.top()->data); s.pop();
		}
		return result;
	}
};

int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}

	std::string line;
	std::vector<std::string> record; 
	int current_file; 
	graph<std::string> g;
	
	while(std::getline(fin,line))
	{
		//push each line from the input file into the record
		record.push_back(line);
	}
	int current;
	for (int i=0; i<record.size(); i++){
		//check if the line does not have a hashtag
		if (record[i].find("#") == -1){ 
			//add a vertex with the current line string
			 current = g.addVertex(record[i]);

		}
		else {
			//parse the lines with #include statements to extract only the file name 
			//first find the substring past the '<' bracket
			int position = record[i].find("<");
			std::string sub = record[i].substr(position + 1);
			//remove the last character which would contain the closing bracket '>'
			sub.pop_back();
			//add vertex with substring 
			int current2 = g.addVertex(sub);
			//add the substring as a neighbour to our vertex without a hashtag
			g.addNeighbour(current2, current);

		}
	}

	//call the topological sort on our graph and print
	std::vector<std::string> output = g.topologicalSort();
		for(auto data:output)
			std::cout<<data<<std::endl;
	return EXIT_SUCCESS;
}