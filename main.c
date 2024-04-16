#include <stdio.h>
#include <stdlib.h>
#include "route-records.h"

int main( int argc, char *argv[] )
{
    /* 1. Declare variables here */
    
	char userOrigin[5];
	char userDest[5];
	char userAirline[5];


    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */

   char *inputFileName = argv[1];


   if (argc != 2){
	   printf("ERROR: Missing File\n");
	   return -1;
   }
   	 

    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */

    printf("Opening %s...\n", argv[1]);
    
    FILE* inputFile = NULL;
    inputFile = fopen(inputFileName, "r");
    

    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    
    if (inputFile == NULL){
	    printf("ERROR: Could not open file\n");
	    return -1;
    }


    // 5. Do the following to load the records into an array of RouteRecords
    	


    		/*5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
		*/
	RouteRecord* records = createRecords(inputFile);
	rewind(inputFile);
	
    		
    		/*5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ??? */
	
	int uniqueRoutes = fillRecords(records, inputFile);
	printf("Unique routes operated by airlines: %d\n", uniqueRoutes);

//	int i;
//	for (i = 0; i < uniqueRoutes; i++) {
//		printf("%s, %s, %s\n", records[i].origin, records[i].destination, records[i].airline);
//	}
    		


    //5.3 Close the the file.

    fclose(inputFile);
    printf("File closed.\n");

	/*
	int i;
	for (i = 0; i < 100; i++) {
		printf("%s, %s, %s\n", records[i].origin, records[i].destination, records[i].airline);
	}
	*/

    // 6. Create an infinite loop that will do the following:

    while (1){
 
    		//6.1 Call printMenu()


	printMenu();	


    		//6.2 Ask the user to input a value for the menu
	
    	int userNum = 0;
	printf("Enter your selection:");
	scanf("%d", &userNum);
	


    		//6.3 Handle the case in which a non-integer value is entered

	if ( (userNum > 5) || (userNum < 1) ){
		printf("\nInvalid choice.\n");
		continue;
	}

    	switch(userNum){


    		//6.4 Create a switch/case statement to handle all the menu option

	    	//6.4.1 Each option requires the user to enter a search key
    		

		case 1:

			printf("\nEnter origin:");
			scanf("%s", userOrigin);
			printf("\nEnter destination:");
			scanf("%s", userDest);
			printf("\nSearching by route...\n");

			searchRecords(records, uniqueRoutes, userOrigin, userDest, ROUTE);

			break;

		case 2:
		
			printf("\nEnter origin:");
			scanf("%s", userOrigin);
			printf("\nSearching by origin...\n");

			searchRecords(records, uniqueRoutes, userOrigin, userDest, ORIGIN);

			break;

		case 3:

			printf("Enter destination:");
			scanf("%s", userDest);
			printf("\nSearching by destination...\n");

			searchRecords(records, uniqueRoutes, userOrigin, userDest, DESTINATION);

			break;

		case 4:
			
			printf("Enter airline:");
			//I'm going to use key1 as the user airline for this case so I don't mess up the function prototype.
			scanf("%s", userAirline);
			printf("\nSearching by airline...\n");

			searchRecords(records, uniqueRoutes, userAirline, userDest, AIRLINE);

			break;
		
		case 5:

	    	//6.4.2 Quit needs to free the array
			
			printf("Good-bye! :>\n");
			free(records);
			return -1;
		
	    		
	}


    }


    return 0;

}
