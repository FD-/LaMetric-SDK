# LaMetric-SDK
An unofficial SDK for developing native standalone LaMetric Time apps

# Installation

__PLEASE NOTE__: This is an inofficial SDK and in no way endorsed with SmartAtoms, the developer of the LaMetric Time device. Should you be a representative of SmartAtoms or the LaMetric team, please let me know how you feel about this project!

__IMPORTANT__: Only ever run custom apps on your LaMetric Time device whose source code you have seen and checked before! All apps on the device share the same Linux user, so they have access to all your data (and credentials) stored on the LaMetric Time!

# Steps

## 0. Get SSH access

Installing custom apps __on recent firmware versions__ requires SSH access to the device. If you use a firmware earlier than 2.1.0, you can use the method described under the Legacy Deployment section below for details.

Although SSH access is already enabled on the stock firmware, it's protected by an unknown password. In order to circumvent this password, you have two options:

-   The LaMetric has a firmware flashing mode, but it performs a signature check, so that only official firmware files can be installed. However, a LaMetric user has figured out the original signing key, and released a version of firmware version 2.0.24 that has SSH access enabled and can be installed via USB using the official firmware update procedure described at https://help.lametric.com/support/solutions/articles/6000095176-lametric-time-can-not-boot-up-and-shows-the-loading-indicator-all-the-time-4-dots-are-spinning-aro. Refer to https://github.com/chorankates/h4ck/issues/2 for details.
    
-   Alternatively, you can physically open your device and remove the micro SD card that is mounted on the main PCB. Put it in a computer and modify the root password hash in /etc/shadow. This should work even on newer versions of the LaMetric OS firmware.
    

## 1. Set up the compiler toolchain

