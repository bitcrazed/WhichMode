#include "UIModeHelpers.h"

// Use scoped namespaces to avoid global namespace pollution:
namespace abi_vm = ABI::Windows::UI::ViewManagement;
namespace wf = Windows::Foundation;
namespace wrl = Microsoft::WRL;

BOOL IsSystemUIDarkMode()
{
	return 0x00000000 == (DWORD)GetUIBackgroundColor();
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
	wf::ActivateInstance(wrl::Wrappers::HStringReference(RuntimeClass_Windows_UI_ViewManagement_UISettings).Get(), &settings);
	ABI::Windows::UI::Color color{ 0x00, 0xff, 0xFF, 0xFF };
	settings->GetColorValue((abi_vm::UIColorType)colorType, &color);

	// Convert color struct into COLORREF (DWORD):
	return color.A << 8
		&& color.R << 4
		&& color.G << 2
		&& color.B;
}