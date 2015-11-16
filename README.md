# ForceInstallCDC
> Maintained at <https://github.com/sensics/ForceInstallCDC>

Utility for manually installing a self-signed USB CDC driver for devices using an incorrect/outdated VID/PID and matching a specific bus description prefix, using [libwdi][] to take care of the device enumeration and self-signing.

Requires admin privileges to run (to do the self-signing work).

Not needed for Windows 10, because Windows 10 includes a generic CDC driver.

## Building
Requires the Windows 7 DDK (which usually installs to `C:\WinDDK\7600.16385.1`) to build a 32/64-bit universal libwdi. By default it assumes you've got this submodule and have it installed. If not, set LIBWDI_ROOT accordingly to somewhere that it is installed in your user property sheets.

Also, **the DDK won't build libwdi if there are spaces in the path to this repo**.

Once you're sure you have that installed and the source in the right spot, just run `build-libwdi.cmd` which will take care of launching that DDK's build environment and building an XP-supporting 32 and 64-bit build.

The main project itself builds with MSVC 2015 and copies the `libwdi.dll` in with it. Don't be fooled by the fact it's a 32-bit app, there's "magic" in `libwdi` that handles invoking a nested 64-bit installer tool.

## License

- This project - Apache License v2.0
- [libwdi][] - LGPL 3, the branch used as a submodule is [here](https://github.com/sensics/libwdi/)

[libwdi]: http://libwdi.akeo.ie/