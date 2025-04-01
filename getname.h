std::string GetPlayerName(uintptr_t PlayerState)
{
	auto fString = read<__int64>(PlayerState + FIND OFFSET LIL NIG@ I DONT HAVE RIGHT 1 BUT THE RESET IS UPDATED);
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
