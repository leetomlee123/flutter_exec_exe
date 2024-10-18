
import 'flutter_exec_exe_platform_interface.dart';

class FlutterExecExe {
  Future<String?> getPlatformVersion() {
    return FlutterExecExePlatform.instance.getPlatformVersion();
  }
}
