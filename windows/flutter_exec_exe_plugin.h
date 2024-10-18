#ifndef FLUTTER_PLUGIN_FLUTTER_EXEC_EXE_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_EXEC_EXE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_exec_exe {

class FlutterExecExePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterExecExePlugin();

  virtual ~FlutterExecExePlugin();

  bool StartExe(const std::string &exe_path);
  bool StopExe();

  // Disallow copy and assign.
  FlutterExecExePlugin(const FlutterExecExePlugin&) = delete;
  FlutterExecExePlugin& operator=(const FlutterExecExePlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace flutter_exec_exe

#endif  // FLUTTER_PLUGIN_FLUTTER_EXEC_EXE_PLUGIN_H_
