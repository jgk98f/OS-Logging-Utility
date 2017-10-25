#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <errno.h>
#include "loglib.h"
using namespace std;
        
        static log_t* headptr = NULL;
        static log_t* tailptr = NULL;
        
        /*addmsg traverses a linked list and adds a log data entry to the end of the list.*/
    int addmsg(data_t data){
            log_t* copy = headptr;
            bool status = true;
            log_t* temp;

                 struct log_t* newnode = reinterpret_cast<log_t*>(malloc( sizeof(struct log_t) + sizeof(struct data_t) +  strlen(data.string)+1));

                 if (newnode == NULL){
                            errno = ENOMEM;
                            perror("Error: addmsg unsuccessful.\n");
                            return -1;
                  }
                  
               newnode->item.time = data.time;
               
               newnode->item.string = data.string;
               newnode->next = NULL;
               
               if (headptr == NULL){
                  headptr = newnode;
                  
                        }
               else {
                        while(copy->next != NULL)
                        {
                                   temp = copy;
                                   copy = copy->next;
                        }
                        
                        copy->next = newnode;
                        tailptr = newnode;
               
                    }                      
                    
            //If write to log was successful, return 0.
            printf("Success: addmsg successful.\n");
            return 0;
            
           
    }

    /*Frees all log resources previously used.*/
    void clearlog(void){
         log_t* temp = NULL;
         
         if(headptr == NULL){   
                printf("Log is already clear!\n");
                   return ;
                 }
                 else{
                             while(headptr != NULL){
                                 temp = headptr;
                                 headptr = headptr->next;
                                 free(temp);
                             }
                             
                             }
                 printf("Log is now clear!\n");
                 return;
         }
    
    /* Get Log returns a pointer to a string allocated big enough to hold all log details. If it cannot do it, then null is returned.*/
    char* getlog(void){
          bool status = true;
          log_t* temp = NULL;
          log_t* copy = headptr;
          char* newLine = "\n";
          char logPointer[5000];
 
          
                   //return NULL if head is NULL there is no list.
                   if(copy == NULL){
                           errno = ENOMEM;
                   return NULL;
                   }
                   else{
                        while(copy != NULL){
                                         temp = copy;
                                         strcat(logPointer, copy->item.string);
                                         strcat(logPointer, newLine);
                                         copy = copy->next;
                                         }
                                         
                                  
          //return the log string generated.
          return logPointer;
          }
          
    }
          
    /*Save the log with specified file name.*/
    int savelog(char* fileName){
        char* const TXT_EXTENSION = ".txt";
        strcat(fileName, TXT_EXTENSION);
        bool status = true;
        log_t* current = headptr;
        ofstream outfile;
        outfile.open(fileName, ios::out | ios::app);
        if(outfile){
    
        log_t* temp = NULL;
        while(current != NULL){
             temp = current;
             current = current->next;
             outfile << temp->item.string;
             outfile << "\n";
             }
             
         }else{
               status = false;                       
         }
         outfile.close();
        
        //If log filewrite was successful, return 0.
        if(status){
        printf("Success: savelog successful.\n");
        return 0;
        }
        //If log filewrite was unsuccessful, return -1.
        else{
             errno = EIO;
             perror("Error: savelog unsuccessful. File open unsuccessful.");
             return -1;
        }

        
    }
