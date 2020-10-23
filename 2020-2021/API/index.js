const mosca = require('mosca');
const express = require('express');
const cors = require('cors');
var protobuf = require("protobufjs");

//API
const port = 3000;
const app = express();

//public var
var data;

app.set('trust proxy', true);
app.use(cors());

app.get('/', function(request, response){
    response.sendFile(__dirname + '/html/index.html');
});

app.get('/api', function(request, response){
    response.send(JSON.stringify(data));
});

//Broker
var settings = {port: 1883};
var broker = new mosca.Server(settings); //start the broker

protobuf.load("awesome.proto", function(err, root) {
    if (err)
        throw err;

    // Obtain a message type
    var AwesomeMessage = root.lookupType("awesomepackage.AwesomeMessage");

    // Exemplary payload
    var payload = { awesomeField: "AwesomeString" };

    // Verify the payload if necessary (i.e. when possibly incomplete or invalid)
    var errMsg = AwesomeMessage.verify(payload);
    if (errMsg)
        throw Error(errMsg);

    // Create a new message
    var message = AwesomeMessage.create(payload); // or use .fromObject if conversion is necessary

    // Encode a message to an Uint8Array (browser) or Buffer (node)
    var buffer = AwesomeMessage.encode(message).finish();
    // ... do something with buffer

    // Decode an Uint8Array (browser) or Buffer (node) to a message
    var message = AwesomeMessage.decode(buffer);
    // ... do something with message

    // If the application uses length-delimited buffers, there is also encodeDelimited and decodeDelimited.

    // Maybe convert the message back to a plain object
    var object = AwesomeMessage.toObject(message, {
        longs: String,
        enums: String,
        bytes: String,
        // see ConversionOptions
    });
});

broker.on('clientConnected', function(client) {
    console.log('client connected', client.id);
});

broker.on('published', function(packet, client) {
    console.log(packet.topic);
    if(packet.topic == "device"){
        data = packet.payload;
    }
});

app.listen(port, () => console.log(`App listening at http://localhost:${port}`));

protobuf.load("awesome.proto", function(err, root) {
    var hubp = root.lookupType("intelliflow.Hub");
    var sensorp = root.lookupType("intelliflow.Sensor");
    var adminp = root.lookupType("intelliflow.Admin");
    var hub = hubp.toObject(message, {
        enums: String,  // enums as string names
        longs: String,  // longs as strings (requires long.js)
        bytes: String,  // bytes as base64 encoded strings
        defaults: true, // includes default values
        arrays: true,   // populates empty arrays (repeated fields) even if defaults=false
        objects: true,  // populates empty objects (map fields) even if defaults=false
        oneofs: true    // includes virtual oneof fields set to the present field's name
    });
});
