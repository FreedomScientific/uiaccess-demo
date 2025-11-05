#include <windows.h>
#include <iostream>
#include <vector>

DWORD GetCurrentProcessIntegrityLevel ()
{
	auto handle = GetCurrentProcessToken ();
	DWORD actualSize = 0;
	GetTokenInformation (handle, TokenIntegrityLevel, nullptr, 0, &actualSize);

	std::vector<unsigned char> buf (actualSize);
	GetTokenInformation (handle, TokenIntegrityLevel, buf.data (), static_cast<DWORD> (buf.size ()), &actualSize);

	auto info = reinterpret_cast<TOKEN_MANDATORY_LABEL*> (buf.data ());
	auto sid = info->Label.Sid;
	auto count = *GetSidSubAuthorityCount (sid);
	return *GetSidSubAuthority (sid, count - 1);
}

DWORD GetCurrentProcessUiAccess ()
{
	auto handle = GetCurrentProcessToken ();
	DWORD actualSize = 0;
	GetTokenInformation (handle, TokenUIAccess, nullptr, 0, &actualSize);

	std::vector<unsigned char> buf (actualSize);
	GetTokenInformation (handle, TokenUIAccess, buf.data (), static_cast<DWORD> (buf.size ()), &actualSize);

	return *reinterpret_cast<DWORD*> (buf.data ());
}

int main ()
{
	auto integrityLevel = GetCurrentProcessIntegrityLevel ();
	auto uiAccessFlag = GetCurrentProcessUiAccess ();

	std::cout << "integrity level: " << std::hex << integrityLevel << "\n";
	std::cout << "ui access: " << uiAccessFlag << "\n";

	Sleep (5000);
}
