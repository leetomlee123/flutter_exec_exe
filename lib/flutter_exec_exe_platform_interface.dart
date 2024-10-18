import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'flutter_exec_exe_method_channel.dart';

abstract class FlutterExecExePlatform extends PlatformInterface {
  /// Constructs a FlutterExecExePlatform.
  FlutterExecExePlatform() : super(token: _token);

  static final Object _token = Object();

  static FlutterExecExePlatform _instance = MethodChannelFlutterExecExe();

  /// The default instance of [FlutterExecExePlatform] to use.
  ///
  /// Defaults to [MethodChannelFlutterExecExe].
  static FlutterExecExePlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FlutterExecExePlatform] when
  /// they register themselves.
  static set instance(FlutterExecExePlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
