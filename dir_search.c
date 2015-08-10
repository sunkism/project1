#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

//FILE DEPTH ???
#ifndef USE_FDS
#define USE_FDS 15
#endif

#define MAX_FILE_LEN 128
//global variable (cfg file)
int gi_max_diff_tm = 300;
int gi_delay_sec   = 60;
char *gsh_default_path = ".";
char *gsh_watch_fname = "core";
int gi_detect_cnt = 0;

int search_directory(const char *filepath, const struct stat *info,
		const int typeflag, struct FTW *pathinfo)
{
	struct tm mtime;
    time_t mtime_sec;
	time_t curtime_sec;
	unsigned long diff_time;
    char fname[MAX_FILE_LEN];
	int flen;
    int ret;

	localtime_r(&(info->st_mtime), &mtime);
    mtime_sec = mktime(&mtime);
    curtime_sec = time(NULL);
    diff_time = curtime_sec - mtime_sec;
	
	if(typeflag == FTW_F)
	{   
		if(diff_time < gi_delay_sec)
		{
			flen = get_fname(filepath,&fname);
			if(!strcmp(gsh_watch_fname, fname))
				printf("core file created!!\n");
			printf("%04d-%02d-%02d %02d:%02d:%02d",
					mtime.tm_year+1900, mtime.tm_mon+1, mtime.tm_mday, 
					mtime.tm_hour, mtime.tm_min, mtime.tm_sec);
			printf("File - path:%s, depth:%d\n", filepath, pathinfo->level);
			gi_detect_cnt++;
		}
			
	}
	else if(typeflag == FTW_D || FTW_DP)
	{	
		if(diff_time < gi_delay_sec)
		{	
			printf("Directory - path:%s, depth:%d\n", filepath, pathinfo->level);
			gi_detect_cnt++;
		}
	}
	
	return 0;
}

int get_fname(char *path, char *fname)
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
int main()
{
	int result = 0;
	char *path = ".";
    int loop_cnt = 60;
    int ii=0;
    while(ii<loop_cnt)
	{
		gi_detect_cnt = 0;
		printf("phase%d :ftw test start \n",ii);
		result = nftw(path,search_directory, USE_FDS, FTW_PHYS);
	
		if(result !=0)
		{
			printf("error!!! %d\n", result);
		    return result;
		}
		printf("phase%d : %d file/directory detected.\n",ii,gi_detect_cnt);
		sleep(gi_delay_sec);
		ii++;
	}
	printf("watch finish\n");
	return 0;
}
