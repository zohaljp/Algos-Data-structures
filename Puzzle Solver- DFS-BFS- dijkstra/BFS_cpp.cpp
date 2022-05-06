#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int row[] = {0,-1,0,1}; //  Down, Left, Up, Right
int column[] = {-1,0,1,0}; // Down, Left, Up, Right
int coster = 0;


struct Node{

    int x;
    int y;
    int move_level;
    int moving_cost;
    Node* prnt;
    int puzzle [3][3];
};

stack <Node*> solutionNodes;


Node *newN (int puzzle[3][3], int x, int y, int a, int b, int move_level, Node *prnt){
    
    Node *nodeNew = new Node;

    nodeNew->prnt = prnt;
    
    int k,l,w;
    for(k=0;k<3;k++){
        for(l=0;l<3;l++){
            nodeNew->puzzle[k][l] = puzzle[k][l];
        }
    }
    
    // according to the tile game, only one tile can move, so position swapped
    // only 1 move allowed
    int temp = nodeNew->puzzle[x][y];
    
    nodeNew->puzzle[x][y] = nodeNew->puzzle[a][b];
  
    nodeNew->puzzle[a][b] = temp;
        
    // the hole coprdinates are updated
  
    nodeNew->x = a;
    nodeNew->y = b;

    // move level updated by 1 everytime a new node is created
    nodeNew->move_level = move_level;
    
    nodeNew->moving_cost = INT_MAX;
   
    return nodeNew;

}

// Helper function to print the 2D array.
void puzzlePrinter (int puzzle[3][3]){
    int k,l;
    for(k=0;k<3;k++){
        for(l=0;l<3;l++){
            cout <<  puzzle[k][l] << '|';
        }
        cout<<endl;
    }
}



// Helper function to compare if the puzzle matches the final state
void finalStatePrinter (Node *finalNode){
    
    // if not yet reached the final state
    if(finalNode == NULL){
        return;
    }
   

    // Gets called recursively and prints out th intial state of the puzzle till it is solved
    finalStatePrinter(finalNode->prnt);

    solutionNodes.push(finalNode->prnt);
    
    // This prints each puzzle everytime a co
    puzzlePrinter(finalNode->puzzle);
    cout << endl << endl;
    
}

// This is a helper function that compares the state of the puzzle with the final state 
// If it is reached then true is sent to stop making new nodes. and final cost is printed
bool isEqual(int a[3][3], int b[3][3])
{
    int v,w;
    for (v=0;v<3;v++)
    {
        for (w=0;w<3;w++)
        {
            if (a[v][w] != b[v][w])
            {
                return false; //if any difference, return false
            }
        }
    }
    return true;
}

void BFS(int finalState[3][3], int initialState[3][3], int x, int y){
   
    Node *startingNode = newN(initialState, x, y, x, y, 0, NULL);
   
    startingNode->moving_cost = 0 ;
   
    // BFS makes use of a queue data structure 
    queue<Node*> nodeQueue;
    
    nodeQueue.push(startingNode);

    if(!nodeQueue.empty()){
        cout << "Staring node placed into the queue"<<endl;
    }

    int w;
    Node* first;
    int flag = 0;
    do{
        
        Node *first = nodeQueue.front();      
        
        nodeQueue.pop();
        
        for(w=0; w<4; w++){

            //a >= 0 && a < 3 && b >= 0 && b < 3

            // X,Y is the prev hold, A containt the number of mves made in arow and B is the number of moves in a column
            // move level incremented everytime this funtion is called
       
            if( ((first->x + row[w])>= 0) && ((first->x + row[w])< 3) ){
                if(((first->y + column[w]) >= 0) && ((first->y + column[w]) < 3))
                {
                   
                    Node *child = newN(first->puzzle, first->x, first->y, first->x + row[w], first->y + column[w], first->move_level + 1, first);
                    nodeQueue.push(child);
                    
                }
            }
        }



        if(isEqual(first->puzzle, finalState)){
           finalStatePrinter(first);
           cout<< "Level: " << first->move_level << endl;
           break; 
        }

    }while(!nodeQueue.empty());

    
    
}

int main(){
    int v,w,x,y;
    int initialState [3][3] = {{1, 3, 4}, {8, 0, 6}, {7, 5, 2}};

    int finalState [3][3] = {{1,2,3}, {8,0,4}, {7,6,5}}; 

    //This find the hold in the starting puzzle

    for(v=0;v<3;v++){
        for(w=0;w<3;w++){
            if(initialState[v][w] == 0){
                x = v;
                y = w;
            }
        }
    }
   
    BFS(finalState,initialState,x,y);     
    
   int size = solutionNodes.size();
    int temp2;
    Node *temp4;
    for(int i = 0; i<solutionNodes.size(); i++){
        Node *temp = solutionNodes.top();
        solutionNodes.pop();
        Node *temp1 = solutionNodes.top();
        temp4  = temp1;
        for(int a = 0; a<3; a++){
            for(int j=0;j<3;j++){               
                if(temp->puzzle[a][j] != temp1->puzzle[a][j]){

                    temp2 = temp->puzzle[a][j];
                    coster += temp2;

                }
            }
            
        }
         
        
    }

        
    

    cout << "Final cost " << coster << endl;     
}