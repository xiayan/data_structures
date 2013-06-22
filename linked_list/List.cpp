#include "List.h"

List::List() : s(0) {
    // Use the first node as sentinel node
    first = new Node();
    first->value = ~(1 << 31);
    first->next = first;
}

List::~List() {
    Node *runner = first;
    do {
        delete runner;
        runner = runner->next;
    } while (runner != first);
}

bool List::isEmpty() {
    return (first == first->next);
}

void List::insert(int x) {
    // Driver for the recursive version of insert
    insert(x, first);
}

void List::insert(int x, Node *current) {
    // Base case: current's next field == first.
    // Since this is a circular linked list, the current node must be the last in the list
    if (current->next == first) {
        Node *new_node = new Node(x, first);
        current->next = new_node;
        s++;
    } else
        // Recursively traverse to the last of the list
        insert(x, current->next);
}

int List::remove(int d) {
    // If the index is out of bound, print the error message and return ~(1 << 31).
    // Has to make sure this number will never appear in the input data file.
    if (d <= 0) {
        cout << "This list is 1-indexing.  The smallest index is 1.\n";
        return ~(1 << 31);
    }
    else if (d > s) {
        cout << "Index " << d << " is out-of-bound!\n";
        cout << "Total: " << s << " elements in the list.\n";
        return ~(1 << 31);
    }

    return remove(d, first);
}

int List::remove(int idx, Node *pre) {
    // Base case: reach the previous of target node.
    // delete the next node and reconnect the link
    if (idx == 1) {
        Node *to_delete = pre->next;
        int val = to_delete->value;
        pre->next = to_delete->next;
        delete to_delete;
        s--;
        return val;
    } else
        // recurse to the right node and delete it
        return remove(--idx, pre->next);
}

void List::erase(int x) {
    // Drive for the recursive erase
    erase(x, first);
}

void List::erase(int x, Node *pre) {
    // Base case: pre node circles back to first.  Just return
    if (pre->next == first) return;
    
    // Recursively check the value of each node with the query x.
    // If they match, delete the node.
    if (pre->next->value == x) {
        Node *to_delete = pre->next;
        pre->next = to_delete->next;
        delete to_delete;
        s--;
        // Still recurse on the same "pre" node, becuase its next node has changed.
        erase(x, pre);
    } else
        // Recurse on pre->next, because we are certain that its next is not a match.
        erase(x, pre->next);
}

void List::print() {
    // if list is empty, print "no element in list"
    if (isEmpty()) {
        cout << "no element in list\n";
        return;
    }

    Node *runner = first->next;
    while (runner != first) {
        cout << runner->value << " ";
        runner = runner->next;
    }
    cout << endl;
}

void List::reverse() {
    // Driver for recursive reverse
    // The algorithm begins and ends with the same node(first), since the list is circular
    // So I use the boolean start to differentiate between the start and end of execution.
    reverse(first, first->next, true);
}

void List::reverse(Node *current, Node *rest, bool start) {
    // If start == true, this is just the beginning of recursion.
    // we just set start to false
    if (current == first && start) start = false;
    // Base case: if start == false, this is the end of recursion. return
    else if (current == first && !start) return;
    // Recurse to the end of the linked list
    reverse(rest, rest->next, start);
    // reverse the links one by one
    rest->next = current;
}

void List::concat(List &l2) {
    // Use this if remove(int d) is allowed.  
    // Base case: l2 is empty
    if (l2.isEmpty()) return;
    // Recursively add the first of l2 to the end of self.
    insert(l2.remove(1));
    concat(l2);
}

void List::concat2(List &l2) {
    // Use this if remove(int d) is not allowed.
    concat2(l2.first->next, l2.first);
}

void List::concat2(Node *current, Node *sentinel) { 
    // Base case: if current circles back to sentinel node, return.
    if (current == sentinel) return;
    // Recursively add current value to the self list.
    insert(current->value);
    concat2(current->next, sentinel);
}
