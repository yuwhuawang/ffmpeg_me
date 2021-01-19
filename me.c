#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>

int main(int argc, char *argv[])
{
    AVFormatContext *ctx = NULL;
    ctx = avformat_alloc_context();
    char *filename = argv[1];
    int ret = avformat_open_input(&ctx, filename  ,NULL, NULL);
    char buff[1024];
    av_strerror(ret, buff, sizeof(buff));
    printf("ret: %s\n", buff);
    
    return 0;
}
