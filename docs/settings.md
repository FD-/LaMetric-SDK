# Settings

Settings allow configuring a LaMetric OS application through the LaMetric iOS or Android app. The system is composed of multiple entities:

## 1. The settings descriptor

The settings descriptor entry in the manifest is mostly concerned with declaring settings and specifying the representation of the settable items to the user in the LaMetric Android and iOS apps. It contains a title and id for every available option, and allows grouping multiple settings into sections:

```
...
"settings_descriptor": [
        {
            "options": [
                {
                    "id": "http://com.lametric/speed",
                    "title": "Complexity"
                },
                {
                    "id": "http://com.lametric/walls",
                    "title": "Enable Walls"
                },
                {
                    "id": "http://com.lametric/score",
                    "title": "Score"
                }
            ],
            "title": "General"
        }
    ],
...
```

## 2. Settings descriptor rules

The settings descriptor is accompanied by settings descriptor rules, which allow specifying what rules entered text in free-text setting fields must conform to and what dependencies between settings exist (only show this field if that field has value x):

```
...
"settings_descriptor": [
    {
        "title": "Notifications",
        "options": [
            {
                "title": "Notify",
                "id": "http://com.lametric.devwidget/notify"
            },
            {
                "title": "Notification sound",
                "id": "http://com.lametric.devwidget/sound",
                "visibility": "@rule:'rule_for_notification_sounds'"
            }
        ]
    }
],
"settings_descriptor_rules": [
    {
        "id": "rule_for_notification_sounds",
        "result_success": "visible",
        "result_failed": "gone",
        "rule": "@schema:'http://com.lametric.devwidget/notify' == true"
    }
]
...
```

## 3. The settings schema

The settings schema entry in the manifest specifies the exact format of the options declared in the settings descriptor. For every settable property, a type and (if desired) a list of pickable items can be included:

```
...
"settings_schema": {
        "$schema": "http://json-schema.org/draft-04/schema#",
        "id": "http://com.lametric/",
        "properties": {
            "score": {
                "id": "http://com.lametric/score",
                "type": "string"
            },
            "speed": {
                "enum": [
                    "Easy",
                    "Normal",
                    "Hard",
                    "Pro"
                ],
                "id": "http://com.lametric/speed",
                "type": "string"
            },
            "walls": {
                "id": "http://com.lametric/walls",
                "type": "boolean"
            }
        },
        "type": "object"
    },
...
```

Notice how the ids link the settings schema with the settings descriptor. Still, the properties' keys used here will be used for storing values in the settings.json file.

## 4. Initial settings.json

The settings.json file in the application directory may contain the initial ("default") values for your settings values. It has the same format as the file stored in your app's widget directory.

## 5. Widget settings.json

The settings.json file in the widget directory contains the values currently set by the user.

## 6. LSettings API

The LSettings API allows you to read and write your settings file from your app. An instance of LSettings can be obtained from the LApplication's settings() method.
