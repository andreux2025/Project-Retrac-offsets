// here the sdk.h for the (FOR EXTERNALS NOT THE SDK OF FORTNITE)

#pragma once
#include <d3d9.h>
#include <vector>
#include "ImGui/imgui.h"
#include "ida.hpp"

#define M_PI 3.14159265358979323846264338327950288419716939937510

class Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	~Vector2() {}
	double x, y;
};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	bool OnScreen()
	{
		return (x > 0 && x < Settings::Width && y > 0 && y < Settings::Height);
	}

	ImVec2 ToImVec2()
	{
		return { (float)x, (float)y };
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float number) const
	{
		return Vector3(x * number, y * number, z * number);
	}
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m{};
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;
		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;
		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;
		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;
		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;
		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;
		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pm1, D3DMATRIX pm2)
{
	D3DMATRIX pout{};
	pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
	pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
	pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
	pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
	pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
	pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
	pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
	pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
	pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
	pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
	pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
	pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
	pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
	pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
	pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
	pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;
	return pout;
}

D3DMATRIX ToMatrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radpitch = (rot.x * M_PI / 180);
	float radyaw = (rot.y * M_PI / 180);
	float radroll = (rot.z * M_PI / 180);
	float sp = sinf(radpitch);
	float cp = cosf(radpitch);
	float sy = sinf(radyaw);
	float cy = cosf(radyaw);
	float sr = sinf(radroll);
	float cr = cosf(radroll);
	D3DMATRIX matrix{};
	matrix.m[0][0] = cp * cy;
	matrix.m[0][1] = cp * sy;
	matrix.m[0][2] = sp;
	matrix.m[0][3] = 0.f;
	matrix.m[1][0] = sr * sp * cy - cr * sy;
	matrix.m[1][1] = sr * sp * sy + cr * cy;
	matrix.m[1][2] = -sr * cp;
	matrix.m[1][3] = 0.f;
	matrix.m[2][0] = -(cr * sp * cy + sr * sy);
	matrix.m[2][1] = cy * sr - cr * sp * sy;
	matrix.m[2][2] = cr * cp;
	matrix.m[2][3] = 0.f;
	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;
	return matrix;
}

struct Camera
{
	Vector3 location;
	Vector3 rotation;
	float fov;
};

struct FNRot
{
	double a;
	char pad_0008[24];
	double b;
	char pad_0028[424];
	double c;
};

namespace Cache
{
	inline uintptr_t Uworld;
	inline uintptr_t GameInstance;
	inline uintptr_t LocalPlayers;
	inline uintptr_t PlayerController;
	inline uintptr_t LocalPawn;
	inline uintptr_t RootComponent;
	inline Vector3 RelativeLocation;
	inline uintptr_t PlayerState;
	inline int MyTeamID;
	inline uintptr_t GameState;
	inline uintptr_t PlayerArray;
	inline int PlayerCount;
	inline float ClosestDistance;
	inline uintptr_t ClosestActor;
	inline uintptr_t ClosestPawn;
	inline Camera LocalCamera;
}

Camera GetCamera()
{
	Camera camera {};
	uintptr_t LocationPointer = read<uintptr_t>(Cache::Uworld + 0x110);
	uintptr_t RotationPointer = read<uintptr_t>(Cache::Uworld + 0x120);
	FNRot Rot{};
	Rot.a = read<double>(RotationPointer);
	Rot.b = read<double>(RotationPointer + 0x20);
	Rot.c = read<double>(RotationPointer + 0x1D0);
	camera.location = read<Vector3>(LocationPointer);
	camera.rotation.x = asin(Rot.c) * (180.0 / M_PI);
	camera.rotation.y = ((atan2(Rot.a * -1, Rot.b) * (180.0 / M_PI)) * -1) * -1;
	camera.fov = read<float>(Cache::PlayerController + 0x394) * 90.f;
	return camera;
}

Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Camera;

	auto chain69 = read<uintptr_t>(Cache::LocalPlayers + 0xa8);
	uint64_t chain699 = read<uintptr_t>(chain69 + 8);

	Camera.x = read<float>(chain699 + 0x6E8);
	Camera.y = read<float>(Cache::RootComponent + 0x12C);

	float test = asin(Camera.x);
	float degrees = test * (180.0 / M_PI);
	Camera.x = degrees;

	if (Camera.y < 0)
		Camera.y = 360 + Camera.y;

	D3DMATRIX tempMatrix = ToMatrix(Camera);
	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	uint64_t chain = read<uint64_t>(Cache::LocalPlayers + 0x70);
	uint64_t chain1 = read<uint64_t>(chain + 0x98);
	uint64_t chain2 = read<uint64_t>(chain1 + 0x130);

	Vector3 vDelta = WorldLocation - read<Vector3>(chain2 + 0x10);
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float zoom = read<float>(chain699 + 0x500);

	float FovAngle = 80.0f / (zoom / 1.19f);

	float ScreenCenterX = Settings::Width / 2.0f;
	float ScreenCenterY = Settings::Height / 2.0f;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}

Vector3 GetEntityBone(uintptr_t mesh, int bone_id)
{
	uintptr_t BoneArray = read<uintptr_t>(mesh + BONE_ARRAY);
	if (BoneArray == NULL) BoneArray = read<uintptr_t>(mesh + BONE_ARRAY + 0x10);
	FTransform bone = read<FTransform>(BoneArray + (bone_id * 0x30));
	FTransform ComponentToWorld = read<FTransform>(mesh + COMPONENT_TO_WORLD);
	D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(matrix._41, matrix._42, matrix._43);
}

