//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include <set>
#include <string.h>
#include "slist.h"

using namespace std;

void simpleSortTotal(AirportList* linkedList);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

double austinLat = 30.1944;
double austinLong = 97.6700;

int main()
{
    ifstream infile;
    int i=0;
    char cNum[10] ;
    AirportList* list = new AirportList();
    int   airportCount;
    
    infile.open ("./USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
			int   c=0;
			while (infile.good())
			{
				Airport airport;
				infile.getline(airport.code, 256, ',');
				infile.getline(cNum, 256, ',');
				airport.latitude = atof(cNum);
				infile.getline(cNum, 256, '\n');
				airport.longitude = atof(cNum);
				list->add(airport);
				if (!(c % 1000)) {
					cout << airport.code << " long: " << airport.longitude << " lat: " << airport.latitude <<  endl;
				}
				i++;
				c++;
			}
			airportCount = c-1;
			infile.close();
			c = 0;

			Node* current = list->head;
			while(current){
				if (!(c % 1000)) {
					cout << current->airport.code << " long: " << current->airport.longitude << " lat: " << current->airport.latitude <<  endl;
					cout << current->next->airport.code << " long: " << current->next->airport.longitude << " lat: " << current->next->airport.latitude <<  endl;
					cout <<"Distance between " << current->airport.code << " and " << current->next->airport.code << " is "
					<< distanceEarth( current->airport.longitude, current->airport.latitude , current->next->airport.longitude, current->next->airport.latitude) << endl;
				}
				c++;
				current = current->next;
			}
			simpleSortTotal(list);
			current = list->head;
			Node* justBefore;
			while(current) {
				justBefore = current;
				current = current->next;
			}
			double dist = distanceEarth(austinLat, austinLong, justBefore->airport.latitude, justBefore->airport.longitude);
			cout << "The farther airport from AUS is " << justBefore->airport.code << " with a latitude of " << justBefore->airport.latitude << ", a longitude of " << justBefore->airport.longitude << ", and a distance from AUS of " << dist << endl;
			int under100Index = 0;
			current = list->head->next;
			while(current) {
				double currentDist = distanceEarth(austinLat, austinLong, current->airport.latitude, current->airport.longitude);
				if(currentDist >= 100){
					break;
				}
				else {
					under100Index++;
					current = current->next;
				}
			}
			cout << "Here is a list of all airports withing 100 miles of AUS: " << endl;
			cout << list->subList(0, under100Index).toString() << endl;

    }
    else
    {
        cout << "Error opening file";
    }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void simpleSortTotal(AirportList* linkedList)
{
	Node* current = linkedList->head;
	int minIndex;
	int findIndexCounter;
	Node* findIndex;
	double smallDist;
	double currentDist;
	for(int i = 1; i < linkedList->length-1; i++) {
		Airport insert;
		int countUp = 1;
		current = linkedList->head->next;;
		while(countUp < i) {
			current = current->next;
			countUp++;
		}
		findIndex = current->next;
		findIndexCounter = i+1;
		minIndex = i;
		double constDist = distanceEarth(austinLat, austinLong, current->airport.latitude, current->airport.longitude);
		smallDist = distanceEarth(austinLat, austinLong, current->airport.latitude, current->airport.longitude);
		while(findIndex) {
			currentDist = distanceEarth(austinLat, austinLong, findIndex->airport.latitude, findIndex->airport.longitude);
			if(currentDist < smallDist) {
				smallDist = currentDist;
				minIndex = findIndexCounter;
			}
			findIndexCounter++;
			findIndex = findIndex->next;
		}
		linkedList->exchg(i, minIndex);
		if(i%750==0)
			cout << endl << "Hold on, still sorting..." << endl;
	}
	cout << endl << "LINKED LIST SORTED" << endl;
}