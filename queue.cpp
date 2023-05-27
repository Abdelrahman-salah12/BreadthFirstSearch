#include <iostream> 
#include "queue.h"
using namespace std;



Node* front = NULL;
Node* rear = NULL;
Node* temp = NULL;


void Enqueue(string val) {

	if (rear == NULL) {
		rear = new Node();
		rear->data = val;
		rear->next = NULL;
		front = rear;
	}
	else {
		temp = new Node();
		temp->data = val;
		temp->next = NULL;
		rear->next = temp;
		rear = temp;
	}
}

string dequeue() {
	// tempororary storage to return front->data
	string dequeuedData;

	if (front == NULL) {
		cout << "stack underflow\n";
		return "";
	}
	else if (front->next != NULL) {
		// if next value exist make it front
		temp = front->next;
		dequeuedData = front->data;
		cout << front->data << " has been dequeued\n";
		free(front);
		front = temp;
		return dequeuedData;
	}
	else {
		temp = new Node();
		temp->data = front->data;
		cout << front->data << " has been dequeued\n";
		free(front);
		front = NULL;
		rear = NULL;
		return temp->data;
	}
}

int length() {
	int length = 0;

	temp = front; // to loop from front to end
	if (front == NULL) {
		cout << "queue is empty\n";
		return 0;
	}
	while (temp != NULL) {
		length++;
		temp = temp->next;
	}
	return length;
}

void display() {
	temp = front; // to loop from front to end
	if (front == NULL) {
		cout << "queue is empty\n";
		return;
	}
	while (temp != NULL) {
		cout << temp->data << endl;
		temp = temp->next;
	}


}
