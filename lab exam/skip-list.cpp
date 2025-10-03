#include "skip-list.h"

/* 
The insert function has been implemented as follows:
1. Randomly decide the number of levels for the new node(newLevel) using coin flips.
2. Now to search position for inserting it, we need to do in O(log n) average time complexity,
    for that, we go to highest level(as it has least num of nodes) and traverse through it till
    we find an element larger than the inserting element, then we go a level down after storing 
    the pointer to node just smaller than inserting element. We go down till we reach level = 0.
3. Now we have, at each level, the pointer to node just smaller than inserting element. Now 
    we insert this node in each level from 0 to newLevel.
*/
bool skipList::insert(int data) 
{
    // TODO 1: IMPLEMENT YOUR CODE HERE
    if (!(head->next[Level]) && Level ==0){
        Node* n = new Node(data, Level);
        head->next[0] = n;
        return true;
    }

    int newLevel = 0;
    while(coin_flip()){
        newLevel++;
    }
    
    for(int i=0; i<newLevel; i++){
        Node* current = head->next[i];
        while(current->next[i] && current->next[i]->getData()<data){
            current= current->next[i];
        }
        
        Node* n = new Node(data, i);
        if (!current->next[i]){
            current->next[i] = n;
        }
        Node* temp = current->next[i];
        current->next[i] = n;
        n->next[i] = temp;

    
    return true;
}
}


/*
The remove function is implemented as follows:
1. Starting fromt he highest level, we traverse through the list to find the position
    of the node to be deleted, at each level we store the pointer to the node just smaller
    than the node to be deleted.
2. At level 0, we check whether the node to be deleted exists or not.
3. If it does exist, we delete it from each level that it exists on.
4. Finally, we do some cleanup, we remove the levels which don't have any nodes.
*/
bool skipList::remove(int data) 
{
    // TODO 2: IMPLEMENT YOUR CODE HERE
    int i =Level;
    if (!head->next[i] && i==0){
        Node* n = new Node(data, i);
        head->next[i] = n;
        return true;
    }
    for(;i>=0;i--){
            Node* current = head;
            while(current->next[i] && current->next[i]->getData()==data){
                current= current->next[i];
            }
            
            if (!current->next[i]){
                break;
            }
            Node* temp = current->next[i];
            current->next[i] = temp->next[i];
            delete temp;
            break;
        }
    
    
 
    return true;
}


/*
The search function is implemented as follows:
1. Starting from the highest level and head node, we traverse
    through the list to find the position of the node to be searched.
2. At level 0, we check whether the node to be searched exists or not.
3. If it exists, we return true, else false.
*/
bool skipList::search(int data) 
{
    
    // TODO 3: IMPLEMENT YOUR CODE HERE
    int i = Level;
    Node* current = head->next[i];
    while(current){
        if (current->getData() == data){
            return true;
        }
        else if (current->getData() < data){
            current = current->next[i];
        }

        else {
            i--;
            current = current->next[i];
        }
    }
    
    return false;
}

