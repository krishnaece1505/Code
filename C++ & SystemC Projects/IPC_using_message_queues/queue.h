/*
* Module : Linked List implementation of Queues - QUEUE.H
*
* Author : Krishnaswamy Kannan
*
* Copyright (c) 2015, Krishnaswamy Kannan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of Redis nor the names of its contributors may be used
*     to endorse or promote products derived from this software without
*     specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#include <iostream>
#include "node.h"
using namespace std;
// -------------- Template class that implements the Queue data structure --------------
template <class T>
class queue
{
private:
	// ---------- Points to the first element in the queue ----------
	node<T> *first; 
	// ---------- Points to the last element in the queue ----------
	node<T> *last;
	// ---------- Gives the numbe of elements stored in the queue ----------
	int element_count;
	// ---------- Gives the status of the single I/O port of the queue ----------
	int access_flag = 0;

public:
	// -------------- Constructor that intializes the queue elements & its size --------------
	queue()
	{
		first = NULL;
		last = NULL;
	}
	// -------------- Stores the incoming data into the queue --------------
	void Enqueue(T element)
	{
		// Create a new node
		node<T> *tmp = new node<T>();
		tmp->data = element;
		tmp->next = NULL;

		if (first == NULL) {
			cout << "\n Queue is empty. Enqueuing data......";
			// ---------- Add the first element to the queue ----------
			first = last = tmp;
		}
		else {
			// ---------- Add the element to the end of the queue ----------		
			last->next = tmp;
			// ---------- Make the last element point to the incoming data ----------	
			last = tmp;
			
		}		
		element_count++;	
	}
	// -------------- Removes an element from the queue --------------
	T Dequeue()
	{
		if (first == NULL)
			cout << "\n Queue is empty. Dequeuing data......";
		// ---------- Store the data of the first element ----------
		T ret = first->data;
		node<T> *tmp = first;

		// ---------- Move the first pointer to next node ----------
		first = first->next;
		// ---------- Remove the first element from the queue ----------
		element_count--;
		delete tmp;
		// ---------- Return the first element of the queue ----------
		return ret;
	}
	// -------------------------- Mutator methods --------------------------
	// -------------- Returns the number of elements filled in the queue --------------
	int data_count()
	{		
		return element_count;
	}
	// -------------- Returns the status of the availability of the port --------------
	int status()
	{
		return access_flag;
	}
	// -------------- Sets the port to be available --------------
	void release_access_flag()
	{
		access_flag = 0;
	}

	// -------------- Sets the port to be occupied --------------
	void set_access_flag()
	{
		access_flag = 1;
	}
		
};

