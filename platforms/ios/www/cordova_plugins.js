cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/com.megster.cordova.rfduino/www/rfduino.js",
        "id": "com.megster.cordova.rfduino.rfduino",
        "clobbers": [
            "rfduino"
        ]
    },
    {
        "file": "plugins/org.apache.cordova.dialogs/www/notification.js",
        "id": "org.apache.cordova.dialogs.notification",
        "merges": [
            "navigator.notification"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "com.megster.cordova.rfduino": "0.1.1",
    "org.apache.cordova.dialogs": "0.2.10"
}
// BOTTOM OF METADATA
});