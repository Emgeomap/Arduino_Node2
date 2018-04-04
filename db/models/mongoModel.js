require('../');
const Schema = mongoose.Schema;
const employeeSchema = new Schema({
    kartId: String,
    firstName: String,
    lastName: String,
    registertime: String,
    active: {
        type: String,
        default: "1"
    }
})
const Employee = mongoose.model('Employee', employeeSchema);
exports.Employee = Employee;
const employeeActSchema = new Schema({
    kartId: String,
    firstName: String,
    lastName: String,
    toWorkTime: String,
    outWorkTime: String,
    active: {
        type: String,
        default: "1"
    }
})
const EmployeeAct = mongoose.model('EmployeeAct', employeeActSchema);
exports.EmployeeAct = EmployeeAct;
