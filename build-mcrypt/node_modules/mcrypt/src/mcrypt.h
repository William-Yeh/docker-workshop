
#ifndef SRC_NODE_MCRYPT_H_
#define SRC_NODE_MCRYPT_H_

#include <vector> 
#include <algorithm> 
#include <sstream>

#include <node.h>
#include <node_buffer.h>
#include <mcrypt.h>

#define MCRYPT_MODULE_ERROR_CHECK(mcrypt) if (mcrypt->mcrypt_ == MCRYPT_FAILED) { \
        return ThrowException(Exception::ReferenceError(String::New("MCrypt module could not open"))); \
    }

#define NODE_MCRYPT_METHOD_PROTO(MethodName) static Handle<Value> MethodName(const Arguments& args)
#define NODE_MCRYPT_METHOD(MethodName) Handle<Value> MCrypt::MethodName(const Arguments& args)
    
using namespace v8;

class MCrypt : public node::ObjectWrap {
    public:
        static void Init(Handle<Object> exports);
    
    private:
        MCrypt(const Arguments& args);
        ~MCrypt();
        
        template <int (*modify)(MCRYPT, void *, int)>
        node::Buffer* transform(const char* plainText, const size_t length, int* result);

        std::vector<size_t> getKeySizes();
        
        static Persistent<Function> constructor;

        NODE_MCRYPT_METHOD_PROTO(New);
        NODE_MCRYPT_METHOD_PROTO(Encrypt);
        NODE_MCRYPT_METHOD_PROTO(Decrypt);
        NODE_MCRYPT_METHOD_PROTO(Open);
        NODE_MCRYPT_METHOD_PROTO(ValidateKeySize);
        NODE_MCRYPT_METHOD_PROTO(ValidateIvSize);
        NODE_MCRYPT_METHOD_PROTO(SelfTest);
        NODE_MCRYPT_METHOD_PROTO(IsBlockAlgorithmMode);
        NODE_MCRYPT_METHOD_PROTO(IsBlockAlgorithm);
        NODE_MCRYPT_METHOD_PROTO(IsBlockMode);
        NODE_MCRYPT_METHOD_PROTO(GetBlockSize);
        NODE_MCRYPT_METHOD_PROTO(GetKeySize);
        NODE_MCRYPT_METHOD_PROTO(GetSupportedKeySizes);
        NODE_MCRYPT_METHOD_PROTO(GetIvSize);
        NODE_MCRYPT_METHOD_PROTO(HasIv);
        NODE_MCRYPT_METHOD_PROTO(GetAlgorithmName);
        NODE_MCRYPT_METHOD_PROTO(GetModeName);
        NODE_MCRYPT_METHOD_PROTO(GenerateIv);
        NODE_MCRYPT_METHOD_PROTO(Close);

        NODE_MCRYPT_METHOD_PROTO(GetAlgorithmNames);
        NODE_MCRYPT_METHOD_PROTO(GetModeNames);
        
        MCRYPT mcrypt_;
        std::string key;
        std::string iv;

        bool checkKeySize;
        bool checkIvSize;
        
        String::AsciiValue algo;
        String::AsciiValue mode;
        String::AsciiValue algoDir;
        String::AsciiValue modeDir;
};

#endif  // ~ SRC_NODE_MCRYPT_H_
