
using namespace std;
#include <iostream>
#include "graph.h"
#include "HashTable.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <climits>

	//Prototypes

	void StartUp(int argc, char *argv[], vector <string> &list, Graph <string> &myGraph, Queue <string> &myQ);
	void OpenFile(ifstream &infile,char *argv[], int argc);
	void printMenu(vector <string> &list, int numberv, HashTable &vertices, Graph <string> &myGraph, Queue <string> &myQ);
	void insertionSort(vector<string> &list);
	void initializeArrays(vector <string> &list, string varr[], bool marked[], int dist[], string prev[]);
	void valIn(string &input, HashTable &vertices);
	void dSetUp(vector <string> &list, int numberv, string input, Graph <string> &myGraph, Queue <string> &myQ);
	int findString(string input, int numberv, string varr[]);
	void printRow(int index, string varr[], int dist[], string prev[]);
	void dAlg(string input, int numberv, string varr[], bool marked[], int dist[], string prev[], Graph <string> &myGraph, Queue <string> &myQ);
	void minDistV(string &currV, int numberv, string varr[], bool marked[], int dist[]);
	bool areAllTrue(bool marked[], int numberv);


int main(int argc, char *argv[]){

	Graph<string> myGraph(50);
	Queue<string> myQ(50);
	vector <string> list;

	StartUp(argc,argv,list,myGraph,myQ);



	return 0;
}


//Precondition: Valid command line arguments, vector, graph object, and queue object will be passed as parameters.
//////Postcondition:Will open and process the file that is sent on the command line and build the graph based on the file.
 void StartUp(int argc, char *argv[], vector <string> &list, Graph <string> &myGraph, Queue <string> &myQ){


		 ifstream infile;


		 OpenFile(infile, argv, argc); 

		 

		
		 HashTable vertices(50);
	
		 string origin, dest, tlength;
		 int numberv, length;
		 string s; 



		  while (getline(infile, s)){

			stringstream ss(s);
			getline(ss,origin,';');
	
			getline(ss,dest,';');
		
			getline(ss,tlength,';');
		

			if(!(vertices.find(origin))){

			myGraph.AddVertex(origin);
			vertices.insert(origin);
			list.push_back(origin);
			numberv++;
			}

			 if(!(vertices.find(dest))){

                        myGraph.AddVertex(dest);
                        vertices.insert(dest);
			list.push_back(dest);
                        numberv++;
                        }

			length = stoi(tlength);
			myGraph.AddEdge(origin, dest, length);


			
			}
		printMenu(list, numberv, vertices, myGraph, myQ);
	}



//Precondition: A valid ifstream and command line arguments will be passed in as parameters.
////Postcondition:Will open the file that is sent to the command line if there is one and if it is valid.
 void OpenFile(ifstream &infile,char *argv[], int argc){

                if(argc == 1){ //if argc equals 1
                cout << "The command line inputs were not correct." << endl;
		cout<< "Please try again." << endl; //they did not enter a filename and display error message
                exit(1); //exit
                }

                string namef =argv[1]; //string for filename

                infile.open(namef.c_str(),ifstream::in); //open up file


		 if(!infile){
			cout << "The File Name included is incorrect." << endl;
			cout << "Please try again." << endl;
                        exit(1);
                }
		 system("clear"); //maybe clear screen here again idk


        }

//Precondition: Valid vector, integer, HashTable object, Graph object, and Queue object will be passed in as parameters.
////////Postcondition:Will print the menu for Dijkstra's algorithm with the vertices sorted in alphabetical order and receive valid input from the user.
 void printMenu(vector <string> &list, int numberv, HashTable &vertices, Graph <string> &myGraph, Queue <string> &myQ){
	
	string input;

	insertionSort(list);
	cout << "\t" <<  "\t" << "^^^^^^^^^^^^^^^^ DIJKSTRA’S ALGORITHM ^^^^^^^^^^^^^^^" << endl << endl;
	cout << "\t" << "\t" << "A Weighted Graph Has Been Built For These " << numberv << " Cities :" << endl << endl;

	for(int i = 0; i < list.size(); i++){
	
	if(i%3 == 0){ 
	cout << endl;

	}

	cout << setw(30) << list[i];


	}

		valIn(input, vertices);
                dSetUp(list, numberv,input, myGraph, myQ); //maybe call this DAlg start because this is the first thing that happens??


        }

//Precondition: Valid string and HashTable object will be passed in as parameters.
////////Postcondition:Will prompt the user to enter valid input until the user enters a valid vertex.
 void valIn(string &input, HashTable &vertices){

	cout << endl << endl;
	cout << "\t" << "\t" << "Please input your starting vertex: ";
	getline(cin,input);


	while(!(vertices.find(input))){

	 cout << "\t" << "\t" << "Starting location does not exist..." << endl;
         cout << "\t" << "\t" <<  "Please input a new starting vertex: " ;
	 getline(cin,input);

	}}


//Precondition: Valid vector will be passed in as a parameter.
////////Postcondition:Will sort the vector in alphabetical order using insertion sort.
void insertionSort(vector<string> &list){

for( int p = 1; p < list.size( ); p++ )
     {
         string tmp = list[ p ];

         int j;
         for( j = p; j > 0 && tmp < list[ j - 1 ]; j-- )
              list[ j ] = list[ j - 1 ];

         list[ j ] = tmp;
     }



}


