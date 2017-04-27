# downloader
下载工具，基于chromium51.0.2704.79

## Get the code
```
mkdir downloader
cd downloader
gclient config https://github.com/wpp2014/downloader.git --name=src
gclient sync
```

## Build
```
cd src
./build/gyp_chromium downloader/downloader.gyp
ninja -C out/Release downloader
```
