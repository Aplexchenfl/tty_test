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

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio, oldtio;
    if(tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD; //CLOCAL:忽略modem控制线  CREAD：打开接受者
    newtio.c_cflag &= ~CSIZE; //字符长度掩码。取值为：CS5，CS6，CS7或CS8

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB; //允许输出产生奇偶信息以及输入到奇偶校验
        newtio.c_cflag |= PARODD;  //输入和输出是奇及校验
        newtio.c_iflag |= (INPCK | ISTRIP); // INPACK:启用输入奇偶检测；ISTRIP：去掉第八位
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch( nSpeed )
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB; //CSTOPB:设置两个停止位，而不是一个
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;

    newtio.c_cc[VTIME]  = 0; //VTIME:非cannoical模式读时的延时，以十分之一秒位单位
    newtio.c_cc[VMIN] = 0; //VMIN:非canonical模式读到最小字符数
    tcflush(fd,TCIFLUSH); // 改变在所有写入 fd 引用的对象的输出都被传输后生效，所有已接受但未读入的输入都在改变发生前丢弃。
    if((tcsetattr(fd,TCSANOW,&newtio))!=0) //TCSANOW:改变立即发生
    {
        perror("com set error");
        return -1;
    }
    printf("set done!\n\r");
    return 0;
}

void test_tty(char *tty_node)
{
    int fd, count = 0, true_num = 0 , nset, read_val, strcasecmp_num;
    char buf[]={"abcdefg1234567890"};
    char read_buf[100];

    fd = open(tty_node, O_RDWR);
    if(fd < 0)
        goto TEST_ERR;

    nset = set_opt(fd, 115200, 8, 'N', 1);
    if (nset == -1)
        goto TEST_ERR1;

    while(1)
    {
        write(fd, buf, sizeof(buf));
        count ++;

        memset(read_buf, 0, sizeof(read_buf));

        read_val = read(fd, read_buf, sizeof(read_buf));
        if(read_val > 0)
        {
            strcasecmp_num = strcasecmp(read_buf, buf);
            if (strcasecmp_num == 0)
                true_num++;
        }

        if ((count % 100) == 0)
        {
            printf("%s  true count num :    %d         \n", tty_node, true_num);
            printf("%s  count num      :    %d         \n", tty_node, count);
        }
        if (count > 5000)
            break;

        usleep(100000);
    }

    close(fd);
    return;

TEST_ERR1:
    close(fd);
TEST_ERR:
    printf("open %s  error\n", tty_node);
    return;
}

int main(void)
{
    pid_t pid0, pid1, pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9;
    char node0[] = "/dev/ttyS0";
    char node1[] = "/dev/ttyS1";
    char node2[] = "/dev/ttyS2";
    char node3[] = "/dev/ttyS3";
    char node4[] = "/dev/ttyS4";
    char node5[] = "/dev/ttyS5";
    char node6[] = "/dev/ttyS6";
    char node7[] = "/dev/ttyS7";
    char node8[] = "/dev/ttyS8";
    char node9[] = "/dev/ttyS9";

    if ((pid1 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid1 == 0)
    {
        test_tty(node0);
        exit(1);
    }

    if ((pid1 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid1 == 0)
    {
        test_tty(node1);
        exit(1);
    }

    if ((pid2 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid2 == 0)
    {
        test_tty(node2);
        exit(1);
    }

    if ((pid3 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid3 == 0)
    {
        test_tty(node3);
        exit(1);
    }

    if ((pid4 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid4 == 0)
    {
        test_tty(node4);
        exit(1);
    }

    if ((pid5 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid5 == 0)
    {
        test_tty(node5);
        exit(1);
    }

    if ((pid6 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid6 == 0)
    {
        test_tty(node6);
        exit(1);
    }

    if ((pid7 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid7 == 0)
    {
        test_tty(node7);
        exit(1);
    }

    if ((pid8 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid8 == 0)
    {
        test_tty(node8);
        exit(1);
    }

    if ((pid9 = fork()) < 0)
    {
        perror("fork error1");
    }
    else if(pid9 == 0)
    {
        test_tty(node9);
        exit(1);
    }

    return 0;
}
