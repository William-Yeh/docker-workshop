

#include "mcrypt.h"

using namespace v8;

Persistent<Function> MCrypt::constructor;

MCrypt::MCrypt(const Arguments& args): 
    checkKeySize(true), 
    checkIvSize(true),
    algo(args[0]), 
    mode(args[1]), 
    algoDir(args[2]), 
    modeDir(args[3]) {

    mcrypt_ = mcrypt_module_open(*algo, *algoDir, *mode, *modeDir);
};

MCrypt::~MCrypt() {
    mcrypt_module_close(mcrypt_);
};

template <int (*modify)(MCRYPT mcrypt, void* target, int length)>
node::Buffer* MCrypt::transform(const char* plainText, const size_t length, int* result) {
    size_t targetLength = length;
    
    // determine allocation size if the cipher algorithm is block mode
    // block mode algorithm needs to fit in modulus of block size
    // and it needs to padding space if not fit into block size
    if (mcrypt_enc_is_block_algorithm(mcrypt_) == 1) {
        size_t blockSize = mcrypt_enc_get_block_size(mcrypt_);
        targetLength = (((length - 1) / blockSize) + 1) * blockSize;   
    }
    
    char* targetData = new char[targetLength]();
    std::copy(plainText, plainText + length, targetData);
    
    // create a dummy object to return on fail result
    node::Buffer* cipherText = node::Buffer::New(1);
    
    // copy of the key and iv due to mcrypt_generic_init not accepts 
    // const char for key and iv. direct passing is not safe because
    // iv and key could be modified by mcrypt_generic_init in this case
    char keyBuf[key.length()];
    key.copy(keyBuf, key.length());
    
    char ivBuf[iv.length()];
    iv.copy(ivBuf, iv.length());
    
    if ((*result = mcrypt_generic_init(mcrypt_, keyBuf, key.length(), ivBuf)) < 0) {
        delete[] targetData;

        return cipherText;
    }

    if ((*result = modify(mcrypt_, targetData, targetLength)) != 0) {
        delete[] targetData;

        return cipherText;
    }

    if ((*result = mcrypt_generic_deinit(mcrypt_)) < 0) {
        delete[] targetData;

        return cipherText;
    }

    cipherText = node::Buffer::New(targetData, targetLength); 
    
    delete[] targetData;

    return cipherText;
}

std::vector<size_t> MCrypt::getKeySizes() {
    
    int count = 0;
    int* sizes = mcrypt_enc_get_supported_key_sizes(mcrypt_, &count);

    if (count <= 0) {
        mcrypt_free(sizes);

        size_t size = mcrypt_enc_get_key_size(mcrypt_);

        if (size > 0) {
            std::vector<size_t> keySizes(1);
            keySizes[0] = size;
            return keySizes;
        }

        std::vector<size_t> keySizes(0);
        return keySizes;
    }

    std::vector<size_t> keySizes(count);

    for (int i = 0; i < count; i++) {
        keySizes[i] = sizes[i];
    }

    mcrypt_free(sizes);
    
    return keySizes;
}

NODE_MCRYPT_METHOD(New) {
    HandleScope scope;
    
    if (!args.IsConstructCall()) {
        Local<Value> argv[] = {args[0], args[1], args[2], args[3]};
        return scope.Close(constructor->NewInstance(4, argv)); 
    }
    
    if (args.Length() < 2) {
        return ThrowException(Exception::TypeError(String::New("Missing parameters. Algorithm and mode should be specified.")));
    }

    MCrypt* mcrypt = new MCrypt(args);

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    mcrypt->Wrap(args.This());

    return args.This();
}

