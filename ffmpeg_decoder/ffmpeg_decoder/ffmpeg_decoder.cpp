// ffmpeg_decoder.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#define __STD_CONSTANT_MACROS

extern "C"
{
	#include <libavutil/opt.h>
	#include "libavcodec/avcodec.h"     //������������Ϣ
	#include "libavformat/avformat.h"	//������װ��Ϣ
	#include "libswscale/swscale.h"     //����ÿһ֡ͼ������
}

int _tmain(int argc, _TCHAR* argv[])
{
	AVFormatContext *pFormatCtx;
	char *filepath = "Titanic.ts";
	char *file_out = "Titanic.yuv";
	char *file_out1 = "Titanic.h264";
	FILE *fp_out;
	FILE *fp_out1;
	errno_t err,err1;

	err = fopen_s(&fp_out, file_out, "wb+");
	if (err != 0)
	{
		printf("The file 'crt_fopen_s.c' was opened\n");
		return -1;
	}

	err1 = fopen_s(&fp_out1, file_out1, "wb+");
	if (err1 != 0)
	{
		printf("The file 'crt_fopen_s.c' was opened\n");
		return -1;
	}

	av_register_all();    //ע���������
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();   //�����ڴ�
	if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) < 0) //��������Ƶ�ļ�
	{
		printf("Can't open the input stream.\n");
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx,NULL)<0)     //�ж��ļ�������Ƶ��������Ƶ��
	{
		printf("Can't find the stream information!\n");
		return -1;
	}

	int i, index_video = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)      //�������Ƶ�������¼�洢��
		{
			index_video = i;
			break;
		}		
	}
	if (index_video == -1)
	{
		printf("Can't find a video stream;\n");
		return -1;
	}

	AVCodecContext *pCodecCtx = pFormatCtx->streams[index_video]->codec;

	AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);     //���ҽ�����
	if (pCodec == NULL)
	{
		printf("Can't find a decoder!\n");
		return -1;
	}

	//if (pCodecCtx->codec_id == AV_CODEC_ID_H264)
	//{
	//	av_opt_set(pCodecCtx->priv_data, "preset", "slow", 0);
	//	av_opt_set(pCodecCtx->priv_data, "tune", "zerolatency", 0);
	//}


	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)   //�򿪱�����
	{
		printf("Can't open the decoder!\n");
		return -1;
	}


	AVFrame *pFrame = av_frame_alloc();  //this only allocates the AVFrame itself, not the data buffers
	AVFrame *pFrameYUV = av_frame_alloc();

	uint8_t *out_buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P,pCodecCtx->width,pCodecCtx->height));  //���ٻ�����
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);//֡��������ڴ���

	AVPacket *pkt = (AVPacket *)av_malloc(sizeof(AVPacket));;
	av_init_packet(pkt);
	
	SwsContext * img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	
	int frame_cnt = 0;
	int ret;
	int get_frame;
	int y_size = pCodecCtx->width*pCodecCtx->height;
	while (av_read_frame(pFormatCtx,pkt) >=0  )
	{
		if (pkt->stream_index == index_video)
		{
			fwrite(pkt->data,1,pkt->size,fp_out1);
			if (avcodec_decode_video2(pCodecCtx, pFrame, &get_frame, pkt) < 0)
			{
				printf("Decode Error!\n");
				return -1;
			}
			if (get_frame)
			{
				printf("Decoded frame index: %d\n", frame_cnt);
				sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
					pFrameYUV->data, pFrameYUV->linesize);
				fwrite(pFrameYUV->data[0], 1, y_size, fp_out);
				fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_out);
				fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_out);
				frame_cnt++;
			}

		}
		av_free_packet(pkt);
	}
	while (1)
	{
		if (avcodec_decode_video2(pCodecCtx, pFrame, &get_frame, pkt) < 0)
		{
			printf("Decode Error!\n");
			break;
		}
		if (get_frame)
		{
			printf("Flush Decoded frame index: %d\n", frame_cnt);
			sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
				pFrameYUV->data, pFrameYUV->linesize);
			fwrite(pFrameYUV->data[0], 1, y_size, fp_out);
			fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_out);
			fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_out);
			frame_cnt++;
		}
		else
			break;
	}

	//close
	fclose(fp_out);
	fclose(fp_out1);

	//free
	sws_freeContext(img_convert_ctx);
	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	avformat_free_context(pFormatCtx);

	return 0;
}

