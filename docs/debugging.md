# Debugging

If the LaMetric Time displays an x and an arrow in place of your custom app, that means your application has crashed repeatedly. Logcat will include some more information, but not the exact error reason (in most cases). Usually, you have an illegal memory access or similar bug in your code. Please note a bug in the reverse-engineered header sometimes can lead to crashes too. If you find that to be the case for a particular API function or class, please file a new issue on GitHub!

For debugging your custom code running on the LaMetric Time hardware, you're mostly limited to the logcat infrastructure LaMetric OS includes.

Logcat was originally developed for the Android OS, but apparently, it has found its way into other embedded Linux systems as well. It consists of a kernel driver that provides access to multiple different message buffers.

On LaMetric OS, apps use the Logcat infrastructure as their main debug output channel. Every app links agains libLog.so, which provides an interface to the message buffers in the kernel driver. The library exposes a few simple methods for logging messages at different levels of criticality. Please note the release version of libLog.so seems to have stubs in place of logv and logd, so you'll have to use logw for debugging purposes. Details on the available functions can be found in the libLog header under include/llog.

## Viewing the log entries

### Without SSH access

Luckily, there is an API endpoint (of the v1 API, not the publicly documented v2 API), which allows to read log entries on stock firmware without SSH access. The endpoint is `https://LAMETRIC_IP_ADDRESS/api/v1/log`. You need to use the API key credentials obtained through developer.lametric.com, as described in the deployment instructions. Since the returned response includes additional information on top of the logcat messages, it takes a little while until the response arrives.

### With SSH access

For viewing the logged messages, just start the logcat tool in an SSH session to your LaMetric Time. You'll see not only the output of your application, but also useful information about the system state or other applications.
