# Building WebRTC

This document describes how to build WebRTC libraries used by react-native-webrtc.

## Overview

The WebRTC libraries used by react-native-webrtc are built from the [jitsi/webrtc](https://github.com/jitsi/webrtc) repository, which contains the WebRTC source code with custom patches applied by the Jitsi team. The custom build script has been migrated to that repository.

## Build Script Location

The custom build script is now located at:
- **Repository**: [jitsi/webrtc](https://github.com/jitsi/webrtc)
- **Build Script**: `tools/build-webrtc.py`
- **Documentation**: See the [README.md](https://github.com/jitsi/webrtc/blob/master/README.md) in the jitsi/webrtc repository

## Build Process

Custom builds can be made using the [build script](https://github.com/jitsi/webrtc/blob/master/tools/build-webrtc.py) from the jitsi/webrtc repository.

### Prerequisites

- Python 3.x
- Build tools for your target platform (Xcode for iOS/macOS, Android SDK/NDK for Android)
- Chromium depot_tools (automatically fetched by the build script)

### Building for iOS

1. Use the build script to create the `WebRTC.xcframework.zip` artifact:
   ```bash
   python tools/build-webrtc.py /path/to/build --setup --ios
   python tools/build-webrtc.py /path/to/build --build --ios
   ```

2. After building, manual steps are required:
   - Update the version number and path in `ios/JitsiWebRTC.podspec`
   - Compute the SHA-256 of the built artifact and update `Package.swift`
   - Copy the `Package.swift` file to the appropriate release branch
   - Commit all changes
   - Create a GitHub release with versioning: X.0.Y (where X is Chrome milestone, Y is build number)
   - Upload the build artifact to the release
   - Push the spec to CocoaPods: `pod trunk push ios/JitsiWebRTC.podspec`

### Building for Android

1. Use the build script to create the `webrtc-android.zip` artifact:
   ```bash
   python tools/build-webrtc.py /path/to/build --setup --android
   python tools/build-webrtc.py /path/to/build --build --android
   ```

2. After building, manual steps are required:
   - Unzip the file and put it onto `android/libs` overwriting any existing file
   - Adjust the version numbers in `android/build.gradle`
   - Commit the result
   - Run the `Release Android` workflow to push the library to Maven Central
   - Complete the release process via Sonatype OSS

### Build Script Options

The build script supports the following options:

- `--setup`: Prepare the target directory for building
- `--build`: Build WebRTC in the target directory
- `--sync`: Run gclient sync on the WebRTC directory
- `--ios`: Use iOS as the target platform
- `--android`: Use Android as the target platform
- `--debug`: Make a Debug build (defaults to Release)

## WebRTC Revisions

For a given stable Chrome release (e.g., M124), there are typically 2 branches in the jitsi/webrtc repository:
- `M124-upstream`: Untouched branch from upstream
- `M124`: Contains custom patches applied by Jitsi

All patches are submitted upstream once tested, or abandoned if not suitable.

## Versioning

Releases follow the versioning scheme: `Chrome Major Version`.`0`.`Release Number`

For example: `124.0.0`, `124.0.1`, etc.

## Distribution

The built libraries are distributed through:
- **iOS/macOS**: CocoaPods as "JitsiWebRTC"
- **Android**: Maven Central
- **iOS**: Swift Package Manager (as of version 106.0.0)

## Notes

- Starting with version 106, iOS builds don't contain bitcode but do contain embedded dSYM slices
- Builds are currently done manually and require testing with react-native-webrtc
- The process involves coordination between multiple repositories and distribution channels