//  exports.h
//
//	Simple header to instruct the linker to forward function exports to another library.
//

#pragma comment(linker,"/export:GetFileVersionInfoA=version_orig.GetFileVersionInfoA,@1")
#pragma comment(linker,"/export:GetFileVersionInfoExA=version_orig.GetFileVersionInfoExA,@2")
#pragma comment(linker,"/export:GetFileVersionInfoExW=version_orig.GetFileVersionInfoExW,@3")
#pragma comment(linker,"/export:GetFileVersionInfoSizeA=version_orig.GetFileVersionInfoSizeA,@4")
#pragma comment(linker,"/export:GetFileVersionInfoSizeExA=version_orig.GetFileVersionInfoSizeExA,@5")
#pragma comment(linker,"/export:GetFileVersionInfoSizeExW=version_orig.GetFileVersionInfoSizeExW,@6")
#pragma comment(linker,"/export:GetFileVersionInfoSizeW=version_orig.GetFileVersionInfoSizeW,@7")
#pragma comment(linker,"/export:GetFileVersionInfoW=version_orig.GetFileVersionInfoW,@8")
#pragma comment(linker,"/export:VerFindFileA=version_orig.VerFindFileA,@9")
#pragma comment(linker,"/export:VerFindFileW=version_orig.VerFindFileW,@10")
#pragma comment(linker,"/export:VerInstallFileA=version_orig.VerInstallFileA,@11")
#pragma comment(linker,"/export:VerInstallFileW=version_orig.VerInstallFileW,@12")
#pragma comment(linker,"/export:VerLanguageNameA=version_orig.VerLanguageNameA,@13")
#pragma comment(linker,"/export:VerLanguageNameW=version_orig.VerLanguageNameW,@14")
#pragma comment(linker,"/export:VerQueryValueA=version_orig.VerQueryValueA,@15")
#pragma comment(linker,"/export:VerQueryValueW=version_orig.VerQueryValueW,@16")
