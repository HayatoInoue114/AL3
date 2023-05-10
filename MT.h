#pragma once
#include<math.h>
#include<assert.h>
#include<cmath>
#include <Vector3.h>
#include <Matrix4x4.h>



// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);
// 内積
float Dot(const Vector3& v1, const Vector3& v2);
// 長さ(ノルム)
float Length(const Vector3& v);
// 正規化
Vector3 Normalize(const Vector3& v);

static const int kColumnWidth = 60;
//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);


// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 単位行列の作成
Matrix4x4 MakeIdentity4x4();

//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);