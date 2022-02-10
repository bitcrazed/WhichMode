#include "UIModeHelpers.h"

// Use scoped namespaces to avoid global namespace pollution:
namespace abi_vm = ABI::Windows::UI::ViewManagement;
namespace wf = Windows::Foundation;
namespace wrl = Microsoft::WRL;

BOOL IsSystemUIDarkMode()
{
	DWORD background{ GetUIBackgroundColor() };

	BOOL luminance = CalculatePercievedLuminance(background);
	return luminance < 127;
};

double CalculatePercievedLuminance(DWORD argbColor)
{
	// Decode ARGB values
	BYTE A{ static_cast<BYTE>((argbColor & 0xff000000) >> 24) };
	BYTE R{ static_cast<BYTE>((argbColor & 0x00ff0000) >> 16) };
	BYTE G{ static_cast<BYTE>((argbColor & 0x0000ff00) >> 8) };
	BYTE B{ static_cast<BYTE>((argbColor & 0x000000ff)) };

	// Calculate perceived luminance (source: https://www.w3.org/TR/AERT/#color-contrast)
	double Y{ (0.299 * R) + (0.587 * G) + (0.114 * B) };
	return Y;
}

COLORREF GetUIBackgroundColor()
{
	return GetUIColorValue(abi_vm::UIColorType_Background);
}

COLORREF GetUIForegroundColor()
{
	return GetUIColorValue(abi_vm::UIColorType_Foreground);
}

COLORREF GetUIColorValue(int colorType)
{
	// Thanks to Raymond Chen for the tips on how to find the 
	// system UI's dark/light mode colors: 
	// https://devblogs.microsoft.com/oldnewthing/20170405-00/?p=95905

	wrl::ComPtr<abi_vm::IUISettings3> settings;
	ABI::Windows::UI::Color color{ 0xff, 0xff, 0xff, 0xff };

	if (SUCCEEDED(wf::ActivateInstance(wrl::Wrappers::HStringReference(RuntimeClass_Windows_UI_ViewManagement_UISettings).Get(), &settings)))
	{
		settings->GetColorValue((abi_vm::UIColorType)colorType, &color);
	}

	// Convert color struct into COLORREF (DWORD), discarding A:
	COLORREF result{ DWORD(0x00 << 24 | color.R << 16 | color.G << 8 | color.B) };

	return result;
}