#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void log_prt(char *filename,const char *format, ...)
{
	va_list arg;
	int count;
	FILE *fp;
    char *logmsg;

	logmsg = (char *)malloc(128);
	
	fp = fopen(filename, "a"); //append
	va_start(arg, format);
	count = vsprintf(logmsg,format,arg);
	va_end(arg);

	fprintf(fp,"%s",logmsg);

	fclose(fp);
}


