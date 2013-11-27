//
//  roomConfig.cpp
//  Test1
//
//  Created by Anthony Jones on 5/19/13.
//
//

#include "roomConfig.h"

roomConfig::roomConfig()
{
    //init array of baseRoom object
    
    for(int i = 0; i < 4; i++){
  
        //transverse through the array and initialize all the baseRoom objects
        baseRoom* r = new baseRoom();
        //r->init();
        char room_key[50];
        sprintf(room_key, "room%dcrew", (i + 1));
        
        //give the room their mapkey string
        r->roomKey = room_key;
        
        //push baseRoom
        rooms.push_back(r);
        
    }
    
    
    //get a random shape
    
    shape = randomShape();
    
    //use shape string as the case in a switch statement
    switch(shape){
        case 1: //straight line
            
            //in each case connect the rooms by assigning pointers to the adjacent rooms
            rooms[0]->downRoom = rooms[1];
            
            rooms[1]->upRoom= rooms[0];
            rooms[1]->downRoom= rooms[2];
            
            rooms[2]->upRoom = rooms[1];
            rooms[2]->downRoom= rooms[3];
            
            rooms[3]->upRoom = rooms[2];
            
            break;
            
        default:
            break;
    }
        
    
    //outside the switch statement
    //randomly assign types to the rooms
    
    map<int, string> typeMap;
    vector<int> cards {1,2,3,4};
    //1
    //*************************
    //for (int k = 0; k < cards.size();k++) {
      //  cout << "ints = " << cards[k] << endl;
    //}
    //cout << "*************" << endl;
    srand(time(NULL));
    int rd = rand() % cards.size();
    cout << "rd = " << rd << endl;
    typeMap.insert(pair<int, string>(cards[rd],"unloading"));
    
    for(int i = 0;i < cards.size();i++)
    {
        if (cards[rd] == cards[i]) {
            cards.erase(cards.begin() + i);
        }
    }
    //if(cards.size() == 3){
      //  cout << "this is 3 " << endl;
    //}
    //*************************
    
    //2
    //*************************
    //for (int k = 0; k < cards.size();k++) {
      //  cout << "ints = " << cards[k] << endl;
    //}
    //cout << "*************" << endl;
    srand(time(NULL));
    rd = rand() % cards.size();
    cout << "rd = " << rd << endl;
    typeMap.insert(pair<int, string>(cards[rd],"shooting"));
    
    for(int i = 0;i < cards.size();i++)
    {
        if (cards[rd] == cards[i]) {
            cards.erase(cards.begin() + i);
        }
    }
    cards.resize(2);
    //if(cards.size() == 2){
      //  cout << "this is 2 " << endl;
    //}
    //*************************
    
    //3
    //*************************
    //for (int k = 0; k < cards.size();k++) {
      //  cout << "ints = " << cards[k] << endl;
    //}
    //cout << "*************" << endl;
    srand(time(NULL));
    rd = rand() % cards.size();
    cout << "rd = " << rd <<endl;
    typeMap.insert(pair<int, string>(cards[rd],"greenroom"));
    
    for(int i = 0;i < cards.size();i++)
    {
        if (cards[rd] == cards[i]) {
            cards.erase(cards.begin() + i);
        }
    }
    cards.resize(1);
    //if(cards.size() == 1){
      //  cout << "this is 1 " << endl;
    //}
    //*************************
    
    //4
    //*************************
    //for (int k = 0; k < cards.size();k++) {
      //  cout << "ints = " << cards[k] << endl;
    //}
    //cout << "*************" << endl;
    srand(time(NULL));
    rd = rand() % cards.size();
    cout << "rd = " << rd << endl;
    typeMap.insert(pair<int, string>(cards[rd],"crafts"));
    
    for(int i = 0;i < cards.size();i++)
    {
        if (cards[rd] == cards[i]) {
            cards.erase(cards.begin() + i);
        }
    }
    //*************************


        
    //for (int u = 0; u < typeMap.size();u++){
    //    cout << u+1 << endl;
     //   cout << "typeMap = " << typeMap.at(u+1) <<endl;
   // }
    
    vector<string> types;
    types.push_back(typeMap.at(1));
     types.push_back(typeMap.at(2));
     types.push_back(typeMap.at(3));
     types.push_back(typeMap.at(4));
    //for (int k = 0; k < 4;k++) {
       // cout << "types = " << types[k] << endl;
    //}
    
    for (int i = 0; i < rooms.size(); i++) {
                 
                
                rooms[i]->setType(types[i]);
          
        
    }
    
    this->printConfig();
    
}
void roomConfig::printConfig()
{
    cout << "roomConfig = " << this << endl;
    cout << "rooms[0] = " << rooms[0] << endl;
    cout << "rooms[1] = " << rooms[1] << endl;
    cout << "rooms[2] = " << rooms[2] << endl;
    cout << "rooms[3] = " << rooms[3] << endl;
}
int roomConfig::randomShape()
{
    int shape = 1;
    
    return shape;
}