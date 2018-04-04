mongoose = require('mongoose'),
mongoose.connect("mongodb://emin.ahadi:emin8986@ds223019.mlab.com:23019/spiot");
mongoose.Promise = global.Promise;
module.exports = mongoose;