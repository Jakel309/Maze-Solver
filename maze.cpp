#include <iostream>
#include <fstream>
#include "p2stack.h"

using namespace std;

struct Directions
{
	int size;
	int west;
	int east;
	int north;
	int south;
};


//Finds the directions from the start to the finish
void checkPossibleM(string maze, Stack<char>& Move, int size)
{
	int pos=size+2;
	char popVar;
	char space='X';
	string mazeF=maze;

	Directions m;

	m.size=0;

	Stack<char> PossibleM;
	initialize(PossibleM);

	//Finds the start
	while(space!='S')
	{
		space=maze[pos];
		pos++;
	}
	pos--;


	//Define directions
	m.west=pos-1;
	m.east=pos+1;
	m.north=pos-size;
	m.south=pos+size;

	//Loop to find path to finish
	while(space!='F')
	{
		bool finish=false;
		bool possible=false;
		//Find all possible moves
		if(mazeF[m.west]=='F')
		{
			push(PossibleM,'W');
			m.size++;
			finish=true;
			possible=true;
		}
		if(mazeF[m.east]=='F')
		{
			push(PossibleM,'E');
			m.size++;
			finish=true;
			possible=true;
		}
		if(mazeF[m.north]=='F')
		{
			push(PossibleM,'N');
			m.size++;
			finish=true;
			possible=true;
		}
		if(mazeF[m.south]=='F')
		{
			push(PossibleM,'S');
			m.size++;
			finish=true;
			possible=true;
		}
		if(!finish){
			if(mazeF[m.west]=='.')
			{
				push(PossibleM,'W');
				m.size++;
				possible=true;
			}
			if(mazeF[m.east]=='.')
			{
				push(PossibleM,'E');
				m.size++;
				possible=true;
			}
			if(mazeF[m.north]=='.')
			{
				push(PossibleM,'N');
				m.size++;
				possible=true;
			}
			if(mazeF[m.south]=='.')
			{
				push(PossibleM,'S');
				m.size++;
				possible=true;
			}
		}

		while (!possible){
			popVar=pop(Move);
			mazeF[pos]='X';
			if(popVar=='W')
				pos=m.east;
			if(popVar=='E')
				pos=m.west;
			if(popVar=='N')
				pos=m.south;
			if(popVar=='S')
				pos=m.north;

			//Redefine directions
			m.west=pos-1;
			m.east=pos+1;
			m.north=pos-size;
			m.south=pos+size;

			//Check if any new possibilities have opened up
			if(mazeF[m.west]=='F')
			{
				push(PossibleM,'W');
				m.size++;
				finish=true;
				possible=true;
			}
			if(mazeF[m.east]=='F')
			{
				push(PossibleM,'E');
				m.size++;
				finish=true;
				possible=true;
			}
			if(mazeF[m.north]=='F')
			{
				push(PossibleM,'N');
				m.size++;
				finish=true;
				possible=true;
			}
			if(mazeF[m.south]=='F')
			{
				push(PossibleM,'S');
				m.size++;
				finish=true;
				possible=true;
			}
			if(!finish){
				if(mazeF[m.west]=='.')
				{
					push(PossibleM,'W');
					m.size++;
					possible=true;
				}
				if(mazeF[m.east]=='.')
				{
					push(PossibleM,'E');
					m.size++;
					possible=true;
				}
				if(mazeF[m.north]=='.')
				{
					push(PossibleM,'N');
					m.size++;
					possible=true;
				}
				if(mazeF[m.south]=='.')
				{
					push(PossibleM,'S');
					m.size++;
					possible=true;
				}
			}
		}
		popVar=pop(PossibleM);
		m.size--;
		//Add next move to final stack
		push(Move, popVar);
		//Change old position to '0' so to not backtrack
		mazeF[pos]='0';

		//Move to the new position
		if(popVar=='W')
			pos=m.west;
		if(popVar=='E')
			pos=m.east;
		if(popVar=='N')
			pos=m.north;
		if(popVar=='S')
			pos=m.south;
		space=maze[pos];
		m.west=pos-1;
		m.east=pos+1;
		m.north=pos-size;
		m.south=pos+size;
		//cout<<popVar;
	}
	destroy(PossibleM);
}

int main()
{
	int size;
	string maze="", filename;
	ifstream fin;

	Stack<char> Move;
	initialize(Move);

	//Gets file name than opens
	cin>>filename;
	fin.open(filename.c_str());

	//Checks if file is open then retrieves data from it
	if(fin.is_open())
	{
		fin>>size;

		string n;
		while(fin>>n)
		{
			maze+=n;
		}
	}
	else
	{
		cout<<"File not found";
		return 0;
	}
	fin.close();
	checkPossibleM(maze,Move,size);

	Stack<char> Final;
	initialize(Final);
	
	while(!isEmpty(Move))
		push(Final, pop(Move));
	while(!isEmpty(Final))
		cout<<pop(Final);
	
	destroy(Move);
	destroy(Final);
}