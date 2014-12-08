# Wizard of Jewliebots

##Application lives in the jewliebot folder



Install Cordova

    $ npm install cordova -g
    
Create the iOS project

    $ cd cordova-plugin-rfduino/examples/bracelet
    $ cordova platform add ios

Install the rfduino plugin

    $ cordova plugin add com.megster.cordova.rfduino

Install the console plugin for xcode debug

    $ cordova plugin add org.apache.cordova.console
    
Use Xcode to install the application on your iOS device

    $ open platforms/ios/Bracelet.xcodeproj
    
Works on Android 4.3+ too

    $ cd cordova-plugin-rfduino/examples/bracelet
    $ cordova platform add android
    $ cordova plugin add com.megster.cordova.rfduino
    $ cordova run
