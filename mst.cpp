#include <iostream>
#include <fstream>
#include <cmath>
#include <limits.h>

using namespace std;


//printing the the array 
void printArray(int* array, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//calculating the distance using the formula given in th assignment
int dist(int x1, int y1, int x2, int y2){
	return round(sqrt(((x1 - x2) * (x1 - x2)) + (y1 - y2) * (y1 - y2)));
}

//checking if the current node has any nodes connected to it
bool checkConnect(int** connect, int curr){
  //if it returns -1 then that means there are no nodes connected
	if (connect[curr][0] != -1){
		return true;
  }
  else{
	  return false;
  }
}

//checking if two specific nodes are connected
bool specNodCon(int** connected, int numNodes, int node1, int node2){
	int index = 0;

  //checking if node1 is connected to node2
	while (index < numNodes && connected[node1][index] != -1){
	
    if (connected[node1][index] == node2){
			return true;
    }

		index++;
	}
	
  //setting the index back to 0
	index = 0;

  //checking if node2 is connected to node1
	while (index < numNodes && connected[node2][index] != -1){
	
    if (connected[node2][index] == node1){
			return true;
    }

		index++;
	}

  //defaults to nodes not being connected
	return false;
}

//find the closest free node
int findFreeClose(int** connected, int* x, int* y, int numNodes, int node1){
	int minIndex = -1;
  int min = INT_MAX;
  //going through all the nodes
	for (int i=0; i < numNodes; i++){
   
    //if the node is not the same and the distance is less than the min
		if (i != node1 && !checkConnect(connected, i) && dist(x[node1], y[node1], x[i], y[i]) < min){
		  //change the index of the minimum
      minIndex = i;
      //reassign the minimum
			min = dist(x[node1], y[node1], x[i], y[i]);
		}
  }

	return minIndex;
}


//getting the two new nodes and calculating the weight of them
int connect(int** connected, int* x, int* y, int numNodes, int node1, int node2, int &weight){
	int index = 0;
  
  //while the index is full
  while (index < numNodes && connected[node1][index] != -1){
  	//go to the next index to find an empty one
    index++;
  }

  //connecting that node1 to node 2
	connected[node1][index] = node2;
	
	index = 0;

  //while the second index is full
	while (index < numNodes && connected[node2][index] != -1){
		index++;
  }
  //connect node2 to node node1
	connected[node2][index] = node1;
	
  //calculate the weight
	return weight += dist(x[node1], y[node1], x[node2], y[node2]);
}

//constructing the actual MST
int mst(int* x, int* y, int numNodes)
{
	int weight = 0;
	int** connected = new int *[numNodes + 1];
	for (int i = 0; i <= numNodes; i++)		//	intitialize blank connections
	{
		connected[i] = new int[numNodes + 1];
		for (int j = 0; j <= numNodes; j++)
			connected[i][j] = -1;
	}
	
	int low = 0;
  int last = 0;

  //go through all the vertices
	for (int k = 0; k < numNodes; k++){
    //finding the edge with the lowest weight
		low = findFreeClose(connected, x, y,numNodes, last);	

    //if the lowest is not a negative number
    if (low >= 0){
      //connect the last node and the low node
			connect(connected, x, y, numNodes, last, low, weight);	
    }		

    last = low;
	}
	
  //delete all the connected nodes
	for (int a = 0; a < numNodes; a++){
		delete [] connected[a];
  }

	delete [] connected;
	
  return weight;
}

int main(int argc, const char * argv[]){
  
  //opening the file
  fstream myFile;
  myFile.open("graph.txt");

  int numTestCases, numVertices;
	myFile >> numTestCases;
	for (int j = 0; j < numTestCases; j++)
	{
		myFile >> numVertices;
		int x[numVertices];
		int y[numVertices];
		
		for (int i = 0; i < numVertices; i++)		//	read coordinates
		{
			myFile >> x[i];
			myFile >> y[i];
		}
		
		cout << "Test case " << j + 1 << ": MST weight " << mst(x, y, numVertices) << "\n";
	}
	
	
	myFile.close();
	return 0;
}
