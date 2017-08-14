#include <stdio.h>
#include <Windows.h>
#include "Debug.h"

namespace Soft3D {

	void Debug::Log(const char* message) {
		fprintf(stderr, "%s%s", message, "\n");
	}
	
	void Debug::Log(const String& message){
		fprintf(stderr, "%s%s",message.c_str(),"\n");
	}


	void Debug::Log(const Vector3& vec3) {
		fprintf(stderr, "Vector3(%f, %f, %f)\n", vec3.x, vec3.y, vec3.z);
	}

	void Debug::Log(const Color& color){
		fprintf(stderr, "Color(%f, %f, %f, %f)\n", color.r, color.g, color.b, color.a);
	}

	void Debug::Log(const Matrix4& mat4) {
		fprintf(stderr, "Matrix4(\n");
		fprintf(stderr, "  %f %f %f %f\n", mat4.data[M00], mat4.data[M01], mat4.data[M02], mat4.data[M03]);
		fprintf(stderr, "  %f %f %f %f\n", mat4.data[M10], mat4.data[M11], mat4.data[M12], mat4.data[M13]);
		fprintf(stderr, "  %f %f %f %f\n", mat4.data[M20], mat4.data[M21], mat4.data[M22], mat4.data[M23]);
		fprintf(stderr, "  %f %f %f %f\n", mat4.data[M30], mat4.data[M31], mat4.data[M32], mat4.data[M33]);
		fprintf(stderr, ")\n");
	}

	void Debug::Log(const Quaternion& quaternion) {
		fprintf(stderr, "Quaternion(%f, %f, %f, %f)\n", quaternion.x, quaternion.y, quaternion.z, quaternion.w);
	}

	void Debug::Error(const char* errMsg) {
		MessageBoxA(NULL, errMsg, "Error", MB_OK);
	}

	void Debug::Info(const char* infoMsg) {
		MessageBoxA(NULL, infoMsg, "Info", MB_OK);
	}

	char* Debug::ToString(const Matrix4& mat4) {
		char* buffer = new char[1024];
		snprintf(buffer, 1024, \
			"Matrix4(\n"\
			"  %f, %f, %f, %f\n"\
			"  %f, %f, %f, %f\n"\
			"  %f, %f, %f, %f\n"\
			"  %f, %f, %f, %f\n"\
			")\n"\
			, mat4.data[M00], mat4.data[M01], mat4.data[M02], mat4.data[M03]\
			, mat4.data[M10], mat4.data[M11], mat4.data[M12], mat4.data[M13]\
			, mat4.data[M20], mat4.data[M21], mat4.data[M22], mat4.data[M23]\
			, mat4.data[M30], mat4.data[M31], mat4.data[M32], mat4.data[M33]);
		return buffer;
	}

}