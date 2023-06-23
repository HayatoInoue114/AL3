#include "MT.h"

#include <assert.h>
#include <cmath>
#include <math.h>



Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return num;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return num;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 num = {scalar * v.x, scalar * v.y, scalar * v.z};
	return num;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float num = {v1.x * v2.x + v1.y * v2.y + v1.z * v2.z};
	return num;
}

float Length(const Vector3& v) {
	float num = {sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)};
	return num;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 num = {v.x / Length(v), v.y / Length(v), v.z / Length(v)};
	return num;
}

//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
//}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 mat = {m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[1][1], m1.m[0][2] + m2.m[0][2],
	                 m1.m[0][3] + m2.m[0][3], m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1],
	                 m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3], m1.m[2][0] + m2.m[2][0],
	                 m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
	                 m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2],
	                 m1.m[3][3] + m2.m[3][3]};
	return mat;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 mat = {m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[1][1], m1.m[0][2] - m2.m[0][2],
	                 m1.m[0][3] - m2.m[0][3], m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1],
	                 m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3], m1.m[2][0] - m2.m[2][0],
	                 m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
	                 m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2],
	                 m1.m[3][3] - m2.m[3][3]};
	return mat;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 mat = {
	    m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
	        m1.m[0][3] * m2.m[3][0],
	    m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
	        m1.m[0][3] * m2.m[3][1],
	    m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
	        m1.m[0][3] * m2.m[3][2],
	    m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][1] * m2.m[2][3] +
	        m1.m[0][3] * m2.m[3][3],
	    m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
	        m1.m[1][3] * m2.m[3][0],
	    m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
	        m1.m[1][3] * m2.m[3][1],
	    m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
	        m1.m[1][3] * m2.m[3][2],
	    m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][1] * m2.m[2][3] +
	        m1.m[1][3] * m2.m[3][3],
	    m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
	        m1.m[2][3] * m2.m[3][0],
	    m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
	        m1.m[2][3] * m2.m[3][1],
	    m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
	        m1.m[2][3] * m2.m[3][2],
	    m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][1] * m2.m[2][3] +
	        m1.m[2][3] * m2.m[3][3],
	    m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
	        m1.m[3][3] * m2.m[3][0],
	    m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
	        m1.m[3][3] * m2.m[3][1],
	    m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
	        m1.m[3][3] * m2.m[3][2],
	    m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][1] * m2.m[2][3] +
	        m1.m[3][3] * m2.m[3][3]};
	return mat;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	float num = {
	    m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
	    m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
	    m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] +
	    m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +
	    m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
	    m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] +
	    m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
	    m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
	    m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
	    m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
	    m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] +
	    m.m[0][3] * m.m[1][1] * m.m[2][1] * m.m[3][0] -
	    m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] -
	    m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] -
	    m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
	    m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] -
	    m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] -
	    m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] -
	    m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] -
	    m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] -
	    m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] -
	    m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] -
	    m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
	    m.m[0][3] * m.m[1][1] * m.m[2][1] * m.m[3][0]};

	Matrix4x4 mat = {
	    1 / num *
	        (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
	         m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
	         m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1]),
	    1 / num *
	        (m.m[0][1] * m.m[2][3] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] +
	         m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][2] * m.m[3][3] -
	         m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]),
	    1 / num *
	        (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
	         m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] -
	         m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][3] * m.m[1][2] * m.m[3][1]),
	    1 / num *
	        (m.m[0][1] * m.m[1][3] * m.m[2][2] + m.m[0][2] * m.m[1][1] * m.m[2][3] +
	         m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][2] * m.m[2][3] -
	         m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]),

	    1 / num *
	        (m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[1][2] * m.m[2][0] * m.m[3][3] +
	         m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][0] * m.m[2][2] * m.m[3][3] -
	         m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]),
	    1 / num *
	        (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
	         m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] -
	         m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][3] * m.m[2][2] * m.m[3][0]),
	    1 / num *
	        (m.m[0][0] * m.m[1][3] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][3] +
	         m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][0] * m.m[1][2] * m.m[3][3] -
	         m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]),
	    1 / num *
	        (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
	         m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] -
	         m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][3] * m.m[1][2] * m.m[2][0]),

	    1 / num *
	        (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
	         m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
	         m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0]),
	    1 / num *
	        (m.m[0][0] * m.m[2][3] * m.m[3][1] + m.m[0][1] * m.m[2][0] * m.m[3][3] +
	         m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][0] * m.m[2][1] * m.m[3][3] -
	         m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]),
	    1 / num *
	        (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
	         m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] -
	         m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][3] * m.m[1][1] * m.m[3][0]),
	    1 / num *
	        (m.m[0][0] * m.m[1][3] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] +
	         m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][0] * m.m[1][1] * m.m[2][3] -
	         m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]),

	    1 / num *
	        (m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[1][1] * m.m[2][0] * m.m[3][2] +
	         m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][0] * m.m[2][1] * m.m[3][2] -
	         m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]),
	    1 / num *
	        (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
	         m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] -
	         m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][2] * m.m[1][0] * m.m[3][0]),
	    1 / num *
	        (m.m[0][0] * m.m[1][2] * m.m[3][1] + m.m[0][1] * m.m[1][0] * m.m[3][2] +
	         m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][0] * m.m[1][1] * m.m[3][2] -
	         m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]),
	    1 / num *
	        (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
	         m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] -
	         m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[1][1] * m.m[2][0])};
	return mat;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 mat = {m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1], m.m[1][1],
	                 m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
	                 m.m[0][3], m.m[0][3], m.m[2][3], m.m[3][3]};
	return mat;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 mat = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	                 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return mat;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 mat = {1,
	                 0,
	                 0,
	                 0,
	                 0,
	                 std::cosf(radian),
	                 std::sinf(radian),
	                 0,
	                 0,
	                 -std::sinf(radian),
	                 std::cosf(radian),
	                 0,
	                 0,
	                 0,
	                 0,
	                 1};
	return mat;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 mat = {std::cosf(radian), 0, -std::sinf(radian), 0, 0, 1, 0, 0,
	                 std::sinf(radian), 0, std::cosf(radian),  0, 0, 0, 0, 1};
	return mat;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 mat = {
	    std::cosf(radian),
	    std::sinf(radian),
	    0,
	    0,
	    -std::sinf(radian),
	    std::cosf(radian),
	    0,
	    0,
	    0,
	    0,
	    1,
	    0,
	    0,
	    0,
	    0,
	    1};
	return mat;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 mat = {
	    scale.x * rotateMatrix.m[0][0],scale.x * rotateMatrix.m[0][1],scale.x * rotateMatrix.m[0][2],0,
	    scale.y * rotateMatrix.m[1][0],scale.y * rotateMatrix.m[1][1],scale.y * rotateMatrix.m[1][2],0,
	    scale.z * rotateMatrix.m[2][0],scale.z * rotateMatrix.m[2][1],scale.z * rotateMatrix.m[2][2],0,
	    translate.x,translate.y,translate.z,1
	};
	return mat;
}