Since the LaMetric OS distribution doesn't include a compiler, you'll have to cross-compile your custom apps on a Linux system (I'm using a Ubuntu virtual machine). 

### x86_64 build machines
I spent quite some time trying to find a cross-compiler toolchain that is compatible with the LaMetric's dynamic linker and eventually settled on using the oldest available Linaro arm-linux-gnueabi toolchain. Although this is not the exact same toolchain as used by the LaMetric team (they use a custom-built buildroot toolchain), the produced binaries are compatible, which is good enough for us. 

1. Open the website at https://releases.linaro.org/components/toolchain/binaries/4.9-2016.02/arm-linux-gnueabi/. 
2. Download gcc-linaro-4.9-2016.02-x86_64_arm-linux-gnueabi.tar.xz, 
3. Extract it and make sure all the included tools are available in your PATH.

### aarch64 build machines
There is a compatible compiler for Ubuntu aarch64 systems in the Ubuntu Xenial repositories.

1. Edit /etc/apt/source.list to add xenial sources:

```bash
deb http://ports.ubuntu.com/ubuntu-ports xenial main
deb http://ports.ubuntu.com/ubuntu-ports xenial universe
```

2. Install the gcc-4.9 cross-compiler:

```bash
sudo apt update
sudo apt install gcc-4.9-arm-linux-gnueabi
sudo apt install g++-4.9-arm-linux-gnueabi
```

3. Add a symlink for the compilers

```bash
sudo ln -s /usr/bin/arm-linux-gnueabi-gcc-4.9 /usr/bin/arm-linux-gnueabi-gcc 
sudo ln -s /usr/bin/arm-linux-gnueabi-g++-4.9 /usr/bin/arm-linux-gnueabi-g++
```

## 2. Get the system libraries

LaMetric OS apps need to be linked against a few shared libraries included in the LaMetric OS distribution. Without SSH access to your device, you'll have to download a firmware image from https://firmware.lametric.com and extract the /usr/lib folder from the nested rootfs squashfs file. In case you have SSH access to the device, just copy the contents of /usr/lib from your LaMetric device to the lib folder of the SDK distribution.

## 3. Build the sample app

You should now be able to cross-compile the included sample application. Go to the sample folder of the SDK distribution and run make package. The resulting ipk file will be built to sample/dist. For deployment instructions, follow the steps from deployment.txt.

## 4. Write your own app

Please note I provide only minimal documentation of the SDK functionality. This is because most functions and classes are self-explanatory and most of the remaining stuff I haven't tried myself. However, I did document all odd behavior I found while trying to get my apps to work. If you need any API that I have not documented / isn't self-explanatory, I recommend using the open-source Ghidra tool for figuring out how any of the official apps make use of the particular functionality you're interested in.

# Deployment

Apps are distributed as ipk files, a format designed for use on embedded Linux platforms. It essentially consists of some nested archived folders, and can be created by hand using common Linux tools such as tar and ar. To speed up the process, the SDK distribution contains a package script in the script folder. If you are using the Makefile included in the sample project, you can just make the package target, and the ipk file will be created for you in the dist folder.

If you invoke the package.sh script manually, have a look at the comments in the script itself.

For actually installing the packaged application on your LaMetric Time, your options depend on the firmware version of your LaMetric device.

### Legacy Firmware: Without SSH access

Custom apps can be installed without SSH access on legacy (before 2.1.0) versions of the stock (unmodified, original) firmware. Unfortunately, the folks at SmartAtoms closed this loophole after I documented it here. 

Conveniently, we can creatively misuse the v1 REST API that the Android and iOS apps use for communicating with the LaMetric Time (not the same as the publicly documented v2 API) for installing our custom-built IPK files on the device, even if they are not included in LaMetric's official repository (which backs their app store). Luckily, the v1 API uses the same authentication as the v2 API, so this method is accessible to users consciously installing custom apps, but protected from being accessed by adversaries, because the credentials are bound to a specific device.

#### Steps:

1. Make the IPK file available on a web server, so it has a URL reachable from your LaMetric Time. The easiest option is to run a simple web server on your computer, but you can also just host it on Dropbox and use a Share link as the URL. Make sure the URL is accessible via HTTP too, not just HTTPS!

2. Go to https://developer.lametric.com and enrol as a developer.

3. Under Your devices, note down the API key of your device. You’ll need it later.

4. Download an HTTP REST client such as [Insomnia](https://insomnia.rest/download/core/?) and start it.

5. In your REST client, choose POST as the method and enter the URL _https://{LAMETRIC_IP_ADDRESS}/api/v1/apps/install_, where _LAMETRIC_IP_ADDRESS_ is the IP address of your LaMetric Time

6. Choose JSON as the data format and paste the following into the request field:

```
["URL_TO_IPK"] 
```

where _URL_TO_IPK_ is the HTTP (not HTTPS!) url to the IPK mentioned in step 1.

7. Choose Basic Auth with username 'dev' and the API key from step 3 as the password

8. Click Send

9. After a few seconds, your app should be installed and running on your LaMetric Time

### With SSH access

1. Copy the ipk file from the dist folder onto your device.

2. On the device, use opkg-cl for installing the package:

```
opkg-cl install com.lametric.sdk.sample_1.0.0.ipk
```

3. Lastly, create a widget instance for the newly installed application:

```
widget.sh create com.lametric.sdk.sample
```

Once you have installed the package and only change the executable, you can update the app without reinstalling the whole package. Just copy the executable to the application folder under `/lametric/data/apps/{package_name}`. The OS will automatically notice the program changed and start it anew.

# Current State

I used the free Ghidra tool for reverse-engineering headers for most of the functionality lfoundation (the main shared library) provides for building applications. I deliberately haven't reverse-engineered classes that seemed irrelevant for custom app development. Although all the functions and classes I used in my own custom apps worked fine, the headers could very well still contain some errors (pointer type where a value type is actually used, missing or wrong const qualifier etc).

# Documentation

For now, I only documented a few subsystems of the SDK in the docs folder of the SDK distribution. Most of the SDK functions should be self-explanatory, and the sample project should provide a good starting point for your own apps. If you have created something that could be useful to others as well, please publish the source code! Likewise, if you have questions or suggestions for this unofficial SDK, please open an issue or pull request on GitHub.

