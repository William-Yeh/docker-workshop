// Directory walker, excluding /dev /proc /sys.
//
// Usage: walk  [starting path]
//
// @adapted from: http://linux.die.net/man/3/ftw
//


#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define BUF_SIZE     512
#define TIME_FORMAT  "%F %R"
#define DEFAULT_DIRECTORY "/"

const char* EXCLUDE_PATH[] = {
    "/dev",
    "/proc",
    "/sys"
};


int should_skip_this_path(const char* path)
{
    int array_length = sizeof(EXCLUDE_PATH) / sizeof(EXCLUDE_PATH[0]);
    for (int i = 0; i < array_length; ++i) {
        if (strstr(path, EXCLUDE_PATH[i]) == path) {
            return 1;
        }
    }
    return 0;
}

static int
display_info(const char* fpath, const struct stat* sb,
             int tflag, struct FTW* ftwbuf)
{
    // last update time
    char utime[BUF_SIZE];
    struct tm* timeinfo = localtime(&sb->st_mtime);
    strftime(utime, BUF_SIZE - 1, TIME_FORMAT, timeinfo);
    //printf("%s\n", utime);

    // file type
    const char* file_type =
        (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
        (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "f" :
        (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
        (tflag == FTW_SLN) ? "sln" : "???";

    if (should_skip_this_path(fpath)) {
        return 0;
    }


    printf("%-3s %s  %7jd  %-40s\n",
        file_type,
        utime,
        (intmax_t) sb->st_size,
        fpath);
    return 0;           /* To tell nftw() to continue */
}

int
main(int argc, char* argv[])
{
    int flags = 0;

    if (argc > 2 && strchr(argv[2], 'd') != NULL)
        flags |= FTW_DEPTH;
    if (argc > 2 && strchr(argv[2], 'p') != NULL)
        flags |= FTW_PHYS;

    if (nftw((argc < 2) ? DEFAULT_DIRECTORY : argv[1], display_info, 20, flags)
            == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
