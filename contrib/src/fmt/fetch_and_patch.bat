set BUILD=%SRC%..\build

set FMT_VERSION=5.3.0
set FMT_URL=https://github.com/fmtlib/fmt/archive/%FMT_VERSION%.tar.gz

mkdir %BUILD%

if %USE_CACHE%==1 (
    copy %CACHE_DIR%\%FMT_VERSION%.tar.gz %cd%
) else (
    %WGET_CMD% %FMT_URL%
)

7z -y x %FMT_VERSION%.tar.gz && 7z -y x %FMT_VERSION%.tar -o%BUILD%
del %FMT_VERSION%.tar && del %FMT_VERSION%.tar.gz && del %BUILD%\pax_global_header
rename %BUILD%\fmt-%FMT_VERSION% fmt

cd %BUILD%\fmt

mkdir msvc && cd msvc
setlocal
set PATH=C:\\Program Files\\CMake\\bin\\;%PATH%
cmake .. -G "Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=Off -DFMT_USE_USER_DEFINED_LITERALS=0
endlocal

cd %SRC%