NODE_MCRYPT_METHOD(Open) {
    HandleScope scope;

    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(String::New("Missing parameter. Key should be specified.")));
    }
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());
    
    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    if (args[0]->IsString()) {
        String::Utf8Value value(args[0]);
    
        mcrypt->key = std::string(*value, value.length());

    } else if (node::Buffer::HasInstance(args[0])) {
    
        mcrypt->key = std::string(node::Buffer::Data(args[0]), node::Buffer::Length(args[0]));

    } else {
        return ThrowException(Exception::TypeError(String::New("Key has got incorrect type. Should be Buffer or String.")));
    }

    if (mcrypt->checkKeySize) {
        std::vector<size_t> keySizes = mcrypt->getKeySizes();
    
        if (keySizes.size() > 0) {

            bool invalid = true;
            
            std::stringstream serror;
            
            serror << "Invalid key size. Available key size are [";
            
            for(size_t i = 0; i < keySizes.size(); i++) {
                
                if (i != 0) {
                    serror << ", ";
                }
                
                serror << keySizes[i];
                
                if (keySizes[i] == mcrypt->key.length()) {
                    invalid = false;
                }
            }

            serror << "]";
            
            std::string error = serror.str();

            if (invalid) {
                return ThrowException(Exception::TypeError(String::New(error.c_str(), error.length())));
            }
        }
    }

    if (args[1]->IsUndefined()) {
        return scope.Close(Undefined());
    }

    size_t ivLen;

    if (args[1]->IsString()) {
        
        String::Utf8Value value(args[1]);

        ivLen = value.length();
        mcrypt->iv = std::string(*value, ivLen);

    } else if (node::Buffer::HasInstance(args[1])) {

        ivLen = node::Buffer::Length(args[1]);
        mcrypt->iv = std::string(node::Buffer::Data(args[1]), ivLen);
    } else {
        return ThrowException(Exception::TypeError(String::New("Iv has got incorrect type. Should be Buffer or String.")));
    }

    if (mcrypt->checkIvSize) {
        if ((size_t)mcrypt_enc_get_iv_size(mcrypt->mcrypt_) != ivLen) {
            return ThrowException(Exception::TypeError(String::New("Invalid iv size. You can determine iv size using getIvSize()")));
        }
    }
    
    return scope.Close(Undefined());
}

NODE_MCRYPT_METHOD(Encrypt) {
    HandleScope scope;
    
    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(String::New("Missing parameter. Plaintext should be specified.")));
    }
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This()); 
    
    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int result = 0;
    node::Buffer* cipherText = node::Buffer::New(1); 

    if (args[0]->IsString()) {

        String::Utf8Value value(args[0]);  
        cipherText = mcrypt->transform<mcrypt_generic>(*value, value.length(), &result);
    
    } else if(node::Buffer::HasInstance(args[0])) {

        cipherText = mcrypt->transform<mcrypt_generic>(node::Buffer::Data(args[0]), node::Buffer::Length(args[0]), &result); 
        
    } else {
        return ThrowException(Exception::TypeError(String::New("Plaintext has got incorrect type. Should be Buffer or String.")));
    }
    
    if (result != 0) {
        const char* error = mcrypt_strerror(result);
        return ThrowException(Exception::Error(String::New(error)));
    }
    
    return scope.Close(cipherText->handle_);
}

NODE_MCRYPT_METHOD(Decrypt) {
    HandleScope scope;
    
    if (args.Length() < 1) {
        return ThrowException(Exception::TypeError(String::New("Missing parameter. Plaintext should be specified.")));
    }
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());
    
    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int result = 0;
    node::Buffer* plainText = node::Buffer::New(1); 

    if (args[0]->IsString()) {

        String::Utf8Value value(args[0]);
        plainText = mcrypt->transform<mdecrypt_generic>(*value, value.length(), &result);

    } else if (node::Buffer::HasInstance(args[0])) {
    
        plainText = mcrypt->transform<mdecrypt_generic>(node::Buffer::Data(args[0]), node::Buffer::Length(args[0]), &result);

    } else {
        return ThrowException(Exception::TypeError(String::New("Ciphertext has got incorrect type. Should be Buffer or String.")));
    }
    
    if (result != 0) {
        const char* error = mcrypt_strerror(result);
        return ThrowException(Exception::Error(String::New(error)));
    }
    
    return scope.Close(plainText->handle_);
}

