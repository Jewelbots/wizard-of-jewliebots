// (c) 2013 Sara Chipps
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* global mainPage, deviceList, refreshButton */
/* global detailPage, lightButton */
/* global rfduino, alert */
'use strict';

var brightness = 100;

// create the friends in absence of a data source
var friends = [
  { name: "Steven",
    deviceId: "001",
    avatar: "images/guy.png"
  },
  { name: "Kim",
    deviceId: "002",
    avatar: "images/lady.png"
  },
];

var app = {
  initialize: function() {
      this.bindEvents();
      this.showPage(mainPage);
  },

  bindEvents: function() {
      document.addEventListener('deviceready', this.onDeviceReady, false);
      refreshButton.addEventListener('touchstart', this.refreshDeviceList, false);
      sendButton.addEventListener('touchstart', this.onData);
      deviceList.addEventListener('touchstart', this.connect, false); // assume not scrolling
      //app.bindProximityFriends();
      app.bindProximityRecipePopup();

      $('.js-finished').on('touchstart', function() {
        app.showPage(mainPage);
      });
  },

  onDeviceReady: function() {
    app.refreshDeviceList();
  },

  refreshDeviceList: function() {
    deviceList.innerHTML = ''; // empties the list
    rfduino.discover(5, app.onDiscoverDevice, app.onError);
  },

  onDiscoverDevice: function(device) {
    var listItem = document.createElement('li'),
        html = '<b>Jewliebots version ' + device.name + '</b><br/>' +
            device.uuid + '<br/>' +
            "Click to connect to Jewelry";

    listItem.setAttribute('uuid', device.uuid);
    listItem.innerHTML = html;
    deviceList.appendChild(listItem);
  },

  connect: function(e) {
    //console.log(e);
    var uuid = e.target.getAttribute('uuid');
    var onConnect = function() {
      rfduino.onData(app.onData, app.onError);
      app.showPage(wizardPageOne);
    };
    rfduino.connect(uuid, onConnect, app.onError);
  },

  getLED: function(){
      var whichLED = document.getElementById('LED').value;
      return whichLED;
  },

  getMode: function(){
      var whichMode = document.getElementById('mode').value;
      return whichMode;
  },

  getColor: function() {
      var whichColor = document.getElementById('color').value;
      return whichColor;
  },

  onData: function() {
    var send = new Uint8Array(5);
    var LED = app.getLED();
    var color = app.getColor();
    var mode = app.getMode();

    send[0] = "0";
    send[1] = brightness;
    send[2] = mode;
    send[3] = LED;
    send[4] = color;

    rfduino.write(send.buffer, app.writeSuccess, app.onError);
  },

  sendProximityRecipe: function() {
    //TODO: this will need to match what to send the device
    //for right now it's just doing the one-time send
    var send = new Uint8Array(5);
    var led = $('#prCharmSetPopup').data('charmid');
    var color = $('#prColor').val();
    var effect = $('#prEffect').val();
    var bright = $('#prGlow').val();

    send[0] = "0";
    send[1] = bright;
    send[2] = effect;
    send[3] = led;
    send[4] = color;

    rfduino.write(send.buffer, app.writeSuccess, app.onError);
    //close the popup
    $('#prCharmSetPopup').popup('close');
  },

  disconnect: function() {
    rfduino.disconnect(app.showMainPage, app.onError);
  },

  onError: function(reason) {
    console.log("Error: " + reason);
    //it's throwing a lot of errors with null reason that don't really appear to be errors?
    if(reason !== null) {
      alert(reason);
      app.showPage(mainPage);
    }
  },

  writeSuccess: function(reason){
    alert("you've sent info " + reason);
    //can use this to debog if you are having trouble sending
  },

  showPage: function(pageName) {
    //naive controller, when this gets more complicated than two recipes, think about a MVC fx
    app.hideAll();
    pageName.hidden = false;
  },

  hideAll: function() {
    mainPage.hidden = true;
    detailPage.hidden = true;
    wizardPageOne.hidden = true;
    proximityRecipePageOne.hidden = true;
    proximityRecipeSet.hidden = true;
  },

  createFriendsList: function(friends) {
    var friendsList = "<tr>";
    for(var i=0;i<friends.length;i++){
      var friend = friends[i];
      //var friendItem = '<li class="js-proximity-friend" data-name="' + friend.name + '" data-deviceid="' + friend.deviceId + '">';
      //friendItem += '<img src="' + friend.avatar + '"></img><strong>' + friend.name + '</strong></li>';
      //friendsList += friendItem;
      if((i)%3 === 0) {
        friendsList += "<tr>";
      }
      var friendData = '<td><img src="' + friend.avatar + '" class="js-proximity-friend" data-name="' + friend.name + '" data-deviceid="' + friend.deviceId + '"></img><h3>' + friend.name + '</h3></td>';
      if((i+1)%3 === 0) {
        friendData += "</tr>";
      }
      friendsList += friendData;
    }
    $("#friendsTable").html(friendsList);
    app.bindProximityFriends();
  },

  bindProximityFriends: function() {
    $(".js-proximity-friend").on('touchstart', function() {
      app.showPage(proximityRecipeSet);
      $('#nearName').text($(this).data("name")).data("deviceid", $(this).data("deviceid"));
      console.log($("#nearName").data("deviceid"));
    });
  },

  bindProximityRecipePopup: function() {
    $('.js-pr-charm').on('touchstart', function() {
      $('#prCharmSetPopup').popup('open', { shadow: true});
      $('#prCharmSetPopup').data("charmid", $(this).data("charmid"));
      return false;
    });
    $('#prCharmSetPopup').on('popupafterclose', function(event, ui) {
      $(this).removeAttr('data-charmid');
      $(this).removeData('data-charmid');
    });
    //bind send on popup
    sendRecipe.addEventListener("touchstart", app.sendProximityRecipe);
  }
};

headerHome.addEventListener("touchstart", function() {
  app.showPage(mainPage);
});

makeRecipeButton.addEventListener("touchstart", function() {
  console.log(friends);
  app.createFriendsList(friends);
  app.showPage(proximityRecipePageOne);
});

detailPageButton.addEventListener("touchstart", function() {
  app.showPage(detailPage);
});

finishButton.addEventListener("touchstart", function() {
  app.showPage(wizardPageOne);
});

brightUP.addEventListener("touchstart", function(){
    brightness+=10;
    if(brightness>255)brightness = 255;
    bright.innerHTML = brightness;
});

brightDOWN.addEventListener("touchstart", function(){
    brightness-=10;
    if(brightness<0)brightness = 0;
    bright.innerHTML = brightness;
});
