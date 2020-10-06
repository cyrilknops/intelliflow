const mosca = require('mosca');
const express = require('express');
const cors = require('cors');

const port = 3000;
const app = express();

app.set('trust proxy', true);
app.use(cors());

app.get('/', function(request, response){
    response.sendFile(__dirname + '/html/index.html');
});



var settings = {port: 1883};
var broker = new mosca.Server(settings); //start the broker

broker.on('clientConnected', function(client) {
    console.log('client connected', client.id);
});

broker.on('published', function(packet, client) {
    console.log(packet.topic);
});

app.listen(port, () => console.log(`App listening at http://localhost:${port}`));