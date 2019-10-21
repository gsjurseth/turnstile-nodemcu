// grab the things we need
import mongoose from 'mongoose';

const Schema = mongoose.Schema;

// create a schema
const visitorSchema = new Schema({
  date: { type: Date, default: Date.now },
  tsID: { type: String, required: true },
  distance: { type: Number, required: true }
});

// the schema is useless so far
// we need to create a model using it
let visitor = mongoose.model('Visitor', visitorSchema);

// make this available to our users in our Node applications
module.exports = visitor;
