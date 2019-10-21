// grab the things we need
import mongoose from 'mongoose';

const Schema = mongoose.Schema;

// create a schema
const turnstileSchema = new Schema({
  date: { type: Date, default: Date.now },
  tsID: { type: String, required: true },
  distance: { type: Number, required: true },
  name: { type: String, required: true }
});

// the schema is useless so far
// we need to create a model using it
let turnstile = mongoose.model('Turnstile', turnstileSchema);

// make this available to our users in our Node applications
module.exports = turnstile;
