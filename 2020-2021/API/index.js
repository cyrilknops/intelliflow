const mosca = require('mosca');
const express = require('express');
const cors = require('cors');
var protobuf = require("protobufjs");

//API
const port = 3000;
const app = express();

//public var
var hubJ, sensorJ, adminJ;

app.set('trust proxy', true);
app.use(cors());

app.get('/', function(request, response){
    response.sendFile(__dirname + '/html/index.html');
});

app.get('/api/hub', function(request, response){
    response.send(JSON.stringify(hubJ));
});
app.get('/api/sensor', function(request, response){
    response.send(JSON.stringify(sensorJ));
});
app.get('/api/admin', function(request, response){
    response.send(JSON.stringify(adminJ));
});


//Broker
var settings = {port: 1883};
var broker = new mosca.Server(settings); //start the broker

broker.on('clientConnected', function(client) {
    console.log('client connected', client.id);
});

broker.on('published', function(packet, client) {
    console.log(packet.topic);
    let buffer = packet.payload;
    protobuf.load("./proto/intelliflow.proto", function(err, root) {
        if (err)
            throw err;
        switch(packet.topic){
            case "sensor":
                var sensorP = root.lookupType("intelliflow.Sensor");
                sensorJ = sensorP.decode(buffer).toJSON();
                console.log(sensorJ);
                break;
            case "hub":
                var hubP = root.lookupType("intelliflow.Hub");
                hubJ = hubP.decode(buffer).toJSON();
                console.log(hubJ);
                break;
            case "admin":
                var adminP = root.lookupType("intelliflow.Admin");
                adminJ = adminP.decode(buffer).toJSON();
                console.log(adminJ);
                break;
        }
    });
});

app.listen(port, () => console.log(`App listening at http://localhost:${port}`));

