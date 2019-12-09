/*
 * Logan Stuchlik & Jordan Welch
 * Project 3 - Planar Graphs and Algorithms
 * Cosc 320
 * Pretend We started before Novemeber 30th in the year 2019
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <iomanip>
enum color_t {WHITE, BLACK, GRAY};
class Graph
{
  private:
    std::vector<color_t> VertColo;
    std::vector<int> VertDist;
    std::vector<int> VertPare;
    std::map<int, std::vector<int>> vertices;
    int tot_verts;
    int tot_edges;
    int **adj_matrix;
  public:
    Graph();
    Graph(int);
    void setEdge(int);
    void addVertex(int);
    bool addEdge(int, int);
    void BFS(int);
    bool isPlanar();
    bool isThreeVertCycle();
    bool corol1_check();
    bool K5_Check();
    bool K33_Check();
    
    bool K33_Connect_Check(int, int, int, int, int, int);
    /*
     * We will have a typical graph structure, but here is where we deviate.
     * We will have boolean algorithms to determine if a given graph is planar or not
     * Based on different theorems and tests
     */
    
};

Graph::Graph() //default constructor, should never be called, but exists in case
{
  tot_verts = 0;
  tot_edges = 0;
}

Graph::Graph(int V) //non-default constructor, handles all graph creation
{
  tot_verts = V;
  adj_matrix = new int*[V+1]; //allocates memory for adj matrix
  tot_edges = 0;
  for(int i = 1; i <= V; i++)
  {
    addVertex(i);
  }
  
  for(int i = 0; i <= V; i++) //continues allocation
  { 
    adj_matrix[i] = new int[V+1];
  }
  
  for(int j = 0; j <= V; j++) //initializes all of the adjacency matrix to 0, prevents crashes! :)
  {
    for(int k = 0; k <= V; k++)
    {adj_matrix[j][k] = 0;}
  }
}

void Graph::setEdge(int E) //simple edge count handler
{tot_edges = E;}

void Graph::addVertex(int addme) //adds in a vertex
{
  int space_checker = 0;
  for(auto it = vertices.begin(); it != vertices.end(); it++) //checks if vertice is already set, should never happen
  {
    if(it->first == addme)
    {space_checker++;}
  }
  
  if(space_checker != 0)
  {
    std::cout<<"Duplicate node detected. Sayonara. \n \n";
    return;
  }
  else
  {
    vertices[addme] = std::vector<int>();
  }
}

bool Graph::addEdge(int from, int to) { //adds an edge
  	bool edcheck = false;
  	for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) { //checks for edge existence
    		if(iterat->first == from) {
      			for(auto iterat2 = iterat->second.begin(); iterat2 != iterat->second.end(); iterat2++) {
    				if(*iterat2 == to) {
					edcheck = true;
				}
      			}
    		}
  	}
  	for(auto iterat = vertices.begin(); iterat != vertices.end(); iterat++) {
    		if(iterat->first == to) {
      			for(auto iterat2 = iterat->second.begin(); iterat2 != iterat->second.end(); iterat2++) {
    				if(*iterat2 == from) {
					edcheck = true;
				}
      			}
    		}
  	}
  	if(edcheck) {
    		std::cout<<"Preexisting" << std::endl;
    		return false;
  	}
  	else {
  		vertices[from].push_back(to);
    		vertices[to].push_back(from);
    		std::cout << "Edge from " << from << " to " << to << std::endl;
		adj_matrix[from][to] = 1;
		adj_matrix[to][from] = 1;
		return true;
  	}
}



bool Graph::K5_Check() 
{
  for(int i1 = 1; i1 <= tot_verts - 4; i1++) { //iterates through every subset of 5 vertices
    for(int i2 = i1 + 1; i2 <= tot_verts - 3; i2++) {
      for(int i3 = i2 + 1; i3 <= tot_verts - 2; i3++) {
	for(int i4 = i3 + 1; i4 <= tot_verts - 1; i4++) {
	  for(int i5 = i4 + 1; i5 <= tot_verts; i5++) {
	    if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i3] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i1][i5] == 1
	      && adj_matrix[i2][i3] == 1 && adj_matrix[i2][i4] == 1 && adj_matrix[i2][i5] == 1 && adj_matrix[i3][i4] == 1
	      && adj_matrix[i3][i5] == 1 && adj_matrix[i4][i5] == 1) { //checks if the connections make a K5
	      return true;
	    }
	  }
	}
      }
    }
  }
  return false;
}

bool Graph::K33_Check()
{
  for(int i1 = 1; i1 <= tot_verts - 5; i1++) { //iterates through every subset of 6 vertices
    for(int i2 = i1 + 1; i2 <= tot_verts - 4; i2++) {
      for(int i3 = i2 + 1; i3 <= tot_verts - 3; i3++) {
	for(int i4 = i3 + 1; i4 <= tot_verts - 2; i4++) {
	  for(int i5 = i4 + 1; i5 <= tot_verts - 1; i5++) {
	    for(int i6 = i5 + 1; i6 < tot_verts; i6++) {
	      if(K33_Connect_Check(i1, i2, i3, i4, i5, i6)) { //calls a connect check
		return true;
	      }
	    }
	  }
	}
      }
    }
  }
  return false;
}

