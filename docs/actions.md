Actions allow apps to communicate with each other. They also allow apps to expose some functionality through the user interface of the LaMetric iOS and Android apps.

An app's supported actions must be specified in its manifest.json file:

"actions": {
        "countdown.pause": {
            "icon": ":res/pause.png",
            "index": 2,
            "title": "{{action_pause}}"
        },
        "countdown.reset": {
            "icon": ":res/reset.png",
            "index": 1,
            "title": "{{action_reset}}"
        },
        "countdown.start": {
            "icon": ":res/start.png",
            "index": 0,
            "title": "{{action_start}}"
        }
    },

The content of the actions field should be pretty self-explanatory. The title values in double curly brackets are keys for the localization system that will be replaced by the corresponding value in the user-configured device language. Unlocalized strings can be used as well.

Actions that are meant for configuration purposes carrying more complex data are called commands and are specified in a dedicated manifest field:

"commands": {
        "countdown.configure": {
            "params": {
                "duration": {
                    "data_type": "int"
                },
                "start_now": {
                    "data_type": "bool"
                }
            }
        }
    },

Commands and actions are exposed through the device's REST API interface, but only actions can be triggered through the iOS and Android apps.

When an action or command request has been issued in another app, your app will receive an LRemoteActionRequest in its remoteActionRequest() method. Your app can then parse the request and respond with an LRemoteActionResponse via the LWidgetManager's sendRemoteActionResponse method. The calling application will then receive the response in its remoteActionResponse() method.

To summarize, actions are roughly what Intents are to the Android world. Similarly, RemoteEvents are what Broadcasts are to the Android world. Still, since I can't really see their utility here, I haven't investigated them yet. They probably are related to the LaMetric's IFTTT support and the triggers field in the manifest.json file.
