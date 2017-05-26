#ifndef _APLEX_TTY_H__
#define _APLEX_TTY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

/*
 * structure aplex_tty:
 * tty_node: serial file node , ex: /dev/ttyO0, /dev/ttyO1;
 * test_count : when test count > test_count , test over , exit; ex: 5000;
 * usleep_time : test speed , How often do you send the data, ex: 100000 (us);
 * test_chr : the data of send to serial ;
 */
struct aplex_tty
{
    char tty_node[16];
    int stop_count;
    unsigned int usleep_time;
    char test_chr[32];
};

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);

void init_aplex_tty(struct aplex_tty *, char *tty_node, int test_count, unsigned int usleep_time, char test_chr[32]);
void test_tty(struct aplex_tty *);

#endif
