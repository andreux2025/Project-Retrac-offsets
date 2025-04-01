bool IsVisible(uintptr_t mesh)
{
	float LastSubmitTime = read<float>(mesh + 0x278);
	float LastRenderTimeOnScreen = read<float>(mesh + 0x280);
	return LastRenderTimeOnScreen + 0.06f >= LastSubmitTime;
}
