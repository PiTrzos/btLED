# RGB Controller App

The RGB Controller App is a Kotlin-based Android application that allows you to send Bluetooth messages to an Arduino device. This application is specifically designed for controlling RGB LEDs connected to an Arduino, with the ability to change colors and lighting patterns. Additionally, it can be integrated with the Prismatik app for ambient lighting simulation, enhancing your lighting experience. Please note that the app is currently designed for controlling 107 LEDs.
<p align="center">
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/ca1cfd88-de78-4c09-9119-7f112f535e34" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/ca1cfd88-de78-4c09-9119-7f112f535e34" width="400" />
</p>


# Prerequisites
Before you can use the RGB Controller App, ensure you have the following prerequisites:

    An Android device with Bluetooth capabilities.
    An Arduino device with the btLed2.ino firmware for controlling RGB LEDs.
    A setup with 107 LEDs - edit the code if needed.
    Paired arduino device with your phone (at least 1) - connect button only works with bluetooth on

# Installation
Clone this repository to your local machine:

    git clone https://github.com/PiTrzos/btLED.git

Open the project in Android Studio.

Build and run the app on your Android device or use APK provided in Repository.

# Features
Bluetooth Communication

The RGB Controller App is equipped with Bluetooth communication capabilities, enabling it to send messages to the connected Arduino device for LED control.
LED Control

You can use the app to control the 107 RGB LEDs connected to the Arduino. This includes changing the colors and adjusting lighting patterns as per your preferences.
Prismatik Integration

The app can be integrated with the Prismatik app, available at Prismatik GitHub, for ambient lighting simulation. This allows you to synchronize the LED lighting with on-screen content, creating an immersive visual experience.

# Connecting to Arduino

    Pair your device with arduino bluetooth controller

    Open the RGB Controller App on your Android device.

    Enable Bluetooth on your Android device and make it discoverable.

    Connect to the Arduino by clicking connect button.

# Controlling LEDs

    Once connected, you can use the app to control Arduino.

    Select colors, adjust brightness, and choose lighting patterns as desired.

    Enjoy your customized LED lighting experience.

App Images

<p align="center">
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/e79873c9-318a-4413-ace9-5f34865e3d0e" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/e79873c9-318a-4413-ace9-5f34865e3d0e" width="400" />
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/7e32ca87-6378-4b17-9f92-9b99947a0384" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/7e32ca87-6378-4b17-9f92-9b99947a0384" width="400" />
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/5d154156-0a1a-4f08-bcab-313a846190b1" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/5d154156-0a1a-4f08-bcab-313a846190b1" width="400" />
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/e941d229-7b80-429c-8307-6071973dcf12" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/e941d229-7b80-429c-8307-6071973dcf12" width="400" />
  <img src="https://github.com/PiTrzos/btLED/assets/146988968/ba313eb1-1d53-40a5-9d81-72eb57ccf21a" data-canonical-src="https://github.com/PiTrzos/btLED/assets/146988968/ba313eb1-1d53-40a5-9d81-72eb57ccf21a" width="400" />
</p>
