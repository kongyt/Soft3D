#include "Matrix4.h"

namespace Soft3D {

	Matrix4::Matrix4() {
		for (int i = 0; i < 16; i++) {
			this->data[i] = 0.0f;
		}
	}

	Matrix4::Matrix4(Float data[16]) {
		for (int i = 0; i < 16; i++) {
			this->data[i] = data[i];
		}
	}

	Matrix4* Matrix4::Clone() {
		return new Matrix4(data);
	}

	Matrix4& Matrix4::Add(const Matrix4& mat4) {
		for (int i = 0; i < 16; i++) {
			data[i] += mat4.data[i];
		}

		return *this;
	}
	
	Matrix4& Matrix4::Sub(const Matrix4& mat4) {
		for (int i = 0; i < 16; i++) {
			data[i] -= mat4.data[i];
		}

		return *this;
	}

	Matrix4& Matrix4::Mul(const Matrix4& mat4) {
		Float old_data[16];

		for (int i = 0; i < 16; i++) {
			old_data[i] = data[i];
		}

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				for (int k = 0; k < 4; k++) {
					this->data[row + col * 4] += old_data[row + k * 4] * mat4.data[k + col * 4];
				}
			}
		}

		return *this;
	}

	Matrix4& Matrix4::Identity() {
		data[M00] = 1.0f;	data[M01] = 0.0f;	data[M02] = 0.0f;	data[M03] = 0.0f;
		data[M10] = 0.0f;	data[M11] = 1.0f;	data[M12] = 0.0f;	data[M13] = 0.0f;
		data[M20] = 0.0f;	data[M21] = 0.0f;	data[M22] = 1.0f;	data[M23] = 0.0f;
		data[M30] = 0.0f;	data[M31] = 0.0f;	data[M32] = 0.0f;	data[M33] = 1.0f;

		return *this;
	}

	Matrix4& Matrix4::Inverse() {
		Float l_det = data[M30] * data[M21] * data[M12] * data[M03] - data[M20] * data[M31] * data[M12] * data[M03] - data[M30] * data[M11]
			* data[M22] * data[M03] + data[M10] * data[M31] * data[M22] * data[M03] + data[M20] * data[M11] * data[M32] * data[M03] - data[M10]
			* data[M21] * data[M32] * data[M03] - data[M30] * data[M21] * data[M02] * data[M13] + data[M20] * data[M31] * data[M02] * data[M13]
			+ data[M30] * data[M01] * data[M22] * data[M13] - data[M00] * data[M31] * data[M22] * data[M13] - data[M20] * data[M01] * data[M32]
			* data[M13] + data[M00] * data[M21] * data[M32] * data[M13] + data[M30] * data[M11] * data[M02] * data[M23] - data[M10] * data[M31]
			* data[M02] * data[M23] - data[M30] * data[M01] * data[M12] * data[M23] + data[M00] * data[M31] * data[M12] * data[M23] + data[M10]
			* data[M01] * data[M32] * data[M23] - data[M00] * data[M11] * data[M32] * data[M23] - data[M20] * data[M11] * data[M02] * data[M33]
			+ data[M10] * data[M21] * data[M02] * data[M33] + data[M20] * data[M01] * data[M12] * data[M33] - data[M00] * data[M21] * data[M12]
			* data[M33] - data[M10] * data[M01] * data[M22] * data[M33] + data[M00] * data[M11] * data[M22] * data[M33];

		if (MathUtils::IsZero(l_det) == false) {
			Float inv_det = 1.0f / l_det;
			Float tmp[16] = { 0 };
			tmp[M00] = data[M12] * data[M23] * data[M31] - data[M13] * data[M22] * data[M31] + data[M13] * data[M21] * data[M32] - data[M11]
				* data[M23] * data[M32] - data[M12] * data[M21] * data[M33] + data[M11] * data[M22] * data[M33];
			tmp[M01] = data[M03] * data[M22] * data[M31] - data[M02] * data[M23] * data[M31] - data[M03] * data[M21] * data[M32] + data[M01]
				* data[M23] * data[M32] + data[M02] * data[M21] * data[M33] - data[M01] * data[M22] * data[M33];
			tmp[M02] = data[M02] * data[M13] * data[M31] - data[M03] * data[M12] * data[M31] + data[M03] * data[M11] * data[M32] - data[M01]
				* data[M13] * data[M32] - data[M02] * data[M11] * data[M33] + data[M01] * data[M12] * data[M33];
			tmp[M03] = data[M03] * data[M12] * data[M21] - data[M02] * data[M13] * data[M21] - data[M03] * data[M11] * data[M22] + data[M01]
				* data[M13] * data[M22] + data[M02] * data[M11] * data[M23] - data[M01] * data[M12] * data[M23];
			tmp[M10] = data[M13] * data[M22] * data[M30] - data[M12] * data[M23] * data[M30] - data[M13] * data[M20] * data[M32] + data[M10]
				* data[M23] * data[M32] + data[M12] * data[M20] * data[M33] - data[M10] * data[M22] * data[M33];
			tmp[M11] = data[M02] * data[M23] * data[M30] - data[M03] * data[M22] * data[M30] + data[M03] * data[M20] * data[M32] - data[M00]
				* data[M23] * data[M32] - data[M02] * data[M20] * data[M33] + data[M00] * data[M22] * data[M33];
			tmp[M12] = data[M03] * data[M12] * data[M30] - data[M02] * data[M13] * data[M30] - data[M03] * data[M10] * data[M32] + data[M00]
				* data[M13] * data[M32] + data[M02] * data[M10] * data[M33] - data[M00] * data[M12] * data[M33];
			tmp[M13] = data[M02] * data[M13] * data[M20] - data[M03] * data[M12] * data[M20] + data[M03] * data[M10] * data[M22] - data[M00]
				* data[M13] * data[M22] - data[M02] * data[M10] * data[M23] + data[M00] * data[M12] * data[M23];
			tmp[M20] = data[M11] * data[M23] * data[M30] - data[M13] * data[M21] * data[M30] + data[M13] * data[M20] * data[M31] - data[M10]
				* data[M23] * data[M31] - data[M11] * data[M20] * data[M33] + data[M10] * data[M21] * data[M33];
			tmp[M21] = data[M03] * data[M21] * data[M30] - data[M01] * data[M23] * data[M30] - data[M03] * data[M20] * data[M31] + data[M00]
				* data[M23] * data[M31] + data[M01] * data[M20] * data[M33] - data[M00] * data[M21] * data[M33];
			tmp[M22] = data[M01] * data[M13] * data[M30] - data[M03] * data[M11] * data[M30] + data[M03] * data[M10] * data[M31] - data[M00]
				* data[M13] * data[M31] - data[M01] * data[M10] * data[M33] + data[M00] * data[M11] * data[M33];
			tmp[M23] = data[M03] * data[M11] * data[M20] - data[M01] * data[M13] * data[M20] - data[M03] * data[M10] * data[M21] + data[M00]
				* data[M13] * data[M21] + data[M01] * data[M10] * data[M23] - data[M00] * data[M11] * data[M23];
			tmp[M30] = data[M12] * data[M21] * data[M30] - data[M11] * data[M22] * data[M30] - data[M12] * data[M20] * data[M31] + data[M10]
				* data[M22] * data[M31] + data[M11] * data[M20] * data[M32] - data[M10] * data[M21] * data[M32];
			tmp[M31] = data[M01] * data[M22] * data[M30] - data[M02] * data[M21] * data[M30] + data[M02] * data[M20] * data[M31] - data[M00]
				* data[M22] * data[M31] - data[M01] * data[M20] * data[M32] + data[M00] * data[M21] * data[M32];
			tmp[M32] = data[M02] * data[M11] * data[M30] - data[M01] * data[M12] * data[M30] - data[M02] * data[M10] * data[M31] + data[M00]
				* data[M12] * data[M31] + data[M01] * data[M10] * data[M32] - data[M00] * data[M11] * data[M32];
			tmp[M33] = data[M01] * data[M12] * data[M20] - data[M02] * data[M11] * data[M20] + data[M02] * data[M10] * data[M21] - data[M00]
				* data[M12] * data[M21] - data[M01] * data[M10] * data[M22] + data[M00] * data[M11] * data[M22];
			data[M00] = tmp[M00] * inv_det;
			data[M01] = tmp[M01] * inv_det;
			data[M02] = tmp[M02] * inv_det;
			data[M03] = tmp[M03] * inv_det;
			data[M10] = tmp[M10] * inv_det;
			data[M11] = tmp[M11] * inv_det;
			data[M12] = tmp[M12] * inv_det;
			data[M13] = tmp[M13] * inv_det;
			data[M20] = tmp[M20] * inv_det;
			data[M21] = tmp[M21] * inv_det;
			data[M22] = tmp[M22] * inv_det;
			data[M23] = tmp[M23] * inv_det;
			data[M30] = tmp[M30] * inv_det;
			data[M31] = tmp[M31] * inv_det;
			data[M32] = tmp[M32] * inv_det;
			data[M33] = tmp[M33] * inv_det;			

		}

		return *this;
	}

	Matrix4& Matrix4::Transpose() {
		Float tmp[16] = { 0.0f };
		for (int i = 0; i < 16; i++) {
			tmp[i] = data[i];
		}
		data[M00] = tmp[M00]; data[M01] = tmp[M10]; data[M02] = tmp[M20]; data[M03] = tmp[M30];
		data[M10] = tmp[M01]; data[M11] = tmp[M11]; data[M12] = tmp[M21]; data[M13] = tmp[M31];
		data[M20] = tmp[M02]; data[M21] = tmp[M12]; data[M22] = tmp[M22]; data[M23] = tmp[M32];
		data[M30] = tmp[M03]; data[M31] = tmp[M13]; data[M32] = tmp[M23]; data[M33] = tmp[M33];

		return *this;
	}

	Matrix4& Matrix4::SetScale(const Vector3& scale) {
		Identity();
		data[M00] = scale.a;
		data[M11] = scale.b;
		data[M22] = scale.c;

		return *this;
	}

	Matrix4& Matrix4::SetTranslate(const Vector3& trans) {
		Identity();
		data[M03] = trans.a;
		data[M13] = trans.b;
		data[M23] = trans.c;

		return *this;
	}

	Matrix4& Matrix4::Scale(const Vector3& scale) {
		data[M00] *= scale.a;
		data[M10] *= scale.a;
		data[M20] *= scale.a;
		data[M30] *= scale.a;

		data[M01] *= scale.b;
		data[M11] *= scale.b;
		data[M21] *= scale.b;
		data[M31] *= scale.b;

		data[M02] *= scale.c;
		data[M12] *= scale.c;
		data[M22] *= scale.c;
		data[M32] *= scale.c;

		return *this;
	}

	Matrix4& Matrix4::Translate(const Vector3& trans) {
		data[M03] = data[M00] * trans.a + data[M01] * trans.b + data[M02] * trans.c + data[M03];
		data[M13] = data[M10] * trans.a + data[M11] * trans.b + data[M12] * trans.c + data[M13];
		data[M23] = data[M20] * trans.a + data[M21] * trans.b + data[M22] * trans.c + data[M23];
		data[M33] = data[M30] * trans.a + data[M31] * trans.b + data[M32] * trans.c + data[M33];

		return *this;
	}

	Matrix4& Matrix4::RotateX(Float rotation) {
		Float cosTheta = cos(rotation / 180.0f * MathUtils::Pi());
		Float sinTheta = sin(rotation / 180.0f * MathUtils::Pi());

		Matrix4 tmp;
		tmp.data[M00] = 1.0f;
		tmp.data[M11] = cosTheta;
		tmp.data[M12] = -sinTheta;
		tmp.data[M21] = sinTheta;
		tmp.data[M22] = cosTheta;
		tmp.data[M33] = 1.0f;

		return this->Mul(tmp);
	}

	Matrix4& Matrix4::RotateY(Float rotation) {
		Float cosTheta = cos(rotation / 180.0f * MathUtils::Pi());
		Float sinTheta = sin(rotation / 180.0f * MathUtils::Pi());

		Matrix4 tmp;
		tmp.data[M00] = cosTheta;
		tmp.data[M20] = -sinTheta;
		tmp.data[M11] = 1.0f;
		tmp.data[M02] = sinTheta;
		tmp.data[M22] = cosTheta;
		tmp.data[M33] = 1.0f;

		return this->Mul(tmp);
	}

	Matrix4& Matrix4::RotateZ(Float rotation) {
		Float cosTheta = cos(rotation / 180.0f * MathUtils::Pi());
		Float sinTheta = sin(rotation / 180.0f * MathUtils::Pi());

		Matrix4 tmp;
		tmp.data[M00] = cosTheta;
		tmp.data[M01] = -sinTheta;
		tmp.data[M10] = sinTheta;
		tmp.data[M11] = cosTheta;
		tmp.data[M22] = 1.0f;
		tmp.data[M33] = 1.0f;

		return this->Mul(tmp);
	}	

}