bool Graph::K33_Connect_Check(int i1, int i2, int i3, int i4, int i5, int i6) { //each if checks for a K3,3 with every combination of 3s
  if(adj_matrix[i1][i4] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i2][i4] == 1 && adj_matrix[i2][i5] == 1 && adj_matrix[i2][i6] == 1
    && adj_matrix[i3][i4] == 1 && adj_matrix[i3][i5] == 1 && adj_matrix[i3][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i3] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i2][i3] == 1 && adj_matrix[i2][i5] == 1 && adj_matrix[i2][i6] == 1
    && adj_matrix[i4][i3] == 1 && adj_matrix[i4][i5] == 1 && adj_matrix[i4][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i3] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i2][i3] == 1 && adj_matrix[i2][i4] == 1 && adj_matrix[i2][i6] == 1
    && adj_matrix[i5][i3] == 1 && adj_matrix[i5][i4] == 1 && adj_matrix[i5][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i3] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i2][i3] == 1 && adj_matrix[i2][i4] == 1 && adj_matrix[i2][i5] == 1
    && adj_matrix[i6][i3] == 1 && adj_matrix[i6][i4] == 1 && adj_matrix[i6][i5] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i3][i2] == 1 && adj_matrix[i3][i5] == 1 && adj_matrix[i3][i6] == 1
    && adj_matrix[i4][i2] == 1 && adj_matrix[i4][i5] == 1 && adj_matrix[i4][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i3][i2] == 1 && adj_matrix[i3][i4] == 1 && adj_matrix[i3][i6] == 1
    && adj_matrix[i5][i2] == 1 && adj_matrix[i5][i4] == 1 && adj_matrix[i5][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i3][i2] == 1 && adj_matrix[i3][i4] == 1 && adj_matrix[i3][i5] == 1
    && adj_matrix[i6][i2] == 1 && adj_matrix[i6][i4] == 1 && adj_matrix[i6][i5] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i3] == 1 && adj_matrix[i1][i6] == 1 && adj_matrix[i4][i2] == 1 && adj_matrix[i4][i3] == 1 && adj_matrix[i4][i6] == 1
    && adj_matrix[i5][i2] == 1 && adj_matrix[i5][i3] == 1 && adj_matrix[i5][i6] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i3] == 1 && adj_matrix[i1][i5] == 1 && adj_matrix[i4][i2] == 1 && adj_matrix[i4][i3] == 1 && adj_matrix[i4][i5] == 1
    && adj_matrix[i6][i2] == 1 && adj_matrix[i6][i3] == 1 && adj_matrix[i6][i5] == 1) {
    return true;
  }
  if(adj_matrix[i1][i2] == 1 && adj_matrix[i1][i3] == 1 && adj_matrix[i1][i4] == 1 && adj_matrix[i5][i2] == 1 && adj_matrix[i5][i3] == 1 && adj_matrix[i5][i4] == 1
    && adj_matrix[i6][i2] == 1 && adj_matrix[i6][i3] == 1 && adj_matrix[i6][i4] == 1) {
    return true;
  }
  return false;
}

bool Graph::corol1_check() //This uses corollary 1
{
  int Math = 3 * tot_verts - 6;
  if(tot_edges <= Math)
  {return true;}
  else
  {return false;}
}

bool Graph::isPlanar()
{
  if(tot_verts < 5)
  {return true;}
  //A graph with less than 5 edges is always planar since it can never be K5 or K3,3
  
  if(tot_verts == 5)
  {
    if(!corol1_check())
    {return false;}
    else
    {return true;}
  }
  
  if(K5_Check())
  {return false;}
  
  if(K33_Check())
  {return false;}
  
  return true;
}



int main()
{
  int Jo_Lo = 21;
  while(Jo_Lo < 1 || Jo_Lo > 20) {
    std::cout << "\nPlease input how many vertices you want (max 20): ";
    std::cin >> Jo_Lo;
  }
  Graph Guraph(Jo_Lo);
  std::cout << "\nThank you.";
  int Dan_Gan = ((Jo_Lo * (Jo_Lo - 1)) / 2) + 1;
  int R_G = Dan_Gan - 1;
  //n(n-1)/2
  while(Dan_Gan < 0 || Dan_Gan > R_G) {
    std::cout << "\nPlease input how many edges you want (max "<< R_G << "): ";
    std::cin >> Dan_Gan;
  }
  Guraph.setEdge(Dan_Gan);
  int ver1, ver2;
  for(int i = 1; i <= Dan_Gan; i++) {
    ver1 = ver2 = 0;
    while((ver1 < 1 || ver1 > Jo_Lo) && (ver2 < 1 || ver2 > Jo_Lo))
    {
      std::cout << "\nPlease enter in two vertices to connect an edge to (1 - " << Jo_Lo << "): ";
      std::cin >> ver1 >> ver2;
    }
    if(!Guraph.addEdge(ver1, ver2)) {
      i--;}
  }
  
  if(Guraph.isPlanar())
  {std::cout<<"\nHooray! Your graph is planar!! :)\n";}
  else
  {std::cout<<"\nAwwwww! Your graph is not planar.. :( big sad\n";}
  
  
  return 0;
}





