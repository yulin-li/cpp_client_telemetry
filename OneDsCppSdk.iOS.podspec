
Pod::Spec.new do |s|

  s.name         = "OneDsCppSdk.iOS"
  s.version      = "3.5.89.1"
  s.summary      = "The 1DS C++ SDK is for sending telemetry"
  s.description  = <<-DESC
  The 1DS C++ SDK is for sending telemetry to the OneCollector service
                     DESC
  s.homepage     = "https://github.com/microsoft/cpp_client_telemetry"
  s.license      = { :type => "Apache License, Version 2.0" }
  s.author    = ""

  s.platform     = :ios, "10.0"
  s.source       = { :git => "ssh://git@github.com/microsoft/cpp_client_telemetry.git", :submodules => true, :tag => "v#{s.version}" }
  s.pod_target_xcconfig = { "HEADER_SEARCH_PATHS" => "$(PODS_ROOT)/#{s.name}/lib/include/** $(PODS_ROOT)/#{s.name}/lib/ $(PODS_ROOT)/#{s.name}/lib/modules/**", "USER_HEADER_SEARCH_PATHS" => "$(PODS_ROOT)/#{s.name}/third_party/Reachability/", "USE_HEADERMAP" => "NO" }
  s.static_framework = true

  s.source_files = "lib/**/*.{cpp,h,hpp,m,mm}", "wrappers/obj-c", "third_party/Reachability/*.{h,m}"
  s.exclude_files = "lib/modules/liveeventinspector/tests", "lib/modules/exp/tests", "lib/android_build/", "lib/bwcontrol/", "lib/http/HttpClient_Android*", "lib/http/HttpClient_Curl.*", "lib/**/*CX.cpp", "lib/http/HttpClient_Win*", "lib/jni", "lib/modules/bondlite", "lib/modules/dataviewer/tests", "lib/modules/examples", "lib/modules/privacy", "lib/modules/privacyguard/tests/", "lib/modules/utc/", "lib/modules/exp/examples/", "lib/offline/OfflineStorage_Room.*", "lib/pal/desktop/", "lib/pal/universal/", "lib/pal/posix/*Android.cpp", "lib/pal/posix/sysinfo_utils_mac.*", "lib/pal/posix/NetworkInformationImpl.cpp", "lib/shared/dllmain.cpp", "lib/shared/TimedEvent.cpp", "lib/shared/WindowsDesktopHelpers.cpp", "lib/include/mat/IBandwidthController.hpp", "wrappers/obj-c/main.mm"
  s.public_header_files = "wrappers/obj-c/*.h"
  s.private_header_files = "lib/**/*.{h,hpp}", "wrappers/obj-c/*private.h", "third_party/Reachability/*.h"

  s.frameworks = "Network", "SystemConfiguration", "UIKit"
  s.libraries = "sqlite3", "stdc++", "z"

  s.requires_arc = true

end
