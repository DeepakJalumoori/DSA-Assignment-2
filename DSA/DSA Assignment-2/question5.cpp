class Node {
public:
    int val;
    Node* next;
    Node* back;
    
        Node(int x, Node* nextNode = nullptr, Node* backNode = nullptr) {
        val = x;
        next = nextNode;
        back = backNode;
    }
};

class MyLinkedList {
private:
    Node* head;
    Node* tail; 
    int size;

public:
    MyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->val;
    }

    void addAtHead(int val) {
        Node* newHead = new Node(val, head);
        if (head) {
            head->back = newHead;
        }
        head = newHead;
        if (size == 0) {
            tail = head;
        }
        ++size;
    }

    void addAtTail(int val) {
        if (size == 0) {
            addAtHead(val);
            return;
        }
        Node* newTail = new Node(val, nullptr, tail);
        tail->next = newTail;
        tail = newTail;
        ++size;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) {
            addAtHead(val);
            return;
        }
        if (index == size) {
            addAtTail(val);
            return;
        }
        Node* prev = head;
        for (int i = 1; i < index; ++i) {
            prev = prev->next;
        }
        Node* newNode = new Node(val, prev->next, prev);
        if (prev->next) {
            prev->next->back = newNode;
        }
        prev->next = newNode;
        ++size;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        Node* toDelete = head;
        for (int i = 0; i < index; ++i) {
            toDelete = toDelete->next;
        }
        if (toDelete->back) {
            toDelete->back->next = toDelete->next;
        }
        if (toDelete->next) {
            toDelete->next->back = toDelete->back;
        }
        if (toDelete == head) {
            head = toDelete->next;
        }
        if (toDelete == tail) {
            tail = toDelete->back;
        }
        delete toDelete;
        --size;
    }
};
