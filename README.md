# GegTimerLiveLink

Geg Timer Live Link project is a demo plugin for UE 4.27 and it has a BP_WallClock which is configured with the UTC Time.
On the StartUpModule the LiveLink will send to BP the UTC values which modify the clock hands rotation.

With the following params (in Property Settings) it is possible to customize the behaviour of BP

| Params | What it does |
| ------ | ------------ |
| **Time Zone Label** | Modifies the label on the clock top |
| **Time Zone** | Add or remove hours to the UTC time |
| **Minutes Increaser** | Allows adding a custom minutes value to time |

![UTC_BP_WallClock](https://user-images.githubusercontent.com/18500631/181046770-f3a0f0e0-e939-4931-8070-053098ebc070.jpg)

With the interior BP params (called Core Settings) it is possible to modify the logic on clock hands' rotation.
These params are in BP settings and are not visible from a BP instance.

## How to use
It is possible to add the BP_WallClock to the Game Viewport directly from the path:
```
'/GegTimerLiveLink/Core/Blueprints/BP_WallClock.BP_WallClock'
```


### Note
This project is licensed under the terms of the MIT license.
