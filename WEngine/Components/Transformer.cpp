#include "Transformer.h"

Transformer::Transformer()
	: Model(Matrix4x4f::GetIdentityMatrix()), ScaleMatrix(Matrix4x4f::GetIdentityMatrix()),
	RotateMatrix(Matrix4x4f::GetIdentityMatrix()), TranslateMatrix(Matrix4x4f::GetIdentityMatrix())
{
}

void Transformer::SetScale(Vec3 scale)
{
	m_scale = scale;
	Matrix4x4f model = Matrix4x4f::GetIdentityMatrix();
	Scale(model, scale);
	ScaleMatrix = model;
	Model = TranslateMatrix * RotateMatrix * ScaleMatrix;
}

void Transformer::SetRotate(Vec3 rotate)
{
	m_rotate = rotate;
	Matrix4x4f model = Matrix4x4f::GetIdentityMatrix();
	Rotate(model, rotate[0], Vec3(1.0f, 0.0f, 0.0f));
	Rotate(model, rotate[1], Vec3(0.0f, 1.0f, 0.0f));
	Rotate(model, rotate[2], Vec3(0.0f, 0.0f, 1.0f));
	RotateMatrix = model;
	Model = TranslateMatrix * RotateMatrix * ScaleMatrix;
}

void Transformer::SetTranslate(Vec3 translate)
{
	m_translate = translate;
	Matrix4x4f model = Matrix4x4f::GetIdentityMatrix();
	Translate(model, translate);
	TranslateMatrix = model;
	Model = TranslateMatrix * RotateMatrix * ScaleMatrix;
}

Matrix4x4f Transformer::GetModelMatrix()
{
	return Model;
}

