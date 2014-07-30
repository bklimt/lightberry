
var upnp = require("upnp-client");

var controlPoint = new upnp.ControlPoint();

var log = function(device) {
  console.log(device.server);
  console.log(device.nt);
  console.log(device.location);
  console.log('');
}

controlPoint.on("DeviceAvailable", function(device) {
  log(device);
});

controlPoint.on("DeviceFound", function(device) {
  log(device);
});

//controlPoint.search('urn:schemas-upnp-org:device:InternetGatewayDevice:1');
controlPoint.search();

