/*
* Module : IPC between threads using Linked List implementation of Queues - MAIN.CPP
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

// -------------- Macros --------------
#define _CRT_SECURE_NO_DEPRECATE // To avoid fprint error in VS 2015
#define TASK1BEGINS // Makes the TASK1 to start sending data to queue
//#define TASK2BEGINS //// Makes the TASK1 to start sending data to queue
// -------------- Headers --------------
#include <iostream>
#include <thread>
#include <chrono>         
#include <string>
#include "node.h"
#include "queue.h"
using namespace std;
using namespace this_thread;
// -------------- Global variables --------------
int QUEUE_SIZE = 5;

// -------------- Enqueue data to the queue one by one --------------
void SendToQueue(queue<string> *q, string data)
{
	q->set_access_flag();
	// ---------- Enqueue elements till queue size is reached ----------	
	if (q->data_count() < QUEUE_SIZE)
	{
		q->Enqueue(data);
	}
	else
	{
		cout << "\n Queue is full. Try again later......";
	}
	// ---------- Release the access to the queue port ----------
	q->release_access_flag();
}
// -------------- Dequeue data from the queue one by one --------------
string ReceiveFromQueue(queue<string> *q)
{
	string queue_data = "";
	string received_data = "";	
	// ---------- Dequeue elements from the queue ----------
	
		queue_data = q->Dequeue();
		//cout << "\n QUEUE : " << queue_data;
		received_data = received_data + "|\""+ queue_data + "\"|" ;
		
	// ---------- Return the dequeued data ----------
	return received_data;
}
// -------------- Task1 sends the temperature sensor readings to the queue --------------
void Task1(queue<string> *q)
{	
#ifdef TASK1BEGINS
	q->set_access_flag();
#endif
#ifdef TASK2BEGINS
	sleep_for(chrono::milliseconds(20));
#endif
	// ---------- Task1 begins first ----------
	string temp_sensor = "24'C";
	cout << "\n Task1 sending data to queue......";
	SendToQueue(q, temp_sensor);

}
// -------------- Task2 sends the light sensor reading to the queue --------------
void Task2(queue<string> *q)
{	
	// ---------- Task2 follows Task1 -> Check for status of port ----------
	string light_sensor = "3020";	
	while (q->status() != 0);
	cout << "\n Task2 sending data to queue......";
	SendToQueue(q, light_sensor);
}
// -------------- Task3 logs the values reads from the queue --------------
void Task3(queue<string> *q)
{
	FILE * fp = fopen("C:\\Kannan\\C++\\C++ Projects\\Sensor_values.txt", "w+");
	string data_read = "";
	string first = "";
	fprintf(fp, "------ FIFO QUEUE ------\nFirst element on the right side\n\n");
	int i = 0;
	while (i<QUEUE_SIZE)
	{
		sleep_for(chrono::milliseconds(10));
		// ---------- Check for the availability of the queue port ----------
		while (q->status() != 0);
		if (q->data_count() != 0)
		{
			cout << "\n Task3 receiving data from queue......";
			data_read = ReceiveFromQueue(q);
			first = data_read + first;						
		}
		i++;		
	}
	fprintf(fp, "%s", first.c_str());
	fclose(fp);
	
	cout << "\n DATA READ FROM QUEUE IS STORED IN \"SENSOR_VALUES.TXT\"...... " << endl;
}

// -------------- Create an instance of Queue and register the threads --------------
void main()
{
	cout << "\n ------- IPC BETWEEN THREADS USING LINKED LIST IMPLEMENTATION OF QUEUES -------";
	cout << "\n                   Copyright (c) 2015, Krishnaswamy Kannan \n";
	// ---------- Create a queue that can store 5 elements ----------
	queue<string> *q = new queue<string>(); 
	// ---------- Create three threads -> 2 senders & 1 receiver ----------
	thread sender1(Task1,q);
	thread sender2(Task2, q);
	thread receiver(Task3,q);
	sender1.join();
	sender2.join();
	receiver.join();
}
