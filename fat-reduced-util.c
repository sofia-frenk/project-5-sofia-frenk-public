#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>
#include<time.h>

#include "fat-reduced.h"

/*
 * name: fat-reduced-util.c
 * last update:
 *    13 nov 2022, bjr
 *     5 nov 2023, bjr
 *
 */

static struct DirEnt root_dir[DIR_N] ;
static unsigned int fat_table[FAT_N] ;
static struct Cluster cluster_table[CLUSTER_N] ;

void init_fat() {
	 int i ;
	 if (is_verbose_g>1) {
		printf("(%s,%d):\n\t%ld fat entries (%ld bytes),"
			"\n\t%ld dir entries (%ld bytes),"
			"\n\tdirent size is %ld bytes.\n", 
			__FILE__,__LINE__,
			(unsigned long) FAT_N, sizeof(fat_table), 
			(unsigned long) DIR_N, sizeof(root_dir), 
			 sizeof(struct DirEnt)
			) ;
	}

	for (i=0;i<FAT_N;i++) fat_table[i] = 0 ;
	for (i=0;i<sizeof(root_dir);i++) ((char *)root_dir)[i] = 0 ;
	return ;
}

int qu_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):qu_action\n",__FILE__,__LINE__) ;
	}
	return ERR_ABORT ;
}

int ls_action(int actc, char * actv[]) {

	// ...

	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	
	
	// ...
	
	
	return 0 ;
}

int wr_action(int actc, char * actv[]) {

	// ...

	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	
	if (strlen(actv[1])>FILENAME_LEN) actv[1][FILENAME_LEN] = '\0' ;


	// ...
	
	
	return 0 ;
}

int rd_action(int actc, char * actv[]) {

	// ...
	
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}


	// ...
	
	
	return 0 ;
}

int rm_action(int actc, char * actv[]) {

	// ...
	
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}


	// ...
	

	return 0 ;
}
/* end of file */
