#include "flutter_exec_exe_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_exec_exe {

PROCESS_INFORMATION process_info;
// static
void FlutterExecExePlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_exec_exe",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterExecExePlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterExecExePlugin::FlutterExecExePlugin() {}

FlutterExecExePlugin::~FlutterExecExePlugin() {}

void FlutterExecExePlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else if (method_call.method_name().compare("startExe") == 0) {
    std::string exe_path = std::get<std::string>(*(method_call.arguments()));
    if (StartExe(exe_path)) {
      result->Success(flutter::EncodableValue(true));
    } else {
      result->Error("ExeStartError", "Failed to start exe");
    }
  } else if (method_call.method_name().compare("stopExe") == 0) {
    if (StopExe()) {
      result->Success(flutter::EncodableValue(true));
    } else {
      result->Error("ExeStopError", "Failed to stop exe");
    }
  } else {
    result->NotImplemented();
  }
}

bool FlutterExecExePlugin::StartExe(const std::string &exe_path) {
  std::wstring wide_exe_path(exe_path.begin(), exe_path.end());

  STARTUPINFO startup_info;
  ZeroMemory(&startup_info, sizeof(startup_info));
  startup_info.cb = sizeof(startup_info);
  ZeroMemory(&process_info, sizeof(process_info));

  if (!CreateProcess(wide_exe_path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info)) {
    return false;
  }
  return true;
}

bool FlutterExecExePlugin::StopExe() {
  if (!TerminateProcess(process_info.hProcess, 0)) {
    return false;
  }
  CloseHandle(process_info.hProcess);
  CloseHandle(process_info.hThread);
  return true;
}

}  // namespace flutter_exec_exe
