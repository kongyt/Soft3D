#include "Matrix4.h"
#include "MathUtils.h"

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

	Matrix4& Matrix4::CopyData(const Matrix4& mat4) {
		for (int i = 0; i < 16; i++) {
			data[i] = mat4.data[i];
		}

		return *this;
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

		data[M00] = old_data[M00] * mat4.data[M00] + old_data[M01] * mat4.data[M10] + old_data[M02] * mat4.data[M20] + old_data[M03] * mat4.data[M30];
		data[M01] = old_data[M00] * mat4.data[M01] + old_data[M01] * mat4.data[M11] + old_data[M02] * mat4.data[M21] + old_data[M03] * mat4.data[M31];
		data[M02] = old_data[M00] * mat4.data[M02] + old_data[M01] * mat4.data[M12] + old_data[M02] * mat4.data[M22] + old_data[M03] * mat4.data[M32];
		data[M03] = old_data[M00] * mat4.data[M03] + old_data[M01] * mat4.data[M13] + old_data[M02] * mat4.data[M23] + old_data[M03] * mat4.data[M33];
		data[M10] = old_data[M10] * mat4.data[M00] + old_data[M11] * mat4.data[M10] + old_data[M12] * mat4.data[M20] + old_data[M13] * mat4.data[M30];
		data[M11] = old_data[M10] * mat4.data[M01] + old_data[M11] * mat4.data[M11] + old_data[M12] * mat4.data[M21] + old_data[M13] * mat4.data[M31];
		data[M12] = old_data[M10] * mat4.data[M02] + old_data[M11] * mat4.data[M12] + old_data[M12] * mat4.data[M22] + old_data[M13] * mat4.data[M32];
		data[M13] = old_data[M10] * mat4.data[M03] + old_data[M11] * mat4.data[M13] + old_data[M12] * mat4.data[M23] + old_data[M13] * mat4.data[M33];
		data[M20] = old_data[M20] * mat4.data[M00] + old_data[M21] * mat4.data[M10] + old_data[M22] * mat4.data[M20] + old_data[M23] * mat4.data[M30];
		data[M21] = old_data[M20] * mat4.data[M01] + old_data[M21] * mat4.data[M11] + old_data[M22] * mat4.data[M21] + old_data[M23] * mat4.data[M31];
		data[M22] = old_data[M20] * mat4.data[M02] + old_data[M21] * mat4.data[M12] + old_data[M22] * mat4.data[M22] + old_data[M23] * mat4.data[M32];
		data[M23] = old_data[M20] * mat4.data[M03] + old_data[M21] * mat4.data[M13] + old_data[M22] * mat4.data[M23] + old_data[M23] * mat4.data[M33];
		data[M30] = old_data[M30] * mat4.data[M00] + old_data[M31] * mat4.data[M10] + old_data[M32] * mat4.data[M20] + old_data[M33] * mat4.data[M30];
		data[M31] = old_data[M30] * mat4.data[M01] + old_data[M31] * mat4.data[M11] + old_data[M32] * mat4.data[M21] + old_data[M33] * mat4.data[M31];
		data[M32] = old_data[M30] * mat4.data[M02] + old_data[M31] * mat4.data[M12] + old_data[M32] * mat4.data[M22] + old_data[M33] * mat4.data[M32];
		data[M33] = old_data[M30] * mat4.data[M03] + old_data[M31] * mat4.data[M13] + old_data[M32] * mat4.data[M23] + old_data[M33] * mat4.data[M33];

		return *this;
	}

	Matrix4& Matrix4::Identity() {
		data[M00] = 1.0f;	data[M01] = 0.0f;	data[M02] = 0.0f;	data[M03] = 0.0f;
		data[M10] = 0.0f;	data[M11] = 1.0f;	data[M12] = 0.0f;	data[M13] = 0.0f;
		data[M20] = 0.0f;	data[M21] = 0.0f;	data[M22] = 1.0f;	data[M23] = 0.0f;
		data[M30] = 0.0f;	data[M31] = 0.0f;	data[M32] = 0.0f;	data[M33] = 1.0f;

		return *this;
	}

	Double Matrix4::Det() {
		return data[M30] * data[M21] * data[M12] * data[M03] - data[M20] * data[M31] * data[M12] * data[M03] - 
			data[M30] * data[M11] * data[M22] * data[M03] + data[M10] * data[M31] * data[M22] * data[M03] + 
			data[M20] * data[M11] * data[M32] * data[M03] - data[M10] * data[M21] * data[M32] * data[M03] - 
			data[M30] * data[M21] * data[M02] * data[M13] + data[M20] * data[M31] * data[M02] * data[M13] + 
			data[M30] * data[M01] * data[M22] * data[M13] - data[M00] * data[M31] * data[M22] * data[M13] - 
			data[M20] * data[M01] * data[M32] * data[M13] + data[M00] * data[M21] * data[M32] * data[M13] + 
			data[M30] * data[M11] * data[M02] * data[M23] - data[M10] * data[M31] * data[M02] * data[M23] -
			data[M30] * data[M01] * data[M12] * data[M23] + data[M00] * data[M31] * data[M12] * data[M23] + 
			data[M10] * data[M01] * data[M32] * data[M23] - data[M00] * data[M11] * data[M32] * data[M23] - 
			data[M20] * data[M11] * data[M02] * data[M33] + data[M10] * data[M21] * data[M02] * data[M33] + 
			data[M20] * data[M01] * data[M12] * data[M33] - data[M00] * data[M21] * data[M12] * data[M33] -
			data[M10] * data[M01] * data[M22] * data[M33] + data[M00] * data[M11] * data[M22] * data[M33];
	}

	Matrix4& Matrix4::Inverse() {
		Double l_det = Det();

		if (MathUtils::IsZero(l_det) == false) {	// double类型，float精度不够
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
			
			Float inv_det = 1.0f / l_det;
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
		data[M00] = scale.x;
		data[M11] = scale.y;
		data[M22] = scale.z;

		return *this;
	}

	Matrix4& Matrix4::SetTranslate(const Vector3& trans) {
		Identity();
		data[M03] = trans.x;
		data[M13] = trans.y;
		data[M23] = trans.z;

		return *this;
	}

	Matrix4& Matrix4::Scale(const Vector3& scale) {
		data[M00] *= scale.x;
		data[M10] *= scale.x;
		data[M20] *= scale.x;
		data[M30] *= scale.x;

		data[M01] *= scale.y;
		data[M11] *= scale.y;
		data[M21] *= scale.y;
		data[M31] *= scale.y;

		data[M02] *= scale.z;
		data[M12] *= scale.z;
		data[M22] *= scale.z;
		data[M32] *= scale.z;

		return *this;
	}

	Matrix4& Matrix4::Translate(const Vector3& trans) {
		data[M03] = data[M00] * trans.x + data[M01] * trans.y + data[M02] * trans.z + data[M03];
		data[M13] = data[M10] * trans.x + data[M11] * trans.y + data[M12] * trans.z + data[M13];
		data[M23] = data[M20] * trans.x + data[M21] * trans.y + data[M22] * trans.z + data[M23];
		data[M33] = data[M30] * trans.x + data[M31] * trans.y + data[M32] * trans.z + data[M33];

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

	void Matrix4::Prj(Vector3& point) {
		Float inv_w = 1.0f / (point.x * data[M30] + point.y * data[M31] + point.z * data[M32] + data[M33]);
		Float x = (point.x * data[M00] + point.y * data[M01] + point.z * data[M02] + data[M03]) * inv_w;
		Float y = (point.x * data[M10] + point.y * data[M11] + point.z * data[M12] + data[M13]) * inv_w;
		Float z = (point.x * data[M20] + point.y * data[M21] + point.z * data[M22] + data[M23]) * inv_w;
		point.x = x;
		point.y = y;
		point.z = z;
	}

	Matrix4& Matrix4::SetToProjection(Float near, Float far, Float fov, Float aspect) {
		Identity();
		Float l_fd = 1.0f / tanf(fov * (MathUtils::Pi() / 180.0f) / 2.0f);
		Float l_a1 = (far + near) / (near - far);
		Float l_a2 = (2 * far * near) / (near - far);
		data[M00] = l_fd / aspect;;
		data[M10] = 0;
		data[M20] = 0;
		data[M30] = 0;
		data[M01] = 0;
		data[M11] = l_fd; 
		data[M21] = 0;
		data[M31] = 0;
		data[M02] = 0;
		data[M12] = 0;
		data[M22] = l_a1;
		data[M32] = -1;
		data[M03] = 0;
		data[M13] = 0;
		data[M23] = l_a2;
		data[M33] = 0;

		return *this;
	}

	Matrix4& Matrix4::SetToOrtho2D(Float x, Float y, Float width, Float height) {
		return SetToOrtho(x, x + width, y, y + height, 0, 1);
	}

	Matrix4& Matrix4::SetToOrtho2D(Float x, Float y, Float width, Float height, Float near, Float far) {
		return SetToOrtho(x, x + width, y, y + height, near, far);
	}

	Matrix4& Matrix4::SetToOrtho(Float left, Float right, Float bottom, Float top, Float near, Float far) {
		Identity();
		Float x_orth = 2 / (right - left);
		Float y_orth = 2 / (top - bottom);
		Float z_orth = -2 / (far - near);

		Float tx = -(right + left) / (right - left);
		Float ty = -(top + bottom) / (top - bottom);
		Float tz = -(far + near) / (far - near);

		data[M00] = x_orth;
		data[M10] = 0;
		data[M20] = 0;
		data[M30] = 0;
		data[M01] = 0;
		data[M11] = y_orth;
		data[M21] = 0;
		data[M31] = 0;
		data[M02] = 0;
		data[M12] = 0;
		data[M22] = z_orth;
		data[M32] = 0;
		data[M03] = tx;
		data[M13] = ty;
		data[M23] = tz;
		data[M33] = 1;

		return *this;
	}

	Matrix4& Matrix4::SetToLookAt(const Vector3& direction, const Vector3& up) {
		Vector3 tmp1, tmp2, tmp3;
		tmp3.Set(direction).Nor();
		tmp1.Set(tmp3);
		tmp1.Crs(up).Nor();
		tmp2.Set(tmp1).Crs(tmp3).Nor();

		Identity();

		data[M00] = tmp1.x;
		data[M01] = tmp1.y;
		data[M02] = tmp1.z;
		data[M10] = tmp2.x;
		data[M11] = tmp2.y;
		data[M12] = tmp2.z;
		data[M20] = -tmp3.x;
		data[M21] = -tmp3.y;
		data[M22] = -tmp3.z;

		return *this;
	}

	Matrix4& Matrix4::SetToLookAt(const Vector3& position, const Vector3& target, const Vector3& up) {
		Vector3 tmp;
		tmp.Set(target).Sub(position);
		SetToLookAt(tmp, up);

		tmp.Set(position).Scl(-1.0f);

		this->Mul(Matrix4().SetToTranslation(tmp));

		return *this;
	}


	Matrix4& Matrix4::SetToTranslation(const Vector3& vector) {
		Identity();

		data[M03] = vector.x;
		data[M13] = vector.y;
		data[M23] = vector.z;

		return *this;
	}
}