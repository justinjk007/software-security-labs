/*use_cap.c*/
#include <errno.h>
#include <fcntl.h>
#include <linux/capability.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>

int cap_disable(cap_value_t capflag)
{
    cap_t mycaps;
    mycaps = cap_get_proc();
    if (mycaps == NULL) return -1;
    if (cap_set_flag(mycaps, CAP_EFFECTIVE, 1, &capflag, CAP_CLEAR) != 0) return -1;
    if (cap_set_proc(mycaps) != 0) return -1;
    return 0;
}

int cap_enable(cap_value_t capflag)
{
    cap_t mycaps;
    mycaps = cap_get_proc();
    if (mycaps == NULL) return -1;
    if (cap_set_flag(mycaps, CAP_EFFECTIVE, 1, &capflag, CAP_SET) != 0) return -1;
    if (cap_set_proc(mycaps) != 0) return -1;
    return 0;
}

int cap_drop(cap_value_t capflag)
{
    cap_t mycaps;
    mycaps = cap_get_proc();
    if (mycaps == NULL) return -1;
    if (cap_set_flag(mycaps, CAP_EFFECTIVE, 1, &capflag, CAP_CLEAR) != 0) return -1;
    if (cap_set_flag(mycaps, CAP_PERMITTED, 1, &capflag, CAP_CLEAR) != 0) return -1;
    if (cap_set_proc(mycaps) != 0) return -1;
    return 0;
}

int main(void)
{
    if (open("/etc/shadow", O_RDONLY) < 0)
        printf("(a) Open failed\n"); /*Question (a): is the above open sucessful? why?*/
    if (cap_disable(CAP_DAC_READ_SEARCH) < 0) return -1;
    if (open("/etc/shadow", O_RDONLY) < 0)
        printf("(b) Open failed\n"); /*Question (b): is the above open sucessful? why?*/
    if (cap_enable(CAP_DAC_READ_SEARCH) < 0) return -1;
    if (open("/etc/shadow", O_RDONLY) < 0)
        printf("(c) Open failed\n"); /*Question (c): is the above open sucessful? why?*/
    if (cap_drop(CAP_DAC_READ_SEARCH) < 0) return -1;
    if (open("/etc/shadow", O_RDONLY) < 0)
        printf("(d) Open failed\n"); /*Question (d): is the above open sucessful? why?*/
    if (cap_enable(CAP_DAC_READ_SEARCH) == 0) return -1;
    if (open("/etc/shadow", O_RDONLY) < 0)
        printf("(e) Open failed\n"); /*Question (e): is the above open sucessful? why?*/
}
