/**
 * Description: The logging mechanism provides functionality such as clearing, adding a log message, getlog, and savelog. 
 * This is utilized via the main function which uses getopt and perror to parse the command line for arguments and calls every logging function at least twice.
 * The error message format is executable : time in nanoseconds since epoch : error message. 
 *
 *  Author: $Author: o3-klamert $
 *  Date: $Date: 2016/09/18 18:45:34 $
 *  Log: $Log: main.cpp,v $
 *  Log: Revision 1.7  2016/09/18 18:45:34  o3-klamert
 *  Log: Revised the comments and changed the default log file to be named logfile.txt.
 *  Log:
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include "loglib.h"
#include "loglib.cpp"
using namespace std;

#define DEBUG false

bool parseCommandLine(int, char**);
void usage();
void usage2();
timespec getTimeSinceEpoch();
string buildMessageFormat(char**, string);


bool parseCommandLine(int argc, char** argv)
{
	char c;
	
	bool nflag = false;

	while ((c = getopt(argc, argv, ":hn:l:")) != -1)
	{
		switch (c)
		{

			case 'h':
			{
                 if(DEBUG == true){
                 cout << "Inside of case: h \n"; 
                 }
                 cout << "-----------------------------------------------------------------------\n";
                 cout << "Instructions:\n";
                 cout << "-----------------------------------------------------------------------\n";
				 usage2();
				 break;
			}
			
			case 'l':
			{
                 if(DEBUG == true){
                 cout << "Inside of case: l \n";
                 cout << "OPTARG: ";
                 cout << optarg << "\n"; 
                 }
                 cout << "-----------------------------------------------------------------------\n";
                 cout << "Saving Log: " << optarg << "\n";
                 cout << "-----------------------------------------------------------------------\n";
				 savelog(optarg);
				 break;
			}
			
			case 'n':
			{
                 if(DEBUG == true){
                 cout << "Inside of case: n \n";
                 cout << "OPTARG: ";
                 cout << atoi(optarg) << "\n";
                 cout << "nflag: " << nflag << "\n"; 
                 }
                 
                 int x = 42;
                 nflag = true;
                 string logString = "The value of x is ";
                 char* cstring;
                 logString.append((const char*)optarg);
                 logString.append(".");

                 x = atoi(optarg);
                 
                 cstring =(char*) buildMessageFormat(argv,logString).c_str();

                struct data_t* logMessage = reinterpret_cast<data_t*>(malloc( sizeof(struct data_t))); 
               
                logMessage->string = cstring;
                time_t timestamp = time(0);
                logMessage->time = timestamp;
                
                addmsg(*logMessage);
                
			    break;
			}
			
			default:
                 if(DEBUG == true){
                 cout << "Inside of case: default \n";
                 }
                 errno = EINVAL;
                 cout << "The flag argument did not match the approved flags.\n";
                 usage2();
                 return -1;
                 break;
                 
			
		}
	}
	return nflag;
}

/**
 * Description: function that returns the time in nanoseconds from the epoch time.
 * 
 * Author: Jason Klamert
 * Date: 9/6/2016
 */
timespec getTimeSinceEpoch(){
       
       struct timespec ts;
       clock_gettime(CLOCK_REALTIME, &ts);
       
       return ts;
}
 
 /**
 * Description: function that prints the proper usage of the routine.
 * Author: Jason Klamert
 * Date: 9/6/2016
 */
void usage(){
     perror("Previous unrecognized argument. Please retry the program.\nUse the format logger [-h, -help, -n integer, or -l fileName] \n");
}  

 /**
 * Description: function that prints the proper usage of the routine.
 * Author: Jason Klamert
 * Date: 9/6/2016
 */
void usage2(){
     cout << "Usage format: main [-h, -help, -n integer, or -l fileName] \n";
} 


 /**
 * Description: function that prints the proper usage of the routine.
 * Author: Jason Klamert
 * Date: 9/6/2016
 */
string buildMessageFormat(char** argv, string error){
     struct timespec tm = getTimeSinceEpoch();
     //convert s to ns and add the actual counted ns for precision.
     unsigned long long ms = tm.tv_sec * 1000;
     unsigned long long us = ms * 1000;
     unsigned long long ns = us * 1000;
     ns += tm.tv_nsec;
     
     char nano [5000000];
     sprintf(nano,"%.9ld",ns);
     
     string str;
     str.append(*argv);
     str.append(" : ");
     str.append(nano);
     str.append("nsec");
     str.append(" : ");
     str.append(strerror(errno));
     str.append(" : ");
     str.append(error);
     str.append(".\n");
     
     return str;
}



/**
 * Description: Routine to use every function of the logging utility at least twice.
 * This parses the commandline for flags regarding the functions to trigger.
 * Author: Jason Klamert
 * Date: 9/6/2016
 */
int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int x = 42;
	bool nflag = false;
	char standard[20] = "logfile";
	
          char* message = "stupid message";
          struct data_t* logMessage = reinterpret_cast<data_t*>(malloc( sizeof(struct data_t))); 
               
                logMessage->string = message;
                time_t timestamp = time(0);
                logMessage->time = timestamp;
                cout << "-----------------------------------------------------------------------\n";
                cout << "Adding Log String: " << message << "\n";
                cout << "-----------------------------------------------------------------------\n";
                addmsg(*logMessage);
    
                 char* s = getlog();
                  
                 cout << "-----------------------------------------------------------------------\n";
                 cout << "Getting Log String:\n";
                 cout << "-----------------------------------------------------------------------\n";
                 if(s != NULL)
				 cout << s << "\n";
				 else
				 cout << buildMessageFormat(argv,s);
				 
				 cout << "-----------------------------------------------------------------------\n";
                 cout << "Saving Log:\n";
                 cout << "-----------------------------------------------------------------------\n";
				 savelog(standard);
				 
				 cout << "-----------------------------------------------------------------------\n";
                 cout << "Clearing Log:\n";
                 cout << "-----------------------------------------------------------------------\n";
				 clearlog();
				 
				 
				 
                 		 
	                nflag = parseCommandLine(argc,argv);
    
                    if(nflag == false){
                    string logString = "The value of x is ";
                    char result[500];
                    char* cstring;
                    if(sprintf(result,"%d",x) < 0)
                    perror("Error: sprintf alloc failure.");
                    logString.append(result);
                    logString.append(".");
                 
                    cstring = (char*)logString.c_str();

                    struct data_t* logMessage = reinterpret_cast<data_t*>(malloc( sizeof(struct data_t))); 
               
                    logMessage->string = cstring;
                    time_t timestamp = time(0);
                    logMessage->time = timestamp;
                
                    cout << "-----------------------------------------------------------------------\n";
                    cout << "Adding Log String: " << logMessage->string << "\n";
                    cout << "-----------------------------------------------------------------------\n";
                    addmsg(*logMessage);
                    char* s = getlog();
                    if(s != NULL)
				    cout << s << "\n";
				    else
				    cout << buildMessageFormat(argv,"Log is empty");
				    
   				    cout << "-----------------------------------------------------------------------\n";
                    cout << "Saving Log:\n";
                    cout << "-----------------------------------------------------------------------\n";
				    savelog(standard);
				 
				    free(logMessage);
             }
             
                 cout << "-----------------------------------------------------------------------\n";
                 cout << "Clearing Log:\n";
                 cout << "-----------------------------------------------------------------------\n";
				 clearlog();
       
	return(0);
}

            
   

       