NODE_MCRYPT_METHOD(ValidateKeySize) {
    HandleScope scope;

    if(args.Length() == 0) {
        return scope.Close(Undefined());
    }

    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());
    Local<Boolean> state = args[0]->ToBoolean();
    mcrypt->checkKeySize = state->Value();

    return scope.Close(Undefined());
}

NODE_MCRYPT_METHOD(ValidateIvSize) {
    HandleScope scope;

    if(args.Length() == 0) {
        return scope.Close(Undefined());
    }

    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());
    Local<Boolean> state = args[0]->ToBoolean();
    mcrypt->checkIvSize = state->Value();

    return scope.Close(Undefined());
}

NODE_MCRYPT_METHOD(SelfTest) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)

    if (mcrypt_enc_self_test(mcrypt->mcrypt_) == 0) {
        return scope.Close(True());
    }
    
    return scope.Close(False());
}

NODE_MCRYPT_METHOD(IsBlockAlgorithmMode) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    if (mcrypt_enc_is_block_algorithm_mode(mcrypt->mcrypt_) == 1) {
        return scope.Close(True());
    }
    
    return scope.Close(False());
}

NODE_MCRYPT_METHOD(IsBlockAlgorithm) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    if (mcrypt_enc_is_block_algorithm(mcrypt->mcrypt_) == 1) {
        return scope.Close(True());
    }
    
    return scope.Close(False());
}

NODE_MCRYPT_METHOD(IsBlockMode) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    if (mcrypt_enc_is_block_mode(mcrypt->mcrypt_) == 1) {
        return scope.Close(True());
    }
    
    return scope.Close(False());
}

NODE_MCRYPT_METHOD(GetBlockSize) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int blockSize = mcrypt_enc_get_block_size(mcrypt->mcrypt_);
    
    return scope.Close(Number::New(blockSize));
}

NODE_MCRYPT_METHOD(GetKeySize) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int keySize = mcrypt_enc_get_key_size(mcrypt->mcrypt_);
    
    return scope.Close(Number::New(keySize));
}

NODE_MCRYPT_METHOD(GetSupportedKeySizes) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    std::vector<size_t> keySizes = mcrypt->getKeySizes();

    Handle<Array> array = Array::New(keySizes.size());
    
    for (size_t i = 0; i < keySizes.size(); i++) {
        array->Set(i, Number::New(keySizes[i]));
    }
    
    return scope.Close(array);
}

NODE_MCRYPT_METHOD(GetIvSize) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int ivSize = mcrypt_enc_get_iv_size(mcrypt->mcrypt_);
    
    return scope.Close(Number::New(ivSize));
}

NODE_MCRYPT_METHOD(HasIv) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    if (mcrypt_enc_mode_has_iv(mcrypt->mcrypt_) == 1) {
        return scope.Close(True());
    }
    
    return scope.Close(False());
}

NODE_MCRYPT_METHOD(GetAlgorithmName) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    char* name = mcrypt_enc_get_algorithms_name(mcrypt->mcrypt_);
    Handle<String> ret = String::New(name);
    mcrypt_free(name);
    
    return scope.Close(ret);
}

NODE_MCRYPT_METHOD(GetModeName) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    char* name = mcrypt_enc_get_modes_name(mcrypt->mcrypt_);
    Handle<String> ret = String::New(name);
    mcrypt_free(name);
    
    return scope.Close(ret);
}

NODE_MCRYPT_METHOD(GenerateIv) {
    HandleScope scope;
    
    MCrypt* mcrypt = ObjectWrap::Unwrap<MCrypt>(args.This());

    MCRYPT_MODULE_ERROR_CHECK(mcrypt)
    
    int ivSize = mcrypt_enc_get_iv_size(mcrypt->mcrypt_);
    
    node::Buffer* buffer = node::Buffer::New(ivSize);
    
    char* iv = node::Buffer::Data(buffer);
    
    while(ivSize) {
        iv[--ivSize] = 255.0 * std::rand() / RAND_MAX;
    }
    
    return scope.Close(buffer->handle_);
}

