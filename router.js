const express = require('express');
const router = express.Router();
const url = require('url');
let mongoModel = require('./db/models/mongoModel');

// router.get('/sensor', (req, res) => {     console.log(req.query.kartId); let
// newEmploye = new mongoModel.Employee();     newEmploye.kartId =
// req.query.kartId,     newEmploye.firstName = 'Emin',     newEmploye.lastName
// = 'Əhədi',     newEmploye.registertime = getDate(),     newEmploye.active =
// "1";     newEmploye.save()         .then((data) => { console.log(data);
// res.end();         }); });

//Send to MongoDb employee KartId
router.get('/employee', (req, res) => {
    console.log(req.query);
    const kartId = req.query.kartId;
    console.log(kartId);
    mongoModel.Employee
        .findOne({ "kartId": kartId })
        .then((data) => {
            if (!data) {
                console.log("Kart qeydiyyatdan keçməyib");
                res.status(404);
                res.end();

            } else {
                console.log(data.firstName + " " + data.lastName);
                res.status(200);
                res.end();
            }
        })
    res.end();
});
//Send Tempurature data to Client

let tempurature = {
    heat: "",
    humudity: ""
}
router.get("/gettempurature", function (req, res) {
    res.send(tempurature);
    res.end();
})
router.get("/tempurature", function (req, res) {
    tempurature.heat = req.query.heat;
    tempurature.humudity = req.query.humudity;
    res.end();
})
//Recive door data from Arduino
let doorStatus = {
    status: ""
}
router.get("/doorPosition", (req, res) => {
    doorStatus.status = req.query.status;
    res.end();
});
//Send data to Client
router.get("/getDoorPosition", (req, res) => {
    res.send(doorStatus);
    res.end();
});
getDate = () => {
    var d = new Date();
    let rawmounth = parseInt(d.getMonth()) + 1;
    if (rawmounth < 10) {
        let zero = "0"
        rawmounth = zero.concat(rawmounth);
    }
    return d.getDate() + "." + rawmounth + "." + d.getFullYear() + "|" + d.getHours() + ":" + d.getMinutes();
}

module.exports = router