//Precondition: Valid command vector, integer, string, Graph object, and Queue object will passed in as parameters.
////////Postcondition:Will set up to perform Dijkstra's algorithm.
void dSetUp(vector <string> &list, int numberv, string input, Graph <string> &myGraph, Queue <string> &myQ){
	string varr[list.size()]; //array of strings of vertices
        bool marked[list.size()]; //array of booleans indicating if a vertex is marked or not
        int dist[list.size()]; //array of integers of distances
        string prev[list.size()]; //array of strings of previous vertices

	initializeArrays(list,varr,marked,dist,prev);

	int index = findString(input, numberv, varr);


	marked[index] = true;
	dist[index] = 0;



	cout << "\t" <<"\t" << "----------------------------------------------------------------------------" << endl;
	cout << setw(30) << "Vertex" << setw(30) << "Distance" << setw(30) << "Previous" << endl << endl;

	printRow(index,varr,dist,prev);
	dAlg(input, numberv, varr, marked, dist, prev, myGraph, myQ);

 
   

}


//Precondition: Valid vector and four parallel arrays will be passed in as parameters.
////////Postcondition:Will intialize the arrays, so we can perform Dijkstra's algorithm.
void initializeArrays(vector <string> &list, string varr[], bool marked[], int dist[], string prev[]){



	for(int i = 0; i < list.size(); i++){

		varr[i] = list[i];
		marked[i] = false;
		dist[i] = INT_MAX;
		prev[i] = "N/A";

	}





}



//Precondition: Valid string, integer, and array will be passed as parameters.
//////////Postcondition:Will return an integer of the index of where the vertex is found in the array.
int findString(string input, int numberv, string varr[]){

	int index = 0;


		for(int i = 0; i < numberv; i++){

		if(input.compare(varr[i]) == 0){

		index = i;}
		}


	return index;

	}



//Precondition: Valid integer, and three arrays (vertices, distance, and previous) will be passed as parameters.
////////////Postcondition:Will print row out with the vertex, distance, and previous.
void printRow(int index, string varr[], int dist[], string prev[]){

	if((dist[index] == INT_MAX) || (dist[index] < 0)){

		cout << setw(30) << varr[index] << setw(30) << "Not On Path"  << setw(30) << prev[index] << endl;

	}


	else{
	cout << setw(30) << varr[index] << setw(30) << dist[index] << setw(30) << prev[index] << endl;}


}



//Precondition: Valid string, integer, four parallel arrays, Graph object, and Queue object will be passed as parameters.
////////////Postcondition:Will perform Dijkstra's algorithm.
void dAlg(string input, int numberv, string varr[], bool marked[], int dist[], string prev[], Graph <string> &myGraph, Queue <string> &myQ){


	string currV = input; //current vertex
	int currIn = 0; //current index of adjacent vertex
	int tempdist = 0; //integer to store the temp distance from one vertex to another 

	while(!areAllTrue(marked,numberv)){	
	myGraph.GetToVertices(currV, myQ);
	

	while(!myQ.isEmpty()){


	currIn = findString(myQ.getFront(),numberv, varr);

	if(marked[currIn] == false){


		tempdist = dist[findString(currV,numberv,varr)] + myGraph.WeightIs(currV, myQ.getFront()); // no tot distance

		if(tempdist < 0 || tempdist == INT_MAX){
	
			break;


		}


		if(tempdist < dist[currIn]){

			dist[currIn] = tempdist;
			prev[currIn] = 	currV;
		}}	

	myQ.dequeue();
	}


	minDistV(currV, numberv,varr,marked,dist);


	 printRow(findString(currV,numberv,varr),varr,dist,prev);

//	int curr = findString(currV,numberv,varr);
//	printRow(curr,varr,dist,prev);

}

	cout << endl <<  "\t" <<"\t" << "----------------------------------------------------------------------------" << endl;


}




//Precondition: Valid string, integer, and arrays for vertices, marked, and distance will be passed as parameters.
////////////Postcondition:Will find the minimum unmarked vertex.
void minDistV(string &currV, int numberv, string varr[], bool marked[], int dist[]){


	vector <int> unMar;

	for(int i  = 0; i < numberv; i++){

		if(marked[i] == false){
		
			unMar.push_back(i);

		}

	} //vector with unMarked vertices
	

	

	int minIndex = unMar[0];
	int mindist = dist[minIndex];





	for(int i = 0; i < unMar.size(); i++){

		if(mindist > dist[unMar[i]]){

			minIndex = unMar[i];
			mindist = dist[minIndex];

		}}


		currV = varr[minIndex];
		marked[minIndex] = true;		


}



//Precondition: Valid array of marked vertices and integer will be passed as parameters.
////////////Postcondition:Will return a boolean if all the vertices are marked or not.
bool areAllTrue(bool marked[], int numberv){

	for(int i = 0; i < numberv; i++){


		if(marked[i] == false){
			return false;
		}

	}

		return true;
	}


