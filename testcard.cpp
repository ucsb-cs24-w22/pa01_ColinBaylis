#include "cards.h"

#include <iostream>
using namespace std;

int getTest();

int main() {
    
    CardBST bst1;
    bst1.insert('d', 9);
    bst1.insert('c', 0);
    bst1.insert('h', 10);
    bst1.insert('h', 4);
    bst1.insert('h', 7);
    bst1.insert('h', 8);
    bst1.insert('h', 6);
    bst1.insert('c', 4);
    bst1.insert('s', 6);
    bst1.insert('h', 9);
    bst1.insert('h', 3);
    bst1.insert('s', 10);
    bst1.insert('d', 11);
    bst1.insert('c', 8);
    bst1.insert('c', 11);
    bst1.insert('d', 3);
    bst1.insert('s', 11);
    bst1.insert('h', 2);
    bst1.insert('c', 6);
    bst1.insert('h', 5);
    bst1.insert('s', 0);
    bst1.insert('s', 12);
    bst1.insert('c', 7);
    bst1.insert('s', 5);
    bst1.insert('s', 2);
    bst1.insert('s', 13);
    bst1.insert('h', 13);
    bst1.insert('s', 9);
    bst1.insert('d', 13);
    bst1.insert('c', 13);


    bool all = true;
    int testnum = getTest();
    if(testnum) { all = false; }

    cout << "CardBST: " << endl << " pre-order: ";
    bst1.printPreOrder();
    cout << endl;

    if (all || testnum == 1) {
        cout << "  in-order: ";
        bst1.printInOrder();
        cout << endl;
    }
    if (all || testnum == 2) {
        cout << "  post-order: ";
        bst1.printPostOrder();
        cout << endl;
    }
    if (all || testnum == 4)
        cout << "  count: " << bst1.count() << endl;
    if (all || testnum == 5) {
        cout << "  contains h 10? " <<
                (bst1.contains('h', 10) ? "Y" : "N") << endl;
        cout << "  contains c 6? " <<
            (bst1.contains('c', 6) ? "Y" : "N") << endl;
        cout << "  contains h 11? " <<
            (bst1.contains('h', 11) ? "Y" : "N") << endl;
        cout << "  contains s 8? " <<
            (bst1.contains('s', 8) ? "Y" : "N") << endl;
        cout << "  contains d 6? " <<
            (bst1.contains('d', 6) ? "Y" : "N") << endl;
        cout << "  contains c 13'? " <<
            (bst1.contains('c', 13) ? "Y" : "N") << endl;
    }
    if(all || testnum == 6){
        cout << "  predecessor of c 6 is: " <<
            bst1.getPredecessor('c', 6)->value << endl;
        cout << "  successor of h 3 is: " <<
            bst1.getPredecessor('h', 3)->value << endl;
        cout << "  predecessor of h 13 is: " <<
            bst1.getPredecessor('h', 13)->suit << endl;
        cout << "  successor of d 11 is: " << 
            bst1.getSuccessor('d', 11)->suit << endl;
    }
    if(all || testnum == 7) {
        cout << "  removing c 6" << endl;
        bst1.remove('c', 6);
        cout << "  removing h 2" << endl;
        bst1.remove('h', 2);
        cout << "  removing h 13" << endl;
        bst1.remove('h', 13);
        cout << "  removing d 11" << endl;
        bst1.remove('d', 11);
        cout << "  contains c 6? " <<
            (bst1.contains('c', 6) ? "Y" : "N") << endl;
        cout << "  contains s 10? " <<
            (bst1.contains('s', 10) ? "Y" : "N") << endl;
        cout << "  contains d 11? " <<
            (bst1.contains('d', 11) ? "Y" : "N") << endl;
        cout << "  contains h 13? " <<
            (bst1.contains('h', 13) ? "Y" : "N") << endl;
        cout << "  contains h 2? " <<
            (bst1.contains('h', 2) ? "Y" : "N") << endl;
        cout << "  contains s 6? " <<
            (bst1.contains('s', 6) ? "Y" : "N") << endl;
        cout << "  pre-order: ";
            bst1.printPreOrder();
            cout << endl;
        }
    return 0;
}

int getTest() {
    cout << "Choice of tests:\n"
	 << "  0. all tests\n"
	 << "  1. just printInOrder\n"
	 << "  2. just printPostOrder\n"
	 << "  4. just count\n"
	 << "  5. just contains\n"
	 << "  6. just predecessor/successor\n"
	 << "  7. just remove\n";
	 
    do {
        int choice;
        cout << "Enter choice:\n";
        cin >> choice;
        if (choice >=0 && choice <= 7)
            return choice;
        cout << "0, 1, 2, 3, 4, 5, 6, or 7 only!\n";
    } while (true);
}