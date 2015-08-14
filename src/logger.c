#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 128

void log_prt(char *filename,const char *format, ...)
{
	va_list arg;
	FILE *fp;
    char *logmsg = NULL;
    
	logmsg = (char *)malloc(MAX_MSG_LEN);
	
	fp = fopen(filename, "a"); //append
	va_start(arg, format);
	vsprintf(logmsg,format,arg);
	va_end(arg);

	fprintf(fp,"%s",logmsg);
    free(logmsg);
	fclose(fp);
}


