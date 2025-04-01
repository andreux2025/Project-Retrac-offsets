// working!
Vector3 GetEntityBone(uintptr_t mesh, int bone_id)
{
	uintptr_t BoneArray = read<uintptr_t>(mesh + BONE_ARRAY);
	if (BoneArray == NULL) BoneArray = read<uintptr_t>(mesh + BONE_ARRAY + 0x10);
	FTransform bone = read<FTransform>(BoneArray + (bone_id * 0x30));
	FTransform ComponentToWorld = read<FTransform>(mesh + COMPONENT_TO_WORLD);
	D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(matrix._41, matrix._42, matrix._43);
