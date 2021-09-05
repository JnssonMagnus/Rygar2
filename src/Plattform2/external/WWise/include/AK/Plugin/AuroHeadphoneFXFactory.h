#pragma once

/// \file
/// Registers the Auro Headphone plugin automatically.
/// This file should be included once in a .CPP (not a .h, really).  The simple inclusion of this file and the linking of the library is enough to use the plugin.
/// <b>WARNING</b>: Include this file only if you wish to link statically with the plugins.  Dynamic Libaries (DLL, so, etc) are automatically detected and do not need this include file.
/// <br><b>Wwise plugin name:</b>  Auro Headphone
/// <br><b>Library file:</b> AuroHeadphoneFX.lib

#if (defined AK_WIN && !defined AK_WINPHONE && (!defined( AK_USE_METRO_API ) || _MSC_VER >= 1900)) || defined AK_PS4 || defined AK_XBOXONE || defined AK_ANDROID

AK_STATIC_LINK_PLUGIN(AuroHeadphoneFX);
#endif

