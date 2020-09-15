# Deployment

Apps are distributed as ipk files, a format designed for use on embedded Linux platforms. It essentially consists of some nested archived folders, and can be created by hand using common Linux tools such as tar and ar. To speed up the process, the SDK distribution contains a package script in the script folder. If you are using the Makefile included in the sample project, you can just make the package target, and the ipk file will be created for you in the dist folder.

If you invoke the package.sh script manually, have a look at the comments in the script itself.

For actually installing the packaged application on your LaMetric Time, your options depend on whether you have SSH access to the device.

### Without SSH access

Custom apps can be installed on stock (unmodified, original) firmware. Conveniently, we can creatively misuse the v1 REST API that the Android and iOS apps use for communicating with the LaMetric Time (not the same as the publicly documented v2 API) for installing our custom-built IPK files on the device, even if they are not included in LaMetric's official repository (which backs their app store). Luckily, the v1 API uses the same authentication as the v2 API, so this method is accessible to users consciously installing custom apps, but protected from being accessed by adversaries, because the credentials are bound to a specific device.

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

where _URL_TO_IPK_ is the url to the IPK mentioned in step 1

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
