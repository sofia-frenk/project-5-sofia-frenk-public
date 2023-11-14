#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>

#include "fat-reduced.h"

/*
 * name: fat-reduced.c
 * last update:
 *    13 nov 2022, bjr
 *     5 nov 2023, bjr
 *
 */

int is_verbose_g = 0 ;
static struct Actions actions[ACTION_N] = {
    { "qu", 0, qu_action},
    { "ls", 0, ls_action},
    { "wr", 2, wr_action},
    { "rm", 1, rm_action},
    { "rd", 1, rd_action},
};

int token_line(char * cmd_line, char * parsed[], int n) {
    int i ;
    char * s ;
    s = strtok(cmd_line, SEP_CHARS) ;
    for (i=0;i<n;i++) {
        if (s!=NULL) {
            parsed[i] = s ;
        }
        else break ;
        s = strtok(NULL, SEP_CHARS) ;
    }
    
    if (is_verbose_g>1) {
        int j ;
        printf("(%s,%d): token_line, %d tokens found\n\t",__FILE__,__LINE__,i) ;
        for (j=0;j<i;j++)  printf("[%d]:|%s| ",j, parsed[j]) ;
        printf("\n") ;
    }

    return i ;
}

int main(int argc, char * argv[]) {
    int ch ;
    char buf[LINE_MAX] ;

    while ((ch = getopt(argc, argv, "v")) != -1) {
        switch(ch) {
            case 'v':
                is_verbose_g += 1 ;
                break ;
            default:
                printf(USAGE_MSG, PROG_NAME) ;
                return 0 ;
        }
    }
    argc -= optind;
    argv += optind;
    
    init_fat() ;
    
    while ( fgets(buf,LINE_MAX,stdin) != NULL ) {
        int cmd_n ;
        char * cmd_a[4] ;
        int found ;
        int i ;
        int err ;
        
        cmd_n = token_line(buf,cmd_a,sizeof(cmd_a)/sizeof(cmd_a[0])) ;
        if (cmd_n==0) continue ;
        
        found = 0 ;
        err = 0 ;
        for (i=0;i<ACTION_N;i++) {
            if (strcmp(cmd_a[0],actions[i].action_name)==0) {
                found = 1 ;
                if (actions[i].action_parameters!=(cmd_n-1))
                    printf("Command %s takes %d parameters\n", cmd_a[0],actions[i].action_parameters) ;
                else {
                    err = actions[i].action_function(cmd_n, cmd_a) ;
                }
                break ;
            }
        }

        if (!found) {
            printf("Command %s not found. Commands are: ",cmd_a[0]) ;
            for (i=0;i<ACTION_N;i++) printf("%s ",actions[i].action_name) ;
            printf("\n") ;
        }
        
        if (err==ERR_ABORT) break ;
        if (err) printf("Command %s returned error %d.\n", cmd_a[0], err ) ;
    }
    
    if (is_verbose_g>1) {
        printf("(%s,%d): exit\n", __FILE__,__LINE__) ;
    }

    return 0 ;
}
