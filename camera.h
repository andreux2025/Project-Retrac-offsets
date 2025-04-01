// UPDATED AND WORKING!
struct Camera
{
	Vector3 location;
	Vector3 rotation;
	float fov;
};

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
