# Wizard of Jewliebots

##Based on the RFDuino Blink Example



Install Cordova

    $ npm install cordova -g
    
Create the iOS project

    $ cd cordova-plugin-rfduino/examples/blink
    $ cordova platform add ios

Install the rfduino plugin

    $ cordova plugin add com.megster.cordova.rfduino
    
Use Xcode to install the application on your iOS device

    $ open platforms/ios/Blink.xcodeproj
    
Works on Android 4.3+ too

    $ cd cordova-plugin-rfduino/examples/blink
    $ cordova platform add android
    $ cordova plugin add com.megster.cordova.rfduino
    $ cordova run
