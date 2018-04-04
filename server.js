let express = require('express'),
    app = express(),
    net = require('net'),
    bp = require('body-parser'),
    router = require('./router'),
    cors =require('cors')
    PORT = 3000;

app.use(cors());
app.use(bp.urlencoded({extended: false}));
app.use(bp.json());
app.use('/', router);
app.listen(PORT, function (err) {
    err == true
        ? console.log('connection unsuccesfull')
        : console.log("Server run on port :", PORT);
})