//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0; column < 4; ++column) {
//			Novice::ScreenPrintf(
//			    x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
//		}
//	}
//}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 mat = {
	    (1 / aspectRatio) * (1 / std::tanf(fovY / 2)),
	    0,
	    0,
	    0,
	    0,
	    1 / std::tanf(fovY / 2),
	    0,
	    0,
	    0,
	    0,
	    farClip / (farClip - nearClip),
	    1,
	    0,
	    0,
	    (-nearClip * farClip) / (farClip - nearClip),
	    0};
	return mat;
}

Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 mat = {
	    2 / (right - left),
	    0,
	    0,
	    0,
	    0,
	    2 / (top - bottom),
	    0,
	    0,
	    0,
	    0,
	    1 / (farClip - nearClip),
	    0,
	    (left + right) / (left - right),
	    (top + bottom) / (bottom - top),
	    nearClip / (nearClip - farClip),
	    1};
	return mat;
}

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 mat = {
	    width / 2,
	    0,
	    0,
	    0,
	    0,
	    -height / 2,
	    0,
	    0,
	    0,
	    0,
	    maxDepth - minDepth,
	    0,
	    left + width / 2,
	    top + height / 2,
	    minDepth,
	    1};
	return mat;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 num = {};
	num.x = v1.y * v2.z - v1.z * v2.y;
	num.y = v1.z * v2.x - v1.x * v2.z;
	num.z = v1.x * v2.y - v1.y * v2.x;

	return num;
}

Vector3 TransformNormal(const Vector3& v,const Matrix4x4& m) {
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}