#include <stdio.h>
#include "Video.h"

#include "MathUtils.h"

namespace Soft3D {

	Bool Video::ffmpegRegisted = false;

	Video::Video(const char* url) {
		if (Video::ffmpegRegisted == false) {
			Video::ffmpegRegisted = true;
			av_register_all();
		}

		formatCtx = avformat_alloc_context();

		if (avformat_open_input(&formatCtx, url, NULL, NULL) != 0) {
			printf("无法打开文件\n");
			exit(-1);
		}

		if (avformat_find_stream_info(formatCtx, NULL)<0)
		{
			printf("Couldn't find stream information.\n");
			exit(-1);
		}

		videoindex = -1;

		for (int i = 0; i<formatCtx->nb_streams; i++)
			if (formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoindex = i;
				break;
			}
		if (videoindex == -1)
		{
			printf("Didn't find a video stream.\n");
			exit(-1);
		}

		codecCtx = formatCtx->streams[videoindex]->codec;
		codec = avcodec_find_decoder(codecCtx->codec_id);
		if (codec == NULL)
		{
			printf("Codec not found.\n");
			exit(-1);
		}
		printf("pCodec=%d\n", codec->id);
		if (avcodec_open2(codecCtx, codec, NULL)<0)
		{
			printf("Could not open codec.\n");
			exit(-1);
		}

		frame = av_frame_alloc();
		int ret, got_picture;
		int y_size = codecCtx->width * codecCtx->height;
		
		pixmap = new Pixmap(codecCtx->width, codecCtx->height, PixmapFormat::RGBA);

		av_init_packet(&packet);

		frameRgb = av_frame_alloc();
		if (frameRgb == NULL) {
			exit(-1);
		}

		pixmap = new Pixmap(codecCtx->width, codecCtx->height, PixmapFormat::RGBA);


		avpicture_fill((AVPicture*)frameRgb, pixmap->data, AV_PIX_FMT_RGBA, codecCtx->width, codecCtx->height);

		img_convert_ctx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt, codecCtx->width, codecCtx->height, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL, NULL);

	}

	void Video::Play() {
		this->isPlaying = true;
		printf("Play");
	}

	void Video::Pause(){
		this->isPlaying = false;
		printf("Stop");
	}

	void Video::Update(Float delta) {
		if (this->isPlaying == true) {
			time += delta;
			GetFrame();
		}		
	}

	void Video::SetProgress(Float progress) {
		printf("set progress=%f\n", progress);
		progress = MathUtils::Clamp(progress, 0.0f, 1.0f);		

		if (formatCtx->duration != AV_NOPTS_VALUE) {
			int64_t duration = formatCtx->duration + (formatCtx->duration <= INT64_MAX - 5000 ? 5000 : 0);
			int64_t secs = duration / AV_TIME_BASE;
			av_seek_frame(formatCtx, videoindex, (int64_t)(progress*secs*1000), AVSEEK_FLAG_FRAME);
		}
		
	}

	void Video::GetFrame() {
		//------------------------------
		
		while (av_read_frame(formatCtx, &packet) >= 0)
		{
			if (packet.stream_index == videoindex)
			{
				int got_picture;
				int ret = avcodec_decode_video2(codecCtx, frame, &got_picture, &packet);
				if (ret < 0)
				{
					printf("decode error!\n");
					exit(-1);
				}

				if (got_picture)
				{
					int rs = sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, frame->height, frameRgb->data, frameRgb->linesize);
					av_free_packet(&packet);
					return;
				}
			}
			av_free_packet(&packet);
		}		
	}

	void Video::Close() {
		avcodec_close(codecCtx);
		avformat_close_input(&formatCtx);
	}

}
