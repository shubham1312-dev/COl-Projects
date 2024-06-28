#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class MyDate
{
public:
    int month;
    int year;

    MyDate(int m = 0, int y = 0) : month(m), year(y) {}
};

class BookData
{
public:
    bool BorrowedStatus;
    int BorrowedByUserID;
    int ISBN;
    string Publisher;
    string Author;
    MyDate DateOfReturn;

    BookData(bool status = false, int userID = -1, int isbn = 0, string publisher = "", string author = "", MyDate date = MyDate())
        : BorrowedStatus(status), BorrowedByUserID(userID), ISBN(isbn), Publisher(publisher), Author(author), DateOfReturn(date) {}
};

template <typename T>
class Node
{
public:
    T data;
    Node *previous;
    Node *next;

    Node(T d) : data(d), previous(nullptr), next(nullptr) {}
};

class RequestData
{
public:
    int ISBN;
    int UserID;
    MyDate RequestDate;

    RequestData(int isbn = 0, int userID = 0, MyDate date = MyDate()) : ISBN(isbn), UserID(userID), RequestDate(date) {}

    string toString()
    {
        return "ISBN: " + to_string(ISBN) + ", UserID: " + to_string(UserID) + ", RequestDate: " + to_string(RequestDate.month) + "/" + to_string(RequestDate.year);
    }
};

class Response
{
public:
    int WaitingTime;
    bool Available;
    int PositionInQueue;

    Response(int time = 0, bool available = false, int position = 0) : WaitingTime(time), Available(available), PositionInQueue(position) {}
};

class UserData
{
public:
    int UserID;
    string Name;
    string Address;
    int Age;

    UserData(int userID = 0, string name = "", string address = "", int age = 0) : UserID(userID), Name(name), Address(address), Age(age) {}
};

class RequestQueue
{
private:
    Node<RequestData> *front;
    Node<RequestData> *back;
    int length;

public:
    RequestQueue() : front(nullptr), back(nullptr), length(0) {}

    int getLength()
    {
        return length;
    }

    void push(int ISBN, int UserID)
    {
        MyDate date;
        RequestData request(ISBN, UserID, date);
        Node<RequestData> *newNode = new Node<RequestData>(request);
        if (back)
        {
            back->next = newNode;
            newNode->previous = back;
        }
        else
        {
            front = newNode;
        }
        back = newNode;
        length++;
    }

    void pop()
    {
        if (front)
        {
            Node<RequestData> *temp = front;
            front = front->next;
            if (front)
            {
                front->previous = nullptr;
            }
            else
            {
                back = nullptr;
            }
            delete temp;
            length--;
        }
    }

    RequestData getFront()
    {
        if (front)
        {
            return front->data;
        }
        return RequestData();
    }

    string toString()
    {
        string result = "Length: " + to_string(length) + "\n";
        Node<RequestData> *curr = front;
        while (curr)
        {
            result += curr->data.toString() + "\n";
            curr = curr->next;
        }
        return result;
    }
};

class PendingRequests
{
private:
    int length;
    Node<RequestData> *front;
    Node<RequestData> *back;

public:
    PendingRequests() : length(0), front(nullptr), back(nullptr) {}

    bool insert(Node<RequestData> *insnode)
    {
        if (!insnode)
            return false;
        if (back)
        {
            back->next = insnode;
            insnode->previous = back;
        }
        else
        {
            front = insnode;
        }
        back = insnode;
        length++;
        return true;
    }

    bool deleteNode(Node<RequestData> *delnode)
    {
        if (!delnode)
            return false;
        if (delnode->previous)
        {
            delnode->previous->next = delnode->next;
        }
        else
        {
            front = delnode->next;
        }
        if (delnode->next)
        {
            delnode->next->previous = delnode->previous;
        }
        else
        {
            back = delnode->previous;
        }
        delete delnode;
        length--;
        return true;
    }

    Node<RequestData> *find(int ISBN)
    {
        Node<RequestData> *curr = front;
        while (curr)
        {
            if (curr->data.ISBN == ISBN)
            {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    string toString()
    {
        string result = "Length: " + to_string(length) + "\n";
        Node<RequestData> *curr = front;
        while (curr)
        {
            result += curr->data.toString() + "\n";
            curr = curr->next;
        }
        return result;
    }
};

class LibraryStorage
{
private:
    unordered_map<int, BookData> storage;
    RequestQueue rqQueue;
    PendingRequests prLinkedList;

public:
    LibraryStorage() {}

    void push(int ISBN, int UserID)
    {
        rqQueue.push(ISBN, UserID);
    }

    string rqQueueToString()
    {
        return rqQueue.toString();
    }

    string prLinkedListToString()
    {
        return prLinkedList.toString();
    }

    bool processQueue()
    {
        if (rqQueue.getLength() == 0)
            return false;
        RequestData frontRequest = rqQueue.getFront();
        int ISBN = frontRequest.ISBN;

        if (storage.find(ISBN) != storage.end())
        {
            BookData &book = storage[ISBN];
            if (!book.BorrowedStatus)
            {
                book.BorrowedStatus = true;
                book.BorrowedByUserID = frontRequest.UserID;
                book.DateOfReturn = MyDate(frontRequest.RequestDate.month + 1, frontRequest.RequestDate.year);
                rqQueue.pop();
                return true;
            }
        }
        prLinkedList.insert(new Node<RequestData>(frontRequest));
        rqQueue.pop();
        return false;
    }

    bool processReturn(BookData book)
    {
        Node<RequestData> *pendingRequest = prLinkedList.find(book.ISBN);
        if (pendingRequest)
        {
            book.BorrowedStatus = true;
            book.BorrowedByUserID = pendingRequest->data.UserID;
            book.DateOfReturn = MyDate(pendingRequest->data.RequestDate.month + 1, pendingRequest->data.RequestDate.year);
            prLinkedList.deleteNode(pendingRequest);
            return true;
        }
        book.BorrowedStatus = false;
        book.BorrowedByUserID = -1;
        return false;
    }
};

int main()
{
    LibraryStorage library;

    library.push(1234, 1);
    library.push(5678, 2);
    library.push(1234, 3);

    cout << "Request Queue:\n"
         << library.rqQueueToString();
    cout << "Pending Requests:\n"
         << library.prLinkedListToString();

    library.processQueue();

    cout << "After processing one request:\n";
    cout << "Request Queue:\n"
         << library.rqQueueToString();
    cout << "Pending Requests:\n"
         << library.prLinkedListToString();

    return 0;
}
