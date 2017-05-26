#include "../include/aplex_tty.h"

int main(void)
{
    struct aplex_tty aplex_tty1, aplex_tty2, aplex_tty3, aplex_tty4, aplex_tty5, aplex_tty6;
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;

    char tty_node1[] = "/dev/ttyO1";
    char tty_node2[] = "/dev/ttyO2";
    char tty_node3[] = "/dev/ttyO3";
    char tty_node4[] = "/dev/ttyO4";
    char tty_node5[] = "/dev/ttyO5";
    char tty_node6[] = "/dev/ttyUSB0";
    int test_count = 5000;
    unsigned int usleep_time = 100000;
    char test_chr[32] = "abcd9876543210\0";

    init_aplex_tty(&aplex_tty1, tty_node1, test_count, usleep_time, test_chr);
    init_aplex_tty(&aplex_tty2, tty_node2, test_count, usleep_time, test_chr);
    init_aplex_tty(&aplex_tty3, tty_node3, test_count, usleep_time, test_chr);
    init_aplex_tty(&aplex_tty4, tty_node4, test_count, usleep_time, test_chr);
    init_aplex_tty(&aplex_tty5, tty_node5, test_count, usleep_time, test_chr);
    init_aplex_tty(&aplex_tty6, tty_node6, test_count, usleep_time, test_chr);

    if ((pid1 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid1 == 0)
    {
        test_tty(&aplex_tty1);
        exit(1);
    }

    if ((pid2 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid2 == 0)
    {
        test_tty(&aplex_tty2);
        exit(1);
    }

    if ((pid3 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid3 == 0)
    {
        test_tty(&aplex_tty3);
        exit(1);
    }

    if ((pid4 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid4 == 0)
    {
        test_tty(&aplex_tty4);
        exit(1);
    }

    if ((pid5 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid5 == 0)
    {
        test_tty(&aplex_tty5);
        exit(1);
    }

    if ((pid6 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid6 == 0)
    {
        test_tty(&aplex_tty6);
        exit(1);
    }

    return 0;
}
