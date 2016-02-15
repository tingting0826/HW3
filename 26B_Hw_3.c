/*********************************************************************************
CIS 26B - Advanced C Programming
Homework #3
********************************************************************************
Name: Tingting Wang

IDE: Visual Studio

Date: 2/11/2016

Program concept: binary file read, search and write. Hash to binary file. 
advanced string function. Error checking. 
********************************************************************************
Here are the #defines and main program for the program which you will write:
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// get rid of system warnings
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning(disable:4996)

#define MAXLINE    512
#define BUCKETS    100
#define BUCKETSIZE 240
#define RECORDSIZE 60
#define CITYMAX    49
#define RECS_PER_BUCKET 4
#define MAXSELECTION 32
#define MAXFILENAME 32
#define BLANK    -1
#define BADLINE  -2
#define GOODADD  -3
#define BADFILE  -4
#define NOTFOUND -5
#define FOUND    -6
#define ADD       1
#define LOOKUP    2
#define QUIT      3

typedef struct
{
	char city[CITYMAX];
	char state[32];
	int highestNum;
	int lowestNum;
}Weather;

int main()
{
    FILE *openWeatherFile(char* fileName);
	int caseOneCheck(char* option);
    int addRecordsToDB(FILE *fp);
    int lookupRecord(FILE *fp);
    int menu(void);
	void hashFile(FILE* fp);
    
    FILE *fp;
    int result, option;
    
    fp = openWeatherFile();
    while ((option = menu()) != QUIT)
    {
        switch (option)
        {
            case BLANK:
            case BADLINE: continue;
            case ADD:
				while ((result = addRecordsToDB(fp)) == BADLINE
					|| result == BADFILE);
                break;
            case LOOKUP:
                while ((result = lookupRecord(fp)) == BADLINE
                       || result == NOTFOUND);
        }
    }
}

/*********************************************************************
** This function will prompt the user, get user's input and return the
   number of the option accordingly. 
*********************************************************************/
int menu(void)
{
	// prompt string
	printf("1. Add records to database.\n2. Look up a record in the database.\n3. Quit.\nEnter selection : ");
	char option[MAXSELECTION];
	gets(option);
	if (option[0] == '\0')
	{
		return BLANK;
	}
	else if (strlen(option) == 1)
	{
		return caseOneCheck(option);
	}
	else
	{
		// enter a longer string(other than one number), return BADLINE
		printf("Legal entry has one menu selection only.\n");
		return BADLINE;
	}
}

/*********************************************************************
** This function will varify when user enter one number or character,
   It will print and return proper optioin results.
*********************************************************************/
int caseOneCheck(char* option)
{
	switch (option[0])
	{
	case '1':
		return ADD;
		break;
	case '2':
		return LOOKUP;
		break;
	case '3':
		return QUIT;
		break;
	default:
		printf("Illegal menu selection!  Try again!\n");
		return BADLINE;
	};
}


/*********************************************************************
** This function will open the weather file if the file is valid. 
   If not, print proper message. 
*********************************************************************/
FILE *openWeatherFile(char* fileName)
{

}

/*********************************************************************
** This function will add weather record into binary file.
   False adding weather will be terminated and proper messages will be 
   printed. Adding result will be returned as a number(BADLINE, GOODADD,
   BADFILE).
*********************************************************************/
int addRecordsToDB(FILE *fp)
{
	// prompt the user to enter name of the file
	printf("Enter file name: ");
	char fileName[MAXFILENAME];
	gets(fileName);
	// enter nothing, return BLANK
	if (fileName[0] == '\0')
	{
		return BLANK;
	}
	// file name format check
	// open file
	if ((fp = openWeatherFile(fileName)) == NULL)
	{
		printf("Batch insertion file could not be opened!\n");
		return BADFILE;
	}
	// input string's according file not valid, return BADLINE "Batch insertion file could not be opened!"
	// hash
	hashFile(fp);
	// inout file open successfully, but bucket overflow, return BADFILE, "Bucket overflow! Record for INPUT,INPUT rejected!"
	// file valid, good file, check if the record is duplicate, print no duplicate message
	// return GOODADD
	// close file
}

/*********************************************************************
** This function will look up the input city's record.
   It will print out record of the in file city. False
   search will result marning messages. Searching result 
   will be returned as a number(FOUND, NOTFOUND, BADLINE)
*********************************************************************/
int lookupRecord(FILE *fp)
{
	// CITY, STATE. found
	// CITY, STATE, NOTFOUND, return
	//   ,    missing city(as long as the fist is empty), RETURN BADLINE
	// some,     missing state, return BADLINE

}

