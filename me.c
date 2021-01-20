#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>

int main(int argc, char *argv[])
{
    av_register_all();
    avformat_network_init();
    AVFormatContext *ctx = NULL;
    //ctx = avformat_alloc_context();
    char *filename = argv[1];
    char path[] = "/mnt/d/s.mp4";
    int ret = avformat_open_input(&ctx, path  ,NULL, NULL);
    //ret = avformat_find_stream_info(ctx, NULL);
    char buff[1024];
    av_strerror(ret, buff, sizeof(buff));
    printf("ret: %s\n", buff);
    ret = avformat_find_stream_info(ctx, NULL);
    AVStream *vStream = ctx->streams[0];
    AVStream *aStream = ctx->streams[1];
    AVCodec *vcodec = avcodec_find_encoder(vStream->codec->codec_id);
    AVCodec *acodec = avcodec_find_encoder(aStream->codec->codec_id);
    AVCodecContext *outvcodectx = avcodec_alloc_context3(vcodec);
    AVCodecParameters *outvcodec = avcodec_open2(outvcodectx, vcodec, NULL);
    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    int *got_picture = 0;
    while (1)
    {
        ret = av_read_frame(ctx, pkt);
        av_strerror(ret, buff, sizeof(buff));
        if (ret < 0){
            break;
        }
        //printf("ret: %s\n", buff);
        if (pkt->stream_index == 0){
            printf("pkt_pts is %d; pkt_dts is %d, pkt_time is %f\n", pkt->pts, pkt->dts,pkt->pts * av_q2d( vStream->time_base));
            ret = avcodec_send_packet(vStream->codec, pkt);
            av_strerror(ret, buff, sizeof(buff));
            printf("ret: %s\n", buff);

            ret = avcodec_receive_packet(vStream->codec, frame);
        }
    }
    

    return 0;
}
