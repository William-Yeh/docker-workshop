# node-mcrypt

MCrypt bindings for Node.js

## Dependencies

### Debian / Ubuntu

```
apt-get install libmcrypt4 libmcrypt-dev
```

### OSX

```
brew install mcrypt
```

## Install

```
npm install mcrypt
```

## Introduction

Alright! There is already OpenSSL extension bundled with Node.js but there are something wrong with some traditional encryption algorithms on OpenSSL.

I tried to decrypt ciphertext of AES and DES algorithms using OpenSSL but i get the garbage outputs. There are some reasons with OpenSSL like null padding.

Also i saw same issues on the stackoverflow.com. Some people encountered with same problems.

This extension provide the cipher and decipher operations via `libmcrypt` and compatible with Java Crypto and PHP MCrypt consequently.

You should start with import the package like

```javascript
var mcrypt = require('mcrypt');
```

There are 3 exposed common functions in the package. These functions are `getAlgorithmNames()`, `getModeNames()` and `MCrypt()` constructor function. Also there are some functions under the prototype of `MCrypt()` constructor function.

### getAlgorithmNames([path]) : Array

`getAlgorithmNames()` returns an array that contains available algorithm names. `path` parameter to specify special algorithm directory. `path` parameter is not required.

```javascript
var mcrypt = require('mcrypt');

var algos = mcrypt.getAlgorithmNames();
console.log(algos);
```

Expected result like that

```
[ 'cast-128', 'gost', 'rijndael-128', 'twofish', 'arcfour', 'cast-256', 'loki97', 'rijndael-192', 'saferplus', 'wake', 'blowfish-compat', 'des', 'rijndael-256', 'serpent', 'xtea', 'blowfish', 'enigma', 'rc2', 'tripledes' ]
```

### getModeNames([path]) : Array

`getModeNames()` returns an array that contains available mode names. `path` parameter to specify special mode directory. `path` parameter is not required.

```javascript
var mcrypt = require('mcrypt');

var algos = mcrypt.getModeNames();
console.log(algos);
```

Expected result like that
```
[ 'cbc', 'cfb', 'ctr', 'ecb', 'ncfb', 'nofb', 'ofb', 'stream' ]
```

### MCrypt(algorithm, mode [, algorithmDir] [, modeDir]) : Object

`MCrypt(algorithm, mode)` is a constructor function to create object for cipher and decipher operations. 
`algorithm` is a required parameter and one of the values of array returned by `getAlgorithmNames()`. 
`mode` is required parameter and one of the values of array returned by `getModeNames()`.
`algorithmDir` and `modeDir` are optional parameters to specify algorithm and mode directories.

```javascript
var MCrypt = require('mcrypt').MCrypt;

var desEcb = new MCrypt('des', 'ecb');
```

There are some prototype functions to make cipher decipher operations and to identify algorithm properties.

#### open(key [, iv])

We are need to `open()` with a key for `decrypt()` and `encrypt()` operations also we should set an iv if required by algorithm in other case `iv` is optional parameter.
`key` and `iv` should be string or Buffer

```javascript
var MCrypt = require('mcrypt').MCrypt;

var desEcb = new MCrypt('des', 'ecb');
desEcb.open('madepass'); // we are set the key
```

#### encrypt(plaintext) : Buffer

`encrypt()` returns a Buffer object that contains ciphertext of `plaintext` parameter. `plaintext` parameter should be `string` or `Buffer`

```javascript
var MCrypt = require('mcrypt').MCrypt;

var desEcb = new MCrypt('des', 'ecb');
desEcb.open('madepass'); // we are set the key

var ciphertext = desEcb.encrypt('this is top secret message!');
console.log(ciphertext.toString('base64'));
```

Expected result like that

```
fkJnIgtiH8nsGDryyuIsmyf5vABMGStlpACfKCTifvA=
```

#### decrypt(ciphertext) : Buffer

`decrypt()` returns a Buffer object that contains plaintext of `ciphertext` parameter. `ciphertext` parameter should be `Buffer`

```javascript
var MCrypt = require('mcrypt').MCrypt;

var desEcb = new MCrypt('des', 'ecb');
desEcb.open('madepass'); // we are set the key

var plaintext = desEcb.decrypt(new Buffer('fkJnIgtiH8nsGDryyuIsmyf5vABMGStlpACfKCTifvA=', 'base64'));
console.log(plaintext.toString());
```

Expected result like that

```
this is top secret message!
```

#### generateIv() : Buffer

`generateIv()` function generates IV randomly.

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
var iv = blowfishCfb.generateIv();

blowfishCfb.open('somekey', iv);

var ciphertext = blowfishCfb.encrypt('sometext');

console.log(Buffer.concat([iv, ciphertext]).toString('base64'));
```

#### validateKeySize(Boolean)
`validateKeySize()` is a function to disable or enable key size validation on `open()`

```javascript
var mc = new MCrypt('blowfish', 'ecb');
mc.validateKeySize(false); // disable key size checking
mc.open('typeconfig.sys^_-');
```

#### validateIvSize(Boolean)
`validateIvSize()` is a function to disable or enable iv size validation on `open()`

```javascript
var mc = new MCrypt('rijndael-256', 'cbc');
mc.validateIvSize(false); // disable iv size checking
mc.open('$verysec$retkey$', 'foobar');
```

#### selfTest() : Boolean

`selfTest()` is an utility function to make test algorithm internally and returns boolean value of status

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.selfTest());
```

#### isBlockAlgorithmMode() : Boolean

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.isBlockAlgorithmMode());
```

#### isBlockAlgorithm() : Boolean

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.isBlockAlgorithm());
```

#### isBlockMode() : Boolean

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.isBlockMode());
```

#### getBlockSize() : Number

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getBlockSize());
```

#### getKeySize() : Number

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getKeySize());
```

#### getSupportedKeySizes() : Array

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getSupportedKeySizes());
```

#### getIvSize() : Number

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getIvSize());
```

#### hasIv() : Boolean

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.hasIv());
```

#### getAlgorithmName() : String

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getAlgorithmName());
```

#### getModeName() : String

```javascript
var MCrypt = require('mcrypt').MCrypt;

var blowfishCfb = new MCrypt('blowfish', 'cfb');
console.log(blowfishCfb.getModeName());
```

