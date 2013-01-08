rem 32bit
"%windir%\Microsoft.NET\Framework\v2.0.50727\csc.exe" /keyfile:CShopUtil.snk /target:library /out:CShopUtil.dll HelloDotNet.cs TestCom.cs UnicodeTextWriter.cs /r:System.Windows.Forms.dll
"%windir%\Microsoft.NET\Framework\v2.0.50727\regasm.exe" CShopUtil.dll /tlb:CShopUtil.tlb
"%ProgramFiles%\Microsoft Visual Studio 8\SDK\v2.0\Bin\gacutil.exe" /i CShopUtil.dll


rem 64bit
rem "%windir%\Microsoft.NET\Framework64\v2.0.50727\csc.exe" /keyfile:CShopUtil.snk /target:library /out:CShopUtil.dll HelloDotNet.cs TestCom.cs UnicodeTextWriter.cs /r:System.Windows.Forms.dll
rem "%windir%\Microsoft.NET\Framework64\v2.0.50727\regasm.exe" CShopUtil.dll /tlb:CShopUtil.tlb
rem "%ProgramFiles(x86)%\Microsoft Visual Studio 8\SDK\v2.0\Bin\gacutil.exe" /i CShopUtil.dll
