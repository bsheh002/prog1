#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) { //creates a new node and sets it payload to the parameter and the node's next to be nullptr
    Node* node1 = new Node;
    node1->payload = payload;
    node1->next = nullptr;
    return node1;
}

Node* loadGame(int n, vector<string> names) { //uses a vector of names and adds it to the node list
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) { //iterates through the number of names in the vector
        name = names.at(i);
        if (head == nullptr) { //checks to see if list is empty and starts the list with the first name in the vector list
            head = newNode(name); // initialize head specially
            head->next = head;
            prev = head;
        } else {
            prev->next = newNode(name);
            prev = prev->next;
        }
    }

    if (prev != nullptr) { //checks to see if there is a previous node and sets the node's next to the head
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) { //checks to see that the list hasn't ended
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) { //checks to see if curr has iterated through every name
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = nullptr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
          prev = curr;
          curr = curr->next;
        }

        prev->next = curr->next; // delete kth node
        
        delete curr;
        curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) { //checks to see if there is a last person standing and sets them to be the winner
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}
