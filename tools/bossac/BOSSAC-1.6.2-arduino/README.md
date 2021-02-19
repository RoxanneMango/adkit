BOSSAC-1.6.2-arduino
--------------------
This version of BOSSA only includes the command line utility of the original project. Some changes were made to update/remove deprecated code,
like the use of std::auto_ptr, which has been changed to std::unique_ptr. In Samba.cpp the _port = port was changed to _port = std::move(port)
usleep was replaced with a SLEEP macro function in sleep.h which accepts an argument of how long to sleep in micro seconds; it has a windows and linux implementation.

--------------------

The original software is developed by Scott Shumate and can be found here:

http://www.shumatech.com/web/products/bossa

NEW IN THIS RELEASE
* New BOSSA shell command line application to do basic memory, flash, and PIO diagnostics
* Workaround for SAM3U firmware bug
* Fixed a bug with setting boot to flash bit on SAM3 devices

RELEASE NOTES
* The OS X USB driver detects an Atmel device as a USB modem.  When prompted about a new network interface, click Cancel to continue.
* Some stability issues have been seen with the OS X USB driver using BOSSA.  When running BOSSA a second time to the same Atmel device, the USB driver can lock up causing BOSSA to freeze.  As a workaround, always disconnect and reconnect the Atmel device before running BOSSA again.
* The firmware inside of SAM3U devices has a bug where non-word flash reads return zero instead of the real data.  BOSSA implements a transparent workaround for flash operations that copies flash to SRAM before reading.  Direct reads using the BOSSA shell will see the bug.
* There are reports that the USB controller in some AMD-based systems has difficulty communicating with SAM devices.  The only known workaround is to use a different, preferrably Intel-based, system.