NODE_MCRYPT_METHOD(GetAlgorithmNames) {
    HandleScope scope;
    
    String::Utf8Value path(args[0]);
    
    int size = 0;
    char** algos = mcrypt_list_algorithms(*path, &size);
    
    Handle<Array> array = Array::New(size);
    
    if (array.IsEmpty()) {
        return Handle<Array>();
    }
    
    for (int i = 0; i < size; i++) {
        array->Set(i, String::New(algos[i]));
    }
    
    mcrypt_free_p(algos, size);
    
    return scope.Close(array);
}

NODE_MCRYPT_METHOD(GetModeNames) {
    HandleScope scope;
    
    String::Utf8Value path(args[0]);
    
    int size = 0;
    char** modes = mcrypt_list_modes(*path, &size);
    
    Handle<Array> array = Array::New(size);
    
    if (array.IsEmpty())
        return Handle<Array>();
    
    for (int i = 0; i < size; i++) {
        array->Set(i, String::New(modes[i]));
    }
    
    mcrypt_free_p(modes, size);
    
    return scope.Close(array);
}

void MCrypt::Init(Handle<Object> exports) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("MCrypt"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1); 
    
    Local<ObjectTemplate> prototype = tpl->PrototypeTemplate(); 
    
    // prototype
    prototype->Set(String::NewSymbol("encrypt"), FunctionTemplate::New(Encrypt)->GetFunction());
    prototype->Set(String::NewSymbol("decrypt"), FunctionTemplate::New(Decrypt)->GetFunction());
    prototype->Set(String::NewSymbol("open"), FunctionTemplate::New(Open)->GetFunction());
    prototype->Set(String::NewSymbol("validateKeySize"), FunctionTemplate::New(ValidateKeySize)->GetFunction());
    prototype->Set(String::NewSymbol("validateIvSize"), FunctionTemplate::New(ValidateIvSize)->GetFunction());
    prototype->Set(String::NewSymbol("selfTest"), FunctionTemplate::New(SelfTest)->GetFunction());
    prototype->Set(String::NewSymbol("isBlockAlgorithmMode"), FunctionTemplate::New(IsBlockAlgorithmMode)->GetFunction());
    prototype->Set(String::NewSymbol("isBlockAlgorithm"), FunctionTemplate::New(IsBlockAlgorithm)->GetFunction());
    prototype->Set(String::NewSymbol("isBlockMode"), FunctionTemplate::New(IsBlockMode)->GetFunction());
    prototype->Set(String::NewSymbol("getBlockSize"), FunctionTemplate::New(GetBlockSize)->GetFunction());
    prototype->Set(String::NewSymbol("getKeySize"), FunctionTemplate::New(GetKeySize)->GetFunction());
    prototype->Set(String::NewSymbol("getSupportedKeySizes"), FunctionTemplate::New(GetSupportedKeySizes)->GetFunction());
    prototype->Set(String::NewSymbol("getIvSize"), FunctionTemplate::New(GetIvSize)->GetFunction());
    prototype->Set(String::NewSymbol("hasIv"), FunctionTemplate::New(HasIv)->GetFunction());
    prototype->Set(String::NewSymbol("getAlgorithmName"), FunctionTemplate::New(GetAlgorithmName)->GetFunction());
    prototype->Set(String::NewSymbol("getModeName"), FunctionTemplate::New(GetModeName)->GetFunction());
    prototype->Set(String::NewSymbol("generateIv"), FunctionTemplate::New(GenerateIv)->GetFunction());
    
    // exports
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("MCrypt"), constructor);
    exports->Set(String::NewSymbol("getAlgorithmNames"), FunctionTemplate::New(GetAlgorithmNames)->GetFunction());
    exports->Set(String::NewSymbol("getModeNames"), FunctionTemplate::New(GetModeNames)->GetFunction());
}

NODE_MODULE(mcrypt, MCrypt::Init)