void hashFile(FILE* fp)
{
	char record[61];
	int i;

	fp = fopen("weather", "w");

	for (i = 0; i < 59; i++) record[i] = ' ';
	record[59] = '\n';
	record[60] = '\0';

	for (i = 0; i < 400; i++) fprintf(fp, "%s", record);
}
/**
You can see that you are adding or looking up records in a HASHED FILE. 
When adding records, the addRecordsToDB function will prompt a user for
a filename which has records that look like this:

ALBUQUERQUE,NEW MEXICO,96,65
RENO,NEVADA,90,50
LAS VEGAS,NEVADA,109,83
PHOENIX,ARIZONA,108,88
SAN FRANCISCO,CALIFORNIA,68,55
SAN JOSE,CALIFORNIA,80,56
DEATH VALLEY,CALIFORNIA,117,90
SEATTLE,WASHINGTON,77,55
PORTLAND,OREGON,86,56
MINOT,NORTH DAKOTA,86,54
PIERRE,SOUTH DAKOTA,90,56
RAPID CITY,SOUTH DAKOTA,88,62
MULE SHOE,WEST VIRGINIA,86,66
PHILADELPHIA,PENNSYLVANIA,87,71
DALLAS,TEXAS,97,72
SALLAD,TEXAS,98,78
DALLSA,TEXAS,76,46
SALDAL,TEXAS,88,65
ASDALL,TEXAS,99,77

You will do batch insertions into the hashed file.  Treat overflows in a
bucket as an unresolvable problem but report the error.  Obviously, the
hash key is state + city and you should sum the cube of the ASCII values
of the characters making up the city/state before modding by 100 to find
the bucket to put the record.  Empty response in a prompt given on choices
1 or 2 should cause program to redeliver the main menu.

On lookups, the user should enter state, city with any amount of whitespace
around the two tokens.  Obviously it is a MAJOR task to parse, case, and
space the requested city/state so that it agrees with your format in the
hashed file.  Don't worry about the characters they enter for the city
and state.  Just give a "Not Found" type of error if they enter something
that is obviously crazy.

//********************************************
//********************************************
//********************************************
Your code to create the empty hashed file is:
//********************************************
 
#include <stdio.h>
int main()
{
    FILE *fp;
    char record[61];
    int i;
    
    fp = fopen("weather", "w");
    
    for (i = 0; i < 59; i++) record[i] = ' ';
    record[59] = '\n';
    record[60] = '\0';
    
    for (i = 0; i < 400; i++) fprintf(fp, "%s", record);
}


You must follow ALL the rules for good token parsing!!
Run the program at least twice. An example is given below.
Duplicate city/state not allowed!!!
//********************************************
//**** EXAMPLE *******************************
//********************************************
1. Add records to database.
2. Look up a record in the database.
3. Quit.
Enter selection:

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:    4
Illegal menu selection!  Try again!
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:   2 foo
Legal entry has one menu selection only!
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:   1

Enter filename:    foobar.foobar
Batch insertion file could not be opened!

Enter filename:
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 1

Enter filename:    asg3.txt
Bucket overflow! Record for ASDALL,TEXAS rejected!

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:   2
Enter city,state:   sALLad  ,   tExAs
Found record: SALLAD,TEXAS                                     98   78

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city,state:   foobar  ,  New  Mexico
Record for FOOBAR,NEW MEXICO                                 not found!

Enter city,state: whatever
Missing state!!  Try again!

Enter city,state:    alBUquerQUE ,  nEW  MexICO
Found record: ALBUQUERQUE,NEW MEXICO                           96   65

1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:    3
$

//********************************************
//***  New session to test lookup line errors
//********************************************
 
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city,state:    foobar   ,
Missing state!!  Try again!

Enter city,state:     ,
Missing city!!  Try again!
Enter city,state:    ,  foobar

Missing city!!  Try again!

Enter selection:   1

Enter filename:   asg3o2.txt
Duplicate record entry not allowed for RENO,NEVADA!
Duplicate record entry not allowed for LAS VEGAS,NEVADA!
Duplicate record entry not allowed for MINOT,NORTH DAKOTA!
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection:   2
Enter city,state:  faRBer  , monTANA
Found record: FARBER,MONTANA                                   85   45


1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 2
Enter city,state:    farBER ,, monTANA
Illegal extra token on line!  Try again!

Enter city,state:
1. Add records to database.
2. Look up a record in the database.
3. Quit.

Enter selection: 3
*/