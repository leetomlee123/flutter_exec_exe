import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_exec_exe/flutter_exec_exe.dart';
import 'package:flutter_exec_exe/flutter_exec_exe_platform_interface.dart';
import 'package:flutter_exec_exe/flutter_exec_exe_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFlutterExecExePlatform
    with MockPlatformInterfaceMixin
    implements FlutterExecExePlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final FlutterExecExePlatform initialPlatform = FlutterExecExePlatform.instance;

  test('$MethodChannelFlutterExecExe is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFlutterExecExe>());
  });

  test('getPlatformVersion', () async {
    FlutterExecExe flutterExecExePlugin = FlutterExecExe();
    MockFlutterExecExePlatform fakePlatform = MockFlutterExecExePlatform();
    FlutterExecExePlatform.instance = fakePlatform;

    expect(await flutterExecExePlugin.getPlatformVersion(), '42');
  });
}
