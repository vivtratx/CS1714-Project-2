#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "route-records.h"

RouteRecord* createRecords(FILE* fileIn){


	//Creates the array of RouteRecord and initializes it

	RouteRecord *records;

	//Goes through the csv file and counts number of total records

	char buffer[100];
	int numRecords = 0;

	//Gets rid of header 
	fgets(buffer, 100, fileIn);

	//Counts num records
	while ( (fgets(buffer, 100, fileIn) != NULL) && !(feof(fileIn)) ){

			numRecords++;

	}

	//Dynamically allocate memory for an array of routerecord based on the count

	records = (RouteRecord*)malloc(numRecords * sizeof(RouteRecord));

	//Each routerecord struct object has an array of 9 integers to hold the number of passengers for nine months (initialize to 0)
	int i = 0;
	int j = 0;
	for (i = 0; i < numRecords; i++){
		for (j = 0; j < 9; j++){
			records[i].passengers[j] = 0;
		}
	}

	//Rewind the file pointer

	rewind(fileIn);

	//Return the pointer to the array dynamically allocated

	return records;

}

int fillRecords(RouteRecord* r, FILE* fileIn){

	//Will process data in the csv file, will go through each record and parse out the record and enter into the array

	char buffer[100];
	int recordCount = 0;

	//Get rid of header
	fgets(buffer, 100, fileIn);

	//Scans each line and parses the data
	while ( (fgets(buffer, 100, fileIn) != NULL) && !(feof(fileIn)) ){
	

		int currMonth = 0;
		char currOrigin[4];
		char currDest[4];
		char currAirline[4];
		int currPass = 0;
		sscanf(buffer, "%d,%[^,],%[^,],%[^,],%d", &currMonth, currOrigin, currDest, currAirline, &currPass);
		//printf("%d,%s,%s,%s,%d\n", currMonth, currOrigin, currDest, currAirline, currPass);

		if (strlen(currAirline) > 2){
			continue;
		}
		else{
			int foundIdx = (findAirlineRoute(r, recordCount, currOrigin, currDest, currAirline, 0));

			if (foundIdx ==  -1){ 

			
				strcpy(r[recordCount].origin, currOrigin);
				strcpy(r[recordCount].destination, currDest);
				strcpy(r[recordCount].airline, currAirline);
				r[recordCount].passengers[currMonth-1] = currPass;
				recordCount++;
			}	
			else{
				r[foundIdx].passengers[currMonth-1] += currPass;
			}
		}

	}

	return recordCount;
}

int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx ){


	//Base Case: If no match
	if ( curIdx >= length ){
		return -1;
	}

	//Look through array r and find a match

	if ( (strcmp(r[curIdx].origin, origin) == 0) && (strcmp(r[curIdx].destination, destination) == 0)&& (strcmp(r[curIdx].airline, airline) == 0)){
		return curIdx;
	}

	//Recursive Case: keep searching array
	else{
		return findAirlineRoute(r, length, origin, destination, airline, curIdx+1);
	}
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st){

	int i = 0;
	int j = 0;
	int numMatches = 0;
	int totalPassengers = 0;
	int avgPassengers = 0;
	int monthNum = 1;
	

	//Sets the array to have 0 passengers per month
	int totalPassPerMonth[9];
	for (i = 0; i < 9; i++){
		totalPassPerMonth[i] = 0;
	}



	//Switch statement to determine what the user wants to search for
	switch (st){

		case ROUTE:
			
			for (i = 0; i < length; i++){
				if ( (strcmp(r[i].origin, key1) == 0) && (strcmp(r[i].destination, key2) == 0) ){

					printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					numMatches++;

					for (j = 0; j < 9; j++){

						totalPassengers += r[i].passengers[j];
						totalPassPerMonth[j] += r[i].passengers[j];
						
					}
				}
			}


			printf("\n%d matches were found.\n", numMatches);

			printf("\nStatistics\n");
			printf("Total Passengers:\t%d\n", totalPassengers);
			

			//Sets the month to 1 and iterates through the passenger count per month :)
			monthNum = 1;
			for (i = 0; i < 9; i++){

				printf("Total Passengers in Month %d:\t%d\n", monthNum, totalPassPerMonth[i]);
				monthNum++;

			}
			
			avgPassengers = (totalPassengers / 9);
			printf("\nAverage Passengers per Month:\t%d\n", avgPassengers);


			break;

		case ORIGIN:

			for (i = 0; i < length; i++){

				if ( (strcmp(r[i].origin, key1) == 0) ){

					printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					numMatches++;

					for (j = 0; j < 9; j++){

						totalPassengers += r[i].passengers[j];
						totalPassPerMonth[j] += r[i].passengers[j];
						
					}
				}
			}

			printf("\n%d matches were found.\n", numMatches);
			printf("\nStatistics\n");
			printf("Total Passengers:\t%d\n", totalPassengers);
			
			monthNum = 1;
			for (i = 0; i < 9; i++){

				printf("Total Passengers in Month %d:\t%d\n", monthNum, totalPassPerMonth[i]);
				monthNum++;

			}
			
			avgPassengers = (totalPassengers / 9);
			printf("\nAverage Passengers per Month:\t%d\n", avgPassengers);

			break;

		case DESTINATION:

			for (i = 0; i < length; i++){
				if ( (strcmp(r[i].destination, key2) == 0) ){
					printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					numMatches++;
					for (j = 0; j < 9; j++){

						totalPassengers += r[i].passengers[j];
						totalPassPerMonth[j] += r[i].passengers[j];
						
					}
				}
			}

			printf("\n%d matches were found.\n", numMatches);
			printf("\nStatistics\n");
			printf("Total Passengers:\t%d\n", totalPassengers);
			
			monthNum = 1;
			for (i = 0; i < 9; i++){

				printf("Total Passengers in Month %d:\t%d\n", monthNum, totalPassPerMonth[i]);
				monthNum++;

			}
			
			avgPassengers = (totalPassengers / 9);
			printf("\nAverage Passengers per Month:\t%d\n", avgPassengers);
			break;

		case AIRLINE: //For this case I was just going to use key1 as my search key for the airline

			for (i = 0; i < length; i++){
				if ( (strcmp(r[i].airline, key1) == 0) ){
					printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
					numMatches++;
					for (j = 0; j < 9; j++){

						totalPassengers += r[i].passengers[j];
						totalPassPerMonth[j] += r[i].passengers[j];
						
					}
				}
			}
			printf("\n%d matches were found.\n", numMatches);
			printf("\nStatistics\n");
			printf("Total Passengers:\t%d\n", totalPassengers);
			
			monthNum = 1;
			for (i = 0; i < 9; i++){

				printf("Total Passengers in Month %d:\t%d\n", monthNum, totalPassPerMonth[i]);
				monthNum++;

			}
			
			avgPassengers = (totalPassengers / 9);
			printf("\nAverage Passengers per Month:\t%d\n", avgPassengers);
			break;

	}
		
}


//PRINT FUNCTION
void printMenu(){

	printf( "\n\n######### Airline Route Records Database MENU #########\n" );
	printf( "1. Search by Route\n" );
	printf( "2. Search by Origin Airport\n" );
	printf( "3. Search by Destination Airport\n" );
	printf( "4. Search by Airline\n" );
	printf( "5. Quit\n" );

}






