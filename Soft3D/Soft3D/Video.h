#ifndef _Video_H__
#define _Video_H__

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


#include "DllApi.h"
#include "Types.h"
#include "Pixmap.h"


namespace Soft3D {

	class DLLAPI Video {
	public:
		Video(const char* url);
		void Play();
		void Pause();
		void Update(Float delta);
		void SetProgress(Float progress);
		void Close();

	private:
		void OpenVideo();
		void GetFrame();


	private:
		AVFormatContext* formatCtx = NULL;
		AVCodecContext* codecCtx = NULL;
		AVCodec*  codec;
		AVFrame * frame = NULL;
		AVFrame*  frameRgb = NULL;
		AVPacket  packet;
		Byte*  buffer;
		Byte* inbuf;
		int videoindex;
		struct SwsContext* img_convert_ctx = NULL;
		static Bool ffmpegRegisted;

	public:
		Pixmap* pixmap;
		Bool isPlaying;
		Float progress;
		Float duration;
		Float time;

	};

}


#endif