bool IsVisible(uintptr_t mesh)
{
	float LastSubmitTime = read<float>(mesh + 0x278);
	float LastRenderTimeOnScreen = read<float>(mesh + 0x280);
	return LastRenderTimeOnScreen + 0.06f >= LastSubmitTime;
}

std::string GetDisplayName(uintptr_t PawnPrivate)
{
	auto PlayerWeapon = read<uint64_t>(PawnPrivate + CURRENTWEAPON);
	auto WeaponData = read<uint64_t>(PlayerWeapon + WEAPONDATA);
	auto DisplayName = read<uintptr_t>(WeaponData + DISPLAYNAME);
	auto iWeaponLength = read<uint32_t>(DisplayName + 0x30);
	std::vector<wchar_t> wcWeaponName(iWeaponLength + 1);

	if (wcWeaponName.data())
		ReadArray(read<uintptr_t>(DisplayName + 0x28), wcWeaponName.data(), iWeaponLength * sizeof(wchar_t));

	std::wstring wWeaponString(wcWeaponName.data());
	wcWeaponName.clear();
	return std::string(wWeaponString.begin(), wWeaponString.end());
}

ImColor GetWeaponColor(uintptr_t WeaponData)
{
	uint8_t Tier = read<uint8_t>(WeaponData + TIER);

	switch (Tier)
	{
	case 0:
		return { 200, 200, 200, 233 };
		break;
	case 1:
		return { 200, 200, 200, 233 };
		break;
	case 2:
		return { 50, 215, 50, 255 };
		break;
	case 3:
		return { 163, 53, 238, 255 };
		break;
	case 4:
		return { 250, 135, 0, 255 };
		break;
	case 5:
		return { 255, 255, 0, 255 };
		break;

	case 6:
		return { 0, 200, 255, 255 };
		break;
	}


	return { 255, 255, 255 };
}

ImColor WeaponColor(uintptr_t Player)
{
	uint64_t CurrentWeapon = read<uint64_t>(Player + CURRENTWEAPON);
	ImColor ReturnedColor = ImColor(255, 255, 255);

	if (CurrentWeapon)
	{
		uint64_t WeaponData = read<uint64_t>(CurrentWeapon + WEAPONDATA);

		if (WeaponData)
		{
			ReturnedColor = GetWeaponColor(WeaponData);
		}
	}

	return ReturnedColor;
}

std::string GetPlayerName(uintptr_t PlayerState)
{
	auto fString = read<__int64>(PlayerState + NAME);
	auto iLength = read<int>(fString + 16);

	auto v6 = (__int64)iLength;
	if (!v6)
		return std::string(_("AI"));

	auto fText = read<__int64>(fString + 8);

	std::vector<wchar_t> wcBuffer(iLength);
	ReadArray(fText, wcBuffer.data(), iLength * sizeof(wchar_t));

	char v21;
	int v22;
	int i;
	int v25;
	_WORD* v23;

	v21 = v6 - 1;
	if (!(_DWORD)v6)
		v21 = 0;
	v22 = 0;
	v23 = (_WORD*)wcBuffer.data();
	for (i = (v21) & 3; ; *v23++ += i & 7)
	{
		v25 = v6 - 1;
		if (!(_DWORD)v6)
			v25 = 0;
		if (v22 >= v25)
			break;
		i += 3;
		++v22;
	}

	std::wstring wsUsername{ wcBuffer.data() };
	wcBuffer.clear();
	return std::string(wsUsername.begin(), wsUsername.end());
}

void ArrowIndicator(ImVec2 vScreenPosition)
{
	auto vCenter = ImVec2(Settings::Width / 2, Settings::Height / 2);
	float fAngle = atan2f(vScreenPosition.y - vCenter.y, vScreenPosition.x - vCenter.x);

	ImVec2 vArrowPosition;
	vArrowPosition.x = vCenter.x + ((Settings::Aimbot::FieldOfView + Settings::Visuals::GameFOV)*cosf(fAngle));
	vArrowPosition.y = vCenter.y + ((Settings::Aimbot::FieldOfView + Settings::Visuals::GameFOV)*sinf(fAngle));

	float fRotationAngle = fAngle - ImGui::GetIO().DeltaTime;

	ImVec2 vVertex[3] =
	{
		ImVec2(vArrowPosition.x + cosf(fRotationAngle) * 25, vArrowPosition.y + sinf(fRotationAngle) * 25),
		ImVec2(vArrowPosition.x + cosf(fRotationAngle - 1.5f) * 8.0f, vArrowPosition.y + sinf(fRotationAngle - 1.5f) * 8.0f),
		ImVec2(vArrowPosition.x + cosf(fRotationAngle + 1.5f) * 8.0f, vArrowPosition.y + sinf(fRotationAngle + 1.5f) * 8.0f)
	};

	ImGui::GetForegroundDrawList()->AddTriangleFilled(vVertex[0], vVertex[1], vVertex[2], ImColor(255, 255, 255, 255));
}

bool IsShotable(Vector3 lur, Vector3 bone)
{
	if (lur.x >= bone.x - 20 && lur.x <= bone.x + 20 && lur.y >= bone.y - 20 && lur.y <= bone.y + 20 && lur.z >= bone.z - 30 && lur.z <= bone.z + 30) return true;
	else return false;
}
