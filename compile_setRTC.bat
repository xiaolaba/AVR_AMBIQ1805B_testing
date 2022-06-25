
CHCP 950

rem //-----------------
rem compile.bat
rem //-----------------
rem 如果不用 -static 選項, Windows 環境, 必須提供
rem path = c:\MinGW\bin 或
rem 複製 libgcc_s_dw2-1.dll 到本資料夾
rem JUL/31/2011, xiaolaba
 
rem 用Gcc, 沒有GDB 除錯資料的編譯
gcc -static -o setRTC.exe setRTC.c RS232_xiaolaba.c
 
rem 用G++, 包含GDB 除錯資料的編譯
g++ -g -static -o setRTC_gdb.exe setRTC.c RS232_xiaolaba.c