#GamePlatformCore

C/C++/Objective-C alpha simple stub used for testing HTTP/HTTPS/web services from native clients.  Also basic threading support cross platform with locks/mutexes and threading for all web requests. Not just for games but pulled from my game engine used to hit web services in json.

Meant to run on desktop (Windows/OSX/Linux) and mobile (iOS and Android 2.3+).

The setup is based on building a C/C++ core/engine (this being one piece I am taking out to open source) that has stubs needed such as Objective-C++ on iOS and NDK on Android to make most of the tools/libs/engine completely cross platform. This is similar to oolong or other game studios C++ engines for multiplatform. Since it needs to be compact, simple and run anywhere, this means using: the standard library, minimal code/simple code for threading/requests, OpenSSL, C++ for most code with only hooks in the platforms. 

Currently mainly just a testing client that has been used in smaller web SDKs for C/C++ libraries on desktop + mobile that needed to hit JSON based web services.

Very Alpha