#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include "logger.h"

//FILE DEPTH ???
#ifndef USE_FDS
#define USE_FDS 15
#endif

#define MAX_FILENAME 128
#define DELAY_SEC 30
#define MAX_DIFF_TM 300  // 5분이내 변경된 파일 찾기
//global variable (cfg file)
int gi_max_diff_tm = 300;
int gi_detect_cnt = 0;
int gi_log_fd;

char *gs_dflt_path = "../run";
char *gs_dflt_fname = "core";
char *gs_watch_fname = NULL;
char *gs_watch_dname = NULL;
char *gs_logname =  "../log/FileWatcherLog.log";


int get_fname(const char *path, char *fname);
void Usage(void);
int get_option(int argc, char *argv[]);

void Usage()
{
	printf("search_directory -f filename\n");
    printf("                 -p path\n");
    printf("** defualt file: core\n");
    printf("** defualt path: ../run\n");
    exit(0);
}

int get_option(int argc, char *argv[])
{
	int param_opt;

	while(-1 != (param_opt = getopt(argc,argv,"f:p:")))
	{
		switch(param_opt)
		{
			case 'f' : gs_watch_fname = optarg; break;
			case 'p' : gs_watch_dname = optarg; break;
			case '?' : Usage();
		}
	}
	if(gs_watch_fname == NULL)
	{
		printf("set defualt file: %s.\n",gs_dflt_fname);
    	gs_watch_fname = (char *)malloc(MAX_FILENAME);
		strcpy(gs_watch_fname,gs_dflt_fname);
	}
	if(gs_watch_dname == NULL)
	{
		printf("set defualt path: %s.\n",gs_dflt_path);
    	gs_watch_dname = (char *)malloc(MAX_FILENAME);
		strcpy(gs_watch_dname,gs_dflt_path);
	}
	return 1;
}
		
int search_directory(const char *filepath, const struct stat *info,
		const int typeflag, struct FTW *pathinfo)
{
	struct tm mtime;
    time_t mtime_sec;
	time_t curtime_sec;
	unsigned long diff_time;
    char *fname;
	int flen;

    fname = (char *)malloc(MAX_FILENAME);
	localtime_r(&(info->st_mtime), &mtime);
    mtime_sec = mktime(&mtime);
    curtime_sec = time(NULL);
    diff_time = curtime_sec - mtime_sec;
	
	if(typeflag == FTW_F)
	{   
		if(diff_time < MAX_DIFF_TM)
		{
			flen = get_fname(filepath,fname);
			if(!strcmp(gs_watch_fname, fname))
			{
				log_prt(gs_logname,
						"Error Message: %04d-%02d-%02d %02d:%02d:%02d %s is detected!",
					mtime.tm_year+1900, mtime.tm_mon+1, mtime.tm_mday, 
					mtime.tm_hour, mtime.tm_min, mtime.tm_sec,filepath);
				gi_detect_cnt++;
			}
		}
			
	}
	else if(typeflag == FTW_D || FTW_DP)
	{
        //no action for directory	
	}
	
	return 0;
}

int get_fname(const char *path, char *fname)
{
	int ii;
	int len;

	len = strlen(path);
	for(ii = len ; ii>0; ii--)
	{
		if(path[ii] == '/') break;
	}
	strcpy(fname, path+ii+1);
	return ii;
}

int main(int argc, char *argv[])
{
	int result = 0;
    int loop_cnt = 20;
    int ii=0;

    if(get_option(argc, argv) == 0)
	{
		Usage();
	}
	log_prt(gs_logname,"File Watcher Start");
    log_prt(gs_logname,"Watch Path: %s, File: %s, Delay(sec): %d",
			          gs_watch_dname, 
					  gs_watch_fname,
					  DELAY_SEC);
    while(ii<loop_cnt)
	{
		gi_detect_cnt = 0;
		result = nftw(gs_watch_dname,search_directory, USE_FDS, FTW_PHYS);
	
		if(result !=0)
		{
			log_prt(gs_logname,"error!!! %d", result);
		    return result;
		}
		log_prt(gs_logname,"phase%d : %d file/directory detected.",ii,gi_detect_cnt);
		sleep(DELAY_SEC);
		ii++;
	}
	log_prt(gs_logname,"File Watcher Stop");
	return 0;
}
