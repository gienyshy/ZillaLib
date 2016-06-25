/*
  ZillaLib
  Copyright (C) 2010-2016 Bernhard Schelling

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __ZL_PLATFORM__
#define __ZL_PLATFORM__

#include "ZL_PlatformConfig.h"

#if defined(__IPHONEOS__)
#include "ZL_PlatformIOS.h"
#elif defined(__ANDROID__)
#include "ZL_PlatformAndroid.h"
#elif defined(__NACL__)
#include "ZL_PlatformNACL.h"
#elif defined(__EMSCRIPTEN__)
#include "ZL_PlatformEmscripten.h"
#elif defined(__WINDOWSPHONE__)
#include "ZL_PlatformWP.h"
#elif defined(ZL_USE_SDL)
#include "ZL_PlatformSDL.h"
#else
#error ZL_Platform not defined?
#endif

#ifdef __cplusplus
#include "ZL_Application.h"

//Stuff all platforms need to implement

//Settings
void ZL_SettingsInit(const char* FallbackConfigFilePrefix);
const ZL_String ZL_SettingsGet(const char* Key);
void ZL_SettingsSet(const char* Key, const ZL_String& Value);
void ZL_SettingsDel(const char* Key);
bool ZL_SettingsHas(const char* Key);
void ZL_SettingsSynchronize();

//application
extern "C" { ticks_t ZL_GetTicks(); }
void ZL_Delay(ticks_t ms);
void ZL_StartTicks();

//display
bool ZL_CreateWindow(const char* windowtitle, int width, int height, int displayflags);
void ZL_GetWindowSize(int *w, int *h);

//Misc
void ZL_OpenExternalUrl(const char* url);

//Joystick
int ZL_NumJoysticks();
struct ZL_JoystickData;
ZL_JoystickData* ZL_JoystickHandleOpen(int index);
void ZL_JoystickHandleClose(ZL_JoystickData* joystick);

//Audio
bool ZL_AudioOpen();

//HTTP network Interface some platforms without sockets have to implement
#define ZL_HTTPCONNECTION_IMPL_INTERFACE struct ZL_HttpConnection_Impl : ZL_Impl { \
	ZL_String url; std::vector<char> post_data; void* handle; unsigned int timeout_msec; bool dostream; \
	ZL_Signal_v2<int, const ZL_String&> sigReceivedString; \
	ZL_Signal_v3<int, const char*, size_t> sigReceivedData; \
	ZL_HttpConnection_Impl(); void Disconnect(); void Connect(); };

//forward declaration of stuff that is used globally around the library code
struct ZL_File_Impl;
struct ZL_Sound_Impl;
struct ZL_Event;
extern struct ZL_Application* ZL_MainApplication;
extern int ZL_DoneReturn;
extern unsigned int ZL_LastFPSTicks;
enum ZL_ApplicationFlagsInternal { ZL_APPLICATION_DONE = 0x0800, ZL_APPLICATION_NOVSYNC = 0x1000, ZL_APPLICATION_VSYNCFAILED = 0x2000, ZL_APPLICATION_VSYNCHACK = 0x4000 };
extern unsigned short ZL_TPF_Limit, ZL_Requested_FPS;
extern unsigned int ZL_MainApplicationFlags;
extern unsigned int *pZL_WindowFlags;
extern int native_width, native_height, window_viewport[4], window_framebuffer, *active_viewport, active_framebuffer;
extern bool native_aspectcorrection;
extern void ZillaLibInit(int argc, char *argv[]);
extern void InitGL(int width, int height);
extern void (*funcInitGL3D)(bool RecreateContext);
extern void _ZL_Display_KeepAlive();
extern void ZL_Display_Process_Event(ZL_Event& event);
extern void (*funcSceneManagerCalculate)(), (*funcSceneManagerDraw)();
extern bool (*funcProcessEventsJoystick)(ZL_Event&);
extern ZL_Sound_Impl* ZL_Sound_Load(ZL_File_Impl* file_impl, bool stream);
extern ZL_Sound_Impl* ZL_Sound_LoadPlatform(void* data);
extern bool ZL_PlatformAudioMix(char *stream, int len);
extern bool (*funcAudioMix)(char*, int);

#endif //__cplusplus
#endif //__ZL_PLATFORM__
