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
    time_t timer;
	struct tm *t;

	logmsg = (char *)malloc(MAX_MSG_LEN);
	timer = time(NULL);
	t = localtime(&timer);

	fp = fopen(filename, "a"); //append
	va_start(arg, format);
	vsprintf(logmsg,format,arg);
	va_end(arg);

	fprintf(fp,"[%d%d%d-%d:%d:%d] %s\n",t->tm_year+1900,
			                         t->tm_mon + 1,
									 t->tm_mday,
									 t->tm_hour,
									 t->tm_min,
									 t->tm_sec,
									 logmsg);
    free(logmsg);
	fclose(fp);
}


