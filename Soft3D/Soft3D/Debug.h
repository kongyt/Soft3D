#ifndef _Debug_H__
#define _Debug_H__

#include "DllApi.h"
#include "Vector3.h"
#include "Color.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Soft3D {

	class DLLAPI Debug{
	public:
		static void Log(const char* message);
		static void Log(const String& message);
		static void Log(const Vector3& vec3);
		static void Log(const Color& color);
		static void Log(const Matrix4& mat4);
		static void Log(const Quaternion& quaternion);
		static void Error(const char* errMsg);
		static void Info(const char* infoMsg);
		static char* ToString(const Matrix4& mat4);

	};

}

#endif