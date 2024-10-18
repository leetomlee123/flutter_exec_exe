import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'flutter_exec_exe_platform_interface.dart';

/// An implementation of [FlutterExecExePlatform] that uses method channels.
class MethodChannelFlutterExecExe extends FlutterExecExePlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('flutter_exec_exe');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

   // 启动 exe
  Future<void> startExe(String exePath) async {
    try {
      final bool result = await methodChannel.invokeMethod('startExe', exePath);
      print("Exe started: $result");
    } on PlatformException catch (e) {
      print("Failed to start exe: ${e.message}");
    }
  }

  // 停止 exe
  Future<void> stopExe() async {
    try {
      final bool result = await methodChannel.invokeMethod('stopExe');
      print("Exe stopped: $result");
    } on PlatformException catch (e) {
      print("Failed to stop exe: ${e.message}");
    }
  }
}
