#pragma once

#include <iostream> 
using namespace std;


struct Node {

	string data;
	Node* next;
};


void Enqueue(string val);

string dequeue();

void display();

int length();

