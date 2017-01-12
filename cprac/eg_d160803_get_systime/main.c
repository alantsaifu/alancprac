#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define V1_FILENAME         "/media/mmcblk0p1"  // Video Encoded File Path

/*
 * The result should look something like
 * Fri 2008-08-22 15:21:59 WAST
 */

int main(void)
{
    time_t     now;
    struct tm *ts;
    unsigned char       buf[80];
    unsigned char       h264_path[128];

    /* Get the current time */
    now = time(NULL);

    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M", ts);

    sprintf(h264_path,"%s/adestream_%s.h264",V1_FILENAME,buf);
    puts(h264_path);

    return 0;
}