/**
 * simple demo for mcrypt in Node.js
 * adapted from PHP example: http://php.net/manual/en/function.mcrypt-encrypt.php
 */

var mcrypt = require('mcrypt');

var CIPHER_ALGO = 'rijndael-256';
var cipher = new mcrypt.MCrypt(CIPHER_ALGO, 'cbc');



var key = new Buffer(
    "bcb04b7e103a0cd8b54763051cef08bc55abe029fdebae5e1d417e2ffb2a00a3"
    , 'hex');

var iv = cipher.generateIv();
var iv_size = iv.length;

console.log('Cipher:', CIPHER_ALGO);
console.log('Key size:', key.length);
console.log('Key:', key.toString('hex'));
console.log('IV: ', iv.toString('hex'));
console.log("---");


// display plaintext
var plaintext = 'This string was AES-256 / CBC / ZeroBytePadding encrypted.';
console.log('Before encryption:', plaintext);


// --- ENCRYPTION ---

cipher.open(key, iv);

var ciphertext = cipher.encrypt(plaintext);
var combined   = Buffer.concat([iv, ciphertext]);
var ciphertext_base64 = combined.toString('base64');
console.log('After encryption: ', ciphertext_base64);


// --- DECRYPTION ---

var ciphertext_binary = new Buffer(ciphertext_base64, 'base64');

var iv_dec         = new Buffer(iv_size);
var ciphertext_dec = new Buffer(ciphertext_binary.length - iv_size);
ciphertext_binary.copy(iv_dec, 0, 0, iv_size);
ciphertext_binary.copy(ciphertext_dec, 0, iv_size);

cipher.open(key, iv_dec);
var plaintext_dec = cipher.decrypt(ciphertext_dec);
console.log('After decryption: ', plaintext_dec.toString());
