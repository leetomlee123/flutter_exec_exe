#include "include/flutter_exec_exe/flutter_exec_exe_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_exec_exe_plugin.h"

void FlutterExecExePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_exec_exe::FlutterExecExePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
