#pragma once

// Required for WRL used by GetUIColorValue()
#include <windows.ui.viewmanagement.h>
#include <wrl\wrappers\corewrappers.h>
#include <wrl\client.h>

/// <summary>
/// Detects if Windows' system UI is in dark mode
/// </summary>
/// <returns>
///     TRUE if Windows' system UI is in dark mode
///     FALSE if Windows' system UI is in light mode
/// </returns>
BOOL		IsSystemUIDarkMode();

/// <summary>
/// Returns value of Windows' system light/dark background color
/// </summary>
/// <returns>COLORREF (0xAARRGGBB) value of color</returns>
COLORREF    GetUIBackgroundColor();

/// <summary>
/// Returns value of Windows' system light/dark foreground color
/// </summary>
/// <returns>COLORREF (0xAARRGGBB) value of color</returns>
COLORREF    GetUIForegroundColor();

/// <summary>
/// Returns value of specified Windows UI element's color
/// </summary>
/// <returns>COLORREF (0xAARRGGBB) value of color</returns>
COLORREF    GetUIColorValue(int colorType);

/// <summary>
/// Calculates percieved luminance of ARGB color
/// </summary>
/// <param name="argbColor">ARGB color packed into long</param>
/// <returns>Percieved luminance value from 0 to 255</returns>
double CalculatePercievedLuminance(DWORD argbColor);
