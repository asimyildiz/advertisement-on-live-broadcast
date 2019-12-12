# Advertisement on Live Broadcast - C++

POC of displaying a popup on live broadcast stream using ffmpeg and sfml for pre-defined stream position
- The idea is to show a popup on live broadcast with a message for pre-defined stream positions even if there is no internet connection for hybrid STBs (satellite + connected)
- This implementation also can be used to display a fingerprint, an EMM message etc. on top of livestream independent from the UI
- This project is also implemented to try ffmpeg while decoding a video stream (ts file in our case) and to see the performance
- This project uses sfml to draw decoded video frames and the popup onto the screen

In order to run or debug the project
- Project is tested with Visual Studio 2017 Community Edition
- All paths are set relative to the project
- Make sure that "lib" and "include" folders exist
- Make sure to download "shared" folder that stores ffmpeg and sfml library dlls from the url : https://drive.google.com/open?id=1jQ61hmow7hvCU8G167q-4ZxWaHpcC0iL
- Make sure to download "assets" folder that stores fonts, icons and video used inside the project from the url : https://drive.google.com/open?id=1mJEbWNC0hdWxs0O-c9Uu3G8IyqPkYOrk
- Then copy the contents of these downloaded folders into "Debug" and "Release" folders before debugging or running the project

Visual Studio Project properties (tested with x86 platform : Debug/Release configurations)
- Debugging->Command Arguments						=> should point to the video file relative to exe inside "Debug" and "Release" folders
- C++->General->Additional Include Directories		=> should point to the "include" folder
- C++->Precompiled Headers							=> should be disabled (Not Using Precompiled Headers)
- Linker->General->Additional Library Directories	=> should point to the "lib" folder
- Linker->Input->Additional Dependencies			=> should have the name of ffmpeg and sfml libraries (for sfml use library names with suffix -d for Debug configuration)
