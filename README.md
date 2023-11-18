# cities2-gptk-fix
A "permanent once-off" fix that allows GPTK to launch Cities Skylines II on macOS.
It uses a DLL proxy for version.dll that patches cohtml_Unity3DPlugin.dll to fix a crash that prevents GPTK from launching the game.

This will work with future updates of the game. If it does stop working on a future update of the game, check back here to find an updated version.dll

## Instructions for use

1. Download the latest release from this repo
2. Copy version.dll into the same folder as Cities2.exe in your bottle
3. Edit your wine configuration and add Cities2.exe to your application ovveride settings
![image](https://github.com/manolz1/cities2-gptk-fix/assets/47918724/a83bf9fe-626d-4c17-9f4c-de647e1e517d)
4. With Cities2.exe selected, press the "Libraries" tab and add a version.dll override as below
   ![image](https://github.com/manolz1/cities2-gptk-fix/assets/47918724/bb5e62db-f114-4768-b861-4c8d2b0e016a)
5. Run the game with D3DMetal/GPTK

## Instructions for building

Use visual studio to build the solution for x64

Thanks to these two projects for helping to create the version.dll proxy

https://github.com/cihansol/PEExportGen

https://github.com/cihansol/DLLProxyProject
