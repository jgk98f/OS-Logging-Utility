#include <time.h>
#ifndef loglib
#define loglib
struct data_t {
     time_t time;
     char *string;
};

struct log_t {
     data_t item;
     struct log_t *next = NULL;
};

int addmsg(data_t data);
void clearlog(void);
char *getlog(void);
int savelog(char *); 
#endif

