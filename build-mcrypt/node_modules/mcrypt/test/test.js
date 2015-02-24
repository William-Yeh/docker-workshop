
var mcrypt = require('../build/Release/mcrypt');
var assert = require('assert');

describe('MCrypt', function() {
    
    describe('getAlgorithmNames', function() {
        it('should be a function', function() {
            assert(typeof mcrypt.getAlgorithmNames == 'function', 'there is getAlgorithmNames function');
        });
        
        it('should return an array', function() {
            assert(mcrypt.getAlgorithmNames() instanceof Array, 'there is an array');
        });
        
        it('should some values in the array', function() {
            assert(mcrypt.getAlgorithmNames().length > 0, 'there are some values');
        });
        
        it('should be DES value in the array', function() {
            assert(mcrypt.getAlgorithmNames().indexOf('des') > -1, 'there is the des value');
        });
    });
    
    describe('getModeNames', function(){
        it('should be a function', function() {
            assert(typeof mcrypt.getModeNames == 'function', 'there is getModeNames function');
        });
        
        it('should return an array', function() {
            assert(mcrypt.getModeNames() instanceof Array, 'there is an array');
        });
        
        it('should some values in the array', function() {
            assert(mcrypt.getModeNames().length > 0, 'there are some values');
        });
        
        it('should be ECB value in the array', function() {
            assert(mcrypt.getModeNames().indexOf('ecb') > -1, 'there is the ecb value');
        });
    });
    
    
    describe('constructor', function() {
        it('should be a constructor function', function() {
            assert(typeof mcrypt.MCrypt == 'function', 'there is MCrypt constructor function');
        });
        
        it('should throw exception without parameters', function() {
            assert.throws(function(){
                new mcrypt.MCrypt(); // without algo and mode
            }, TypeError, 'there is a TypeError when parameters are missed');
        });
        
        it('should throw exception with less parameter', function(){
            assert.throws(function(){
                new mcrypt.MCrypt('des'); // without mode
            });
        });
        
        it('should throw exception with wrong parameters', function() {
            assert.throws(function(){
                new mcrypt.MCrypt('deso', 'ecb'); // invalid algo name
            }, ReferenceError, 'there is a ReferenceError when parameters are wrong');
            
            assert.throws(function(){
                new mcrypt.MCrypt('des', 'ebo'); // invalid mode name
            }, ReferenceError, 'there is a ReferenceError when parameters are wrong');
        });
        
        it('should not throw exception with correct parameters', function() {
            assert.doesNotThrow(function() {
                new mcrypt.MCrypt('des', 'ecb');
            }, 'there is no error when parameters are correct');
        });
    });

    describe('MCrypt instance (BLOWFISH-ECB)', function() {
        var mc = new mcrypt.MCrypt('blowfish', 'ecb');

        it('should be an object', function() {
            assert(typeof mc == 'object', 'there is an object');
        });

        describe('open', function() {
            var key = 'typeconfig.sys^_-';

            it('should open without error', function() {
                assert.doesNotThrow(function() {
                    mc.validateKeySize(false);
                    mc.open(key);
                }, 'there is error when opened with key');
            });
        });
    });
    
    describe('MCrypt instance (DES-ECB)', function() {
        var mc = new mcrypt.MCrypt('des', 'ecb');
        
        it('should be an object', function() {
            assert(typeof mc == "object", 'there is an object');
        });
        
        describe('open', function() {
            var key = 'madepass';
            var plaintext = 'top secret information!!';
            var ciphertext = '7Bg68sriLJuKCYPl1NmSwGrBrE0E5I+T';
        
            it('should open without error', function(){
                assert.doesNotThrow(function(){
                    mc.open(key);
                }, 'there is error when opened with key');
            });            

            describe('encrypt', function() {
                it('plaintext and decrypted ciphertext should be same', function(){
                    assert.equal(ciphertext, mc.encrypt(plaintext).toString('base64'), 'ciphertext are not same');
                });
                
            });

            describe('decrypt', function() {
                it('ciphertext and encrypted plaintext should be same', function(){
                    assert.equal(plaintext, mc.decrypt(new Buffer(ciphertext, 'base64')).toString(), 'plaintext are not same');
                });
            });
            
            describe('selfTest', function(){
                it('should return true', function(){
                    assert(mc.selfTest(), 'return value is not true');
                });
            });
            
            describe('isBlockAlgorithmMode', function(){
                it('should return true', function(){
                    assert(mc.isBlockAlgorithmMode(), 'return value is not true');
                });
            });
            
            describe('isBlockAlgorithm', function(){
                it('should return true', function(){
                    assert(mc.isBlockAlgorithm(), 'return value is not true');
                });
            });
            
            describe('isBlockMode', function(){
                it('should return true', function(){
                    assert(mc.isBlockMode(), 'return value is not true');
                });
            });
            
            describe('getKeySize', function(){
                it('should equal to keysize of algorithm', function(){
                    assert.equal(mc.getKeySize(), 8, 'return value is not 8');
                });
            });
            
            describe('getSupportedKeySizes', function(){
                it('should return an array', function() {
                    assert(mc.getSupportedKeySizes() instanceof Array, 'return value is not array');
                });
                
                it('array should not be empty', function() {
                    assert(mc.getSupportedKeySizes().length > 0, 'return value is empty');
                });
            });
            
            describe('getIvSize', function(){
                it('should equal to iv size of algorithm', function(){
                    assert.equal(mc.getIvSize(), 8, 'iv size not equals with 8');
                });
            });
            
            describe('hasIv', function(){
                it('should return false', function(){
                    assert.equal(mc.hasIv(), false, 'return value is not false');
                });
            });
            
            describe('getAlgorithmName', function(){
                it('should return DES', function(){
                    assert.equal(mc.getAlgorithmName(), 'DES', 'return value is not DES');
                });
            });
            
            describe('getModeName', function() {
                it('should return ECB', function(){
                    assert.equal(mc.getModeName(), 'ECB', 'return value is not ECB');
                });
            });
            
        });
        
        
    });
});

