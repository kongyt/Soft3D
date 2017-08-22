#ifndef _Test_Scene_H__
#define _Test_Scene_H__

#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

#ifdef __cplusplus
}
#endif


#include "../Soft3D/Soft3D.h"
#include "TestInput.h"
#include "TestClickListener.h"

using namespace Soft3D;


#define BUFSIZE  409600

class TestScene :public Scene {
public:

	int ffmpegtest2() {
		int             i, videoindex;
		char filepath[] = "test.mp4";
		av_register_all();
		formatCtx = avformat_alloc_context();
		if (avformat_open_input(&formatCtx, filepath, NULL, NULL) != 0) {
			printf("无法打开文件\n");
			return -1;
		}
		if (avformat_find_stream_info(formatCtx, NULL)<0)
		{
			printf("Couldn't find stream information.\n");
			return -1;
		}
		videoindex = -1;
		for (i = 0; i<formatCtx->nb_streams; i++)
			if (formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoindex = i;
				break;
			}
		if (videoindex == -1)
		{
			printf("Didn't find a video stream.\n");
			return -1;
		}
		codecCtx = formatCtx->streams[videoindex]->codec;
		codec = avcodec_find_decoder(codecCtx->codec_id);
		if (codec == NULL)
		{
			printf("Codec not found.\n");
			return -1;
		}
		printf("pCodec=%d\n", codec->id);
		if (avcodec_open2(codecCtx, codec, NULL)<0)
		{
			printf("Could not open codec.\n");
			return -1;
		}

		frame = av_frame_alloc();
		int ret, got_picture;
		int y_size = codecCtx->width * codecCtx->height;
		//av_new_packet(&packet, y_size);
		av_init_packet(&packet);

		//------------------------------
		while (av_read_frame(formatCtx, &packet) >= 0)
		{
			printf("packet2->stream_index=%d\n", packet.stream_index);
			printf("videoindex=%d\n", videoindex);
			if (packet.stream_index == videoindex)
			{
				printf("decode start!");
				//packet->data[0]=0;packet->data[1]=0;packet->data[2]=0;packet->data[3]=1;
				// packet->size-=4;
				printf("packet2->data=%d %d %d %d\n", packet.data[0], packet.data[1], packet.data[2], packet.data[3]);
				printf("packet2->size=%d\n", packet.size);
				ret = avcodec_decode_video2(codecCtx, frame, &got_picture, &packet);
				printf("got_picture=%x\n", got_picture);
				if (ret < 0)
				{
					printf("decode error!\n");
					return -1;
				}

				if (got_picture)
				{
					
					if (frameRgb == NULL) {
						frameRgb = av_frame_alloc();
						if (frameRgb == NULL) {
							return -1;
						}

						width = codecCtx->width;
						height = codecCtx->height;
						pixmap2 = new Pixmap(800, 480, PixmapFormat::RGBA);

						/*int numBytes = avpicture_get_size(AV_PIX_FMT_RGBA, width, height);
						buffer = (Byte*)av_malloc(numBytes);*/
						avpicture_fill((AVPicture*)frameRgb, pixmap2->data, AV_PIX_FMT_RGBA, codecCtx->width, codecCtx->height);
					}

					struct SwsContext* img_convert_ctx = NULL;
					img_convert_ctx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt, 800, 480, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL, NULL);
					int rs = sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, frame->height, frameRgb->data, frameRgb->linesize);

					//pixmap2->format = PixmapFormat::RGBA;
					return 1;
				}
			}
			av_free_packet(&packet);
		}
		//av_free(pFrameYUV);
		avcodec_close(codecCtx);
		avformat_close_input(&formatCtx);

		return 0;

	}

	int ffmpegtest() {

		inbuf = new Byte[BUFSIZE + AV_INPUT_BUFFER_PADDING_SIZE];
		memset(inbuf + BUFSIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

		av_register_all();
		av_init_packet(&packet);

		if (avformat_open_input(&formatCtx, "test.mp4", NULL, NULL) != 0) {
			return -1;
		}

		if (avformat_find_stream_info(formatCtx, NULL) < 0) {
			return -1;
		}

		av_dump_format(formatCtx, -1, "test.mp4", 0);

		int videoStream = -1;
		for (int i = 0; i < formatCtx->nb_streams; i++) {
			if (formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoStream = i;
				break;
			}
		}

		if (videoStream == -1) {
			return -1;
		}

		AVCodecParameters* codecParm = formatCtx->streams[videoStream]->codecpar;
		codec = avcodec_find_decoder(codecParm->codec_id);

		if (codec == NULL) {
			return -1;
		}

		codecCtx = avcodec_alloc_context3(codec);
		if (codecCtx == NULL) {
			return -1;
		}

		//if (codec->capabilities & AV_CODEC_CAP_TRUNCATED)
		//	codecCtx->flags |= AV_CODEC_FLAG_TRUNCATED; // we do not send complete frames

		if (avcodec_open2(codecCtx, codec, NULL) < 0) {
			return -1;
		}

		FILE* f = fopen("test.mp4", "rb");

		frame = av_frame_alloc();
		if (frame == NULL) {
			return -1;
		}

		frameRgb = NULL;
	

		int i = 0;
		int frameFinished;



		while (1) {
			packet.size = fread(inbuf, 1, BUFSIZE, f);
			packet.data = inbuf;

			int got_frame;
			int len = avcodec_decode_video2(codecCtx, frame, &got_frame, &packet);
			if (len < 0) {
				return -1;
			}

			if (got_frame) {
				if (frameRgb == NULL) {
					frameRgb = av_frame_alloc();
					if (frameRgb == NULL) {
						return -1;
					}

					width = codecCtx->width;
					height = codecCtx->height;

					int numBytes = avpicture_get_size(AV_PIX_FMT_RGBA, width, height);
					buffer = (Byte*)av_malloc(numBytes);

					avpicture_fill((AVPicture*)frameRgb, buffer, AV_PIX_FMT_RGBA, codecCtx->width, codecCtx->height);
				}
			
				struct SwsContext* img_convert_ctx = NULL;
				img_convert_ctx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt, codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
				int rs = sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, frame->height, frameRgb->data, frameRgb->linesize);
				pixmap2->width = frame->width;
				pixmap2->height = frame->height;
				pixmap2->data = frameRgb->data[0];
			

				pixmap2->format = PixmapFormat::RGB;
				return 1;
			}

			if (packet.data) {
				packet.size -= len;
				packet.data += len;
			}

		}

	}

	TestScene(){
		camera.SetToPers(60, 800, 480);
		//camera.SetToOrth(1300, 480);

		root = new GameObject();

		// 从文件读取纹理图
		FILE* fp = fopen("bg2.png", "rb");
		pixmap1 = new Pixmap(fp);
		fclose(fp);

		//pixmap2 = new Pixmap(pixmap1->width, pixmap1->height, PixmapFormat::RGBA);
	
		ffmpegtest2();
		//pixmap2 = new Pixmap(800, 480, PixmapFormat::RGBA);
		// 生成纹理
		texture = new Texture(pixmap2);
		texture->Load();

		region = new TextureRegion(texture);

		// 生成渲染对象
		sprite1 = new Sprite(region);
		sprite1->SetSize(200, 100);
		sprite1->SetRotation(45);
		sprite1->SetColor(1, 1, 1, 1);

		sprite2 = new Sprite(region);
		sprite2->SetSize(200, 100);
		sprite2->SetRotation(-45);
		sprite2->SetColor(1, 1, 1, 1);

		sprite3 = new Sprite(region);
		sprite3->SetSize(200, 100);
		sprite3->SetRotation(0);
		sprite3->SetColor(1, 0, 0, 1);
		
		root->AddRenderObject(sprite1); // 添加渲染对象
		root->AddRenderObject(sprite2); // 添加渲染对象
		root->AddRenderObject(sprite3); // 添加渲染对象

		root->SetPosition(0, 0, -1000);
		root->SetRotation(0, 0.5f, 0);
		root->SetScale(1,1,1);

		Input::SetProcessor(new TestInput());

		uiLayer = new UILayer(800, 480);
		Input::SetProcessor(uiLayer);

		uiButton = new UIButton(region);
		uiButton->x = 100;
		uiButton->y = 100;
		uiButton->width = 200;
		uiButton->height = 100;

		uiLayer->GetRoot().AddChild(uiButton);
	}

	~TestScene() {

	}

	void Show() {
	
	}

	void Resize(int width, int height) {

	}

	float dt = 0;
	void Render(RenderContext& context, Float delta) {
		dt += delta;
		//camera.position.x -= 1;
		//camera.Update(true);
		context.SetCameraMatrix(camera.m_combined);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);		

		root->SetRotation(0, dt, 0);

		root->Update(delta);
		root->Render(context);

		uiLayer->Update(delta);
		uiLayer->Render(context);
	}

	void Pause() {
	
	}

	void Resume() {
	
	}

	void Destroy() {
		delete uiButton;
		delete uiLayer;
		delete sprite1;
		delete sprite2;
		delete sprite3;
		delete region;
		delete texture;
		pixmap1->Destroy();
		delete pixmap1;
		pixmap2->Destroy();
		delete pixmap2;
		delete root;
	}
private:

	Camera camera;
	GameObject * root;
	Pixmap* pixmap1;
	Pixmap* pixmap2;
	Texture* texture;
	TextureRegion* region;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	UILayer* uiLayer;
	UIActor* uiButton;

	AVFormatContext* formatCtx = NULL;
	AVCodecContext* codecCtx = NULL;
	AVCodec*  codec;
	AVFrame * frame = NULL;
	AVFrame*  frameRgb = NULL;
	AVPacket  packet;
	Byte*  buffer;
	Byte* inbuf;
	int width;
	int height;
};

#endif