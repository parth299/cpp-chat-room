#include <iostream>
#include <string>
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class Message {
    public:
        Message(): bodyLength_(0){};
        enum {header = 4};
        enum {maxBytes = 512};

        Message(std::string message) {
            bodyLength_ = getNewBodyLength(message.size());
            encodeHeader();
        }

        size_t getNewBodyLength(size_t newLength) {
            if(newLength>maxBytes) {
                return maxBytes;
            }
            return newLength;
        }

        void encodeHeader() {
            char newHeader[header + 1] = "";
            snprintf(newHeader, sizeof(newHeader), "%4zu", bodyLength_);
            memcpy(data, newHeader, header);
        }

    private:
        char data[header+maxBytes];
        size_t bodyLength_;
        char newData[6] = "Hello";
};

#endif 