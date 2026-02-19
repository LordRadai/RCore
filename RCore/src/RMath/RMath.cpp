#include "RMath.h"
#include <math.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

DirectX::XMMATRIX RMath::getRotationMatrixFromLookAtVector(DirectX::SimpleMath::Vector3 lookAt)
{
	Vector3 forward = lookAt;
	Vector3 right = forward.Cross(Vector3::UnitY);
	Vector3 up = forward.Cross(right);

	forward.Normalize();
	right.Normalize();
	up.Normalize();

	return Matrix(right, up, forward);
}


DirectX::XMMATRIX RMath::getRotationMatrixFromWorldMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMMATRIX rotation = m_world;

	rotation.r[3].m128_f32[0] = 0;
	rotation.r[3].m128_f32[1] = 0;
	rotation.r[3].m128_f32[2] = 0;
	rotation.r[3].m128_f32[3] = 1;

	return rotation;
}

DirectX::XMMATRIX RMath::getRotationFrom2Vectors(DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB)
{
	Vector3 top = (pointA.y > pointB.y) ? pointA : pointB;
	Vector3 bottom = (pointA.y > pointB.y) ? pointB : pointA;

	// Compute capsule axis direction
	Vector3 dir = top - bottom;
	float length = dir.Length();
	if (length < 1e-6f)
		return XMMatrixIdentity();

	dir.Normalize();

	Vector3 modelForward(0, 1, 0);

	// Check if already aligned or opposite
	float dot = modelForward.Dot(dir);
	if (fabs(dot - 1.0f) < 1e-6f)
	{
		// Already aligned
		return XMMatrixIdentity();
	}
	if (fabs(dot + 1.0f) < 1e-6f)
	{
		// Opposite direction
		return XMMatrixRotationX(XM_PI);
	}

	// Compute rotation axis and angle
	Vector3 axis = modelForward.Cross(dir);
	axis.Normalize();
	float angle = acos(dot);

	// Create rotation matrix
	return XMMatrixRotationAxis(XMLoadFloat3(&axis), angle);
}

DirectX::SimpleMath::Vector3 RMath::getYawPitchRollFromMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMVECTOR from(DirectX::XMVectorSet(m_world.r[0].m128_f32[1], m_world.r[2].m128_f32[0], 0.0f, 0.0f));
	DirectX::XMVECTOR to(DirectX::XMVectorSet(m_world.r[1].m128_f32[1], m_world.r[2].m128_f32[2], 0.0f, 0.0f));
	DirectX::XMVECTOR res(DirectX::XMVectorATan2(from, to));

	float yaw = DirectX::XMVectorGetY(res);
	float pitch = DirectX::XMScalarASin(-m_world.r[2].m128_f32[2]);
	float roll = DirectX::XMVectorGetX(res);

	return DirectX::SimpleMath::Vector3(roll, pitch, yaw);
}

DirectX::SimpleMath::Vector3 RMath::getLookAtVectorFromMatrix(DirectX::XMMATRIX m_world)
{
	DirectX::XMMATRIX rotation = RMath::getRotationMatrixFromWorldMatrix(m_world);

	DirectX:XMVECTOR transformed_pos = DirectX::SimpleMath::Vector3(0, 0, 1);
	transformed_pos = DirectX::XMVector3Transform(transformed_pos, rotation);

	return DirectX::SimpleMath::Vector3(transformed_pos);
}

//Converts quaternion to euler angles
DirectX::SimpleMath::Vector3 RMath::convertQuatToEulerAngles(const DirectX::SimpleMath::Quaternion& quaternion)
{
	DirectX::SimpleMath::Vector3 eulerAngles;
	DirectX::SimpleMath::Matrix rotationMatrix = DirectX::XMMatrixRotationQuaternion(quaternion);

	eulerAngles.x = atan2f(rotationMatrix._32, rotationMatrix._33); // Pitch
	eulerAngles.y = asinf(-rotationMatrix._31); // Yaw
	eulerAngles.z = atan2f(rotationMatrix._21, rotationMatrix._11); // Roll

	return eulerAngles;
}

float RMath::degToRad(float angle)
{
	return ((angle / 360.f) * XM_2PI);
}

float RMath::radToDeg(float angle)
{
	return ((angle / XM_2PI) * 360.f);
}

DirectX::SimpleMath::Vector4 RMath::getFloatColor(const UINT color)
{
	Vector4 colorVec;

	colorVec.w = ((color >> 24) & 0xFF) / 255.0f;  // Extract Alpha
	colorVec.z = ((color >> 16) & 0xFF) / 255.0f;  // Extract Red
	colorVec.y = ((color >> 8) & 0xFF) / 255.0f;   // Extract Green
	colorVec.x = (color & 0xFF) / 255.0f;          // Extract Blue

	return colorVec;
}

DirectX::SimpleMath::Vector4 RMath::getFloatColor(const BYTE* pColor)
{
	return getFloatColor(pColor[0], pColor[1], pColor[2], pColor[3]);
}

DirectX::SimpleMath::Vector4 RMath::getFloatColor(const BYTE r, const BYTE g, const BYTE b, const BYTE a)
{
	Vector4 colorVec;

	colorVec.w = a / 255.0f;	// Extract Alpha
	colorVec.z = b / 255.0f;	// Extract Red
	colorVec.y = g / 255.0f;	// Extract Green
	colorVec.x = r / 255.0f;	// Extract Blue

	return colorVec;
}

UINT RMath::getHexColor(DirectX::SimpleMath::Vector4 color)
{
	BYTE red = color.x * 255;
	BYTE green = color.y * 255;
	BYTE blue = color.z * 255;
	BYTE alpha = color.w * 255;

	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

//Converts floating point time value to discrete frame count
float RMath::frameToTime(int frame, int frameRate)
{
	return ((float)frame / (float)frameRate);
}

//Converts discrete frame count to a floating point time value
int RMath::timeToFrame(float time, int frameRate)
{
	return std::roundf(time * frameRate);
}