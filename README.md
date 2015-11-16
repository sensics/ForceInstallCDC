# force-install-libwdi

Utility for manually installing a self-signed USB CDC driver for devices using an incorrect/outdated VID/PID and matching a specific bus description prefix.

## Building
Requires the Windows 7 DDK (which usually installs to `C:\WinDDK\7600.16385.1`) to build a 32/64-bit universal libwdi. By default it assumes you've got this submodule and have it installed. If not, set LIBWDI_ROOT accordingly to somewhere that it is installed in your user property sheets.

Also, **the DDK won't build libwdi if there are spaces in the path to this repo**.

Once you're sure you have that installed and the source in the right spot, just run `build-libwdi.cmd` which will take care of launching that DDK's build environment and building an XP-supporting 32 and 64-bit build.

The main project itself builds with MSVC 2015.