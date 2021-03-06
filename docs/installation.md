# Installation

__PLEASE NOTE__: This is an inofficial SDK and in no way endorsed with SmartAtoms, the developer of the LaMetric Time device. Should you be a representative of SmartAtoms or the LaMetric team, please let me know how you feel about this project!

__IMPORTANT__: Only ever run apps on your LaMetric Time device whose source code you have seen and checked before! All apps on the device share the same Linux user, so they have access to all your data (and credentials) stored on the LaMetric Time!

# Steps

## 0. Get SSH access (Optional)

Installing custom apps on your LaMetric device __no longer requires__ having SSH access to the device, so it works on the original stock firmware. See the Deployment section below for details.

Still, having SSH access is the most convenient method for developing custom apps for the LaMetric Time, so you may still be interested in enabling it. Although SSH access is already enabled on the stock firmware, it's protected by an unknown password. In order to circumvent this password, you have two options:

-   The LaMetric has a firmware flashing mode, but it performs a signature check, so that only official firmware files can be installed. However, a LaMetric user has figured out the original signing key, and released a version of firmware version 2.0.24 that has SSH access enabled and can be installed via USB using the official firmware update procedure described at https://help.lametric.com/support/solutions/articles/6000095176-lametric-time-can-not-boot-up-and-shows-the-loading-indicator-all-the-time-4-dots-are-spinning-aro. Refer to https://github.com/chorankates/h4ck/issues/2 for details.
    
-   Alternatively, you can physically open your device and remove the micro SD card that is soldered onto the main PCB. Mount it on a computer and modify the root password hash in /etc/shadow. This should work even on newer versions of the LaMetric OS firmware.
    

## 1. Set up the compiler toolchain

Since the LaMetric OS distribution doesn't include a compiler, you'll have to cross-compile your custom apps on a Linux system (I'm using a Ubuntu virtual machine). I spent quite some time trying to find a cross-compiler toolchain that is compatible with the LaMetric's dynamic linker and eventually settled on using the oldest available Linaro arm-linux-gnueabi toolchain from https://releases.linaro.org/components/toolchain/binaries/4.9-2016.02/arm-linux-gnueabi/. Although this is not the exact same toolchain as used by the LaMetric team (they use a custom-built buildroot toolchain), the produced binaries are compatible, which is good enough for us. Download gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabi.tar.xz, extract it and make sure all the included tools are available in your PATH.

## 2. Get the system libraries

LaMetric OS apps need to be linked against a few shared libraries included in the LaMetric OS distribution. Without SSH access to your device, you'll have to download a firmware image from https://firmware.lametric.com and extract the /usr/lib folder from the nested rootfs squashfs file. In case you have SSH access to the device, just copy the contents of /usr/lib from your LaMetric device to the lib folder of the SDK distribution.

## 3. Build the sample app

You should now be able to cross-compile the included sample application. Go to the sample folder of the SDK distribution and run make package. The resulting ipk file will be built to sample/dist. For deployment instructions, follow the steps from deployment.txt.

## 4. Write your own app

Please note I provide only minimal documentation of the SDK functionality. This is because most functions and classes are self-explanatory and most of the remaining stuff I haven't tried myself. However, I did document all odd behavior I found while trying to get my apps to work. If you need any API that I have not documented / isn't self-explanatory, I recommend using the open-source Ghidra tool for figuring out how any of the official apps make use of the particular functionality you're interested in.
