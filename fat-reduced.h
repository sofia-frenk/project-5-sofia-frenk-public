/*
 * name: fat-reduced.h
 * last-update:
 *     13 nov 2022 -bjr: created
 *      5 nov 2023 -bjr
 */

#ifndef _FAT_REDUCED_H
#define _FAT_REDUCED_H 1

#define FILENAME_LEN 15
#define ACTION_NAME_LEN 4
#define CLUSTER_SIZE 32
#define DIR_N 64
#define FAT_N 128
#define CLUSTER_N 128
#define ACTION_N 5

#define FAT_FREE 0
#define FAT_LAST -1

#define USAGE_MSG "usage: %s [-v]\n"
#define PROG_NAME "fat-reduced"
#define SEP_CHARS " \t\n"
#define LINE_MAX 1024

#define ERR_ABORT -1
#define ERR_CREATE 1
#define ERR_NOEXIST 2
#define ERR_DIRFULL 3
#define ERR_FATFULL 4
#define ERR_DISKFULL 5

extern int is_verbose_g ;

struct Actions {
    char action_name[ACTION_NAME_LEN] ;
    int action_parameters ;
    int (*action_function)(int, char *[]) ;
    } ;

struct  DirEnt {
    char name[FILENAME_LEN+1] ;
    unsigned int len ;
    unsigned int starting_cluster ;
    } ;

struct Cluster {
    char data[CLUSTER_SIZE] ;
    } ;

void init_fat() ;

int qu_action(int, char *[]) ;
int ls_action(int, char *[]) ;
int wr_action(int, char *[]) ;
int rm_action(int, char *[]) ;
int rd_action(int, char *[]) ;

#endif /* _FAT_REDUCED_H */

