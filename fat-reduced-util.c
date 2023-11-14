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
    
    for (int i=0; i<DIR_N; i++)
    {
        if(strlen(root_dir[i].name) == 0)
            continue;
        
        printf("DirEnt number: %d\n", i);
        printf("File length: %u\n", root_dir[i].len);
        printf("File name: %s\n", root_dir[i].name);
    }
    
    return 0 ;
}

int wr_action(int actc, char * actv[])
{

    // ...
    
    
    if (is_verbose_g>1) {
        printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
    }
    
    if (strlen(actv[1])>FILENAME_LEN) actv[1][FILENAME_LEN] = '\0' ;


    // ...
    
    char* FILENAME = actv[1];
    
    //step 1: find where to write DirEnt
    int DirEntIndex = -1;
    for(int i=0; i<DIR_N; i++)
    {
        if(strlen(root_dir[i].name) == 0)
        {
            DirEntIndex = i;
            break;
        }
    }
    if(DirEntIndex == -1)
        return 1;
    
    //step 2: writting the data/content to DirEnt
    strncpy(root_dir[DirEntIndex].name, FILENAME, strlen(FILENAME));
    root_dir[DirEntIndex].name[strlen(FILENAME)] = '\0';
    
    char* content = actv[2];
    root_dir[DirEntIndex].len = (int) (strlen(content)+1);
    
    int ClusterGroupIndex = -1;
    
    for(int i=0; i<FAT_N; i++)
    {
        if(fat_table[i] == 0)
        {
            ClusterGroupIndex = i;
            break;
        }
    }
    strncpy(cluster_table[ClusterGroupIndex].data, content, strlen(content));
    cluster_table[ClusterGroupIndex].data[strlen(content)] = '\0';
    fat_table[ClusterGroupIndex] = 1;
    return 0 ;
}


int rd_action(int actc, char * actv[]) {

    // ... will need file_name_to_DirEnt to get DirEnt
    
    if (is_verbose_g>1) {
        printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
    }


    // ...will need file_name_to_DirEnt to get DirEnt
    
    char* FILENAME = actv[1];
    int file_index = -1;

    // Find the file in the root directory
    for (int i = 0; i < DIR_N; i++) {
        if (strcmp(root_dir[i].name, FILENAME) == 0) {
            file_index = i;
            break;
        }
    }
    
    // Check if the file was found
    if (file_index == -1) {
        printf("File not found: %s\n", FILENAME);
        return 1;
    }
    
    int c = root_dir[file_index].starting_cluster;
    printf("%s\n", cluster_table[c].data);
    
    return 0 ;
}

struct DirEnt* file_name_to_DirEnt(char* FILENAME)
{
    for(int i=0; i<DIR_N; i++)
    {
        if(!strcmp(FILENAME, root_dir[i].name))
        {
            return &root_dir[i];
        }
    }
    return NULL;
}

int rm_action(int actc, char * actv[]) {

    // ... will need file_name_to_DirEnt
    
    if (is_verbose_g>1) {
        printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
    }

    // ...
    
    char* FILENAME = actv[1];
    
    struct DirEnt* de = file_name_to_DirEnt(FILENAME);
    
    de->name[0] = '\0';
    
    de->len = 0;
    
    cluster_table[de->starting_cluster].data[0] = '\0';
    
    fat_table[de->starting_cluster] = 0;
    
    return 0 ;
}
/* end of file */
