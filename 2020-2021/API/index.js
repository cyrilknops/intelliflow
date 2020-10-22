const mosca = require('mosca');
const express = require('express');
const cors = require('cors');


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