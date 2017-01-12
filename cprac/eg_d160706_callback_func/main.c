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

#define DEFAULT_BLOCK_SIZE (4096)

// 定義callback function的prototype。
typedef void (* CALLBACK) (int);

// 定義了一個名為ShowPercentage的函式。這就是我們的callback函式。
// 他的prototype必須與前面的CALLBACK宣告一致。
void ShowPercentage(int percentage)
{
    fprintf(stderr, "percentage:%d\r\n", percentage);
}

// 定義了一個CopyFile的函式，這個函式會將參數source所指定檔案複製到
// target參數所指定的檔案去。而且每複製DEFAULT_BLOCK_SIZE數量的資料
// 就會呼叫一次callback參數所指到function一次。
void CopyFile(const char *source, const char *target, CALLBACK callback)
{
    char buf[DEFAULT_BLOCK_SIZE] ;
    struct stat fs ;
    int fdSrc, fdTrg ;
    int readBytes = 0, totalReadBytes = 0, percentage = 0;
    fdSrc = open(source, O_RDONLY);
    fstat(fdSrc, &fs);
    fdTrg = open(target,O_CREAT|O_TRUNC|O_RDWR);
    // 主要複製資料的迴圈
    while((readBytes=read(fdSrc, buf, DEFAULT_BLOCK_SIZE)) > 0)
    {
        write(fdTrg, buf, readBytes);
        totalReadBytes += readBytes ;
        //複製資料後就呼叫callback函式去做顯示百分比的動作。
        callback( (totalReadBytes*100)/fs.st_size);
    }
    close(fdTrg);
    close(fdSrc);
}

int main(void)
{
    // 這個範例中只是利用callback來顯示目前的進度。
    // 實際上我們可以利用callback來做更多的動作。
    CopyFile("A.TXT", "B.TXT", ShowPercentage);
    return 0 ;
}