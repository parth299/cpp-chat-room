#include <iostream>
#include <string>
#include <cstring>

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
            std::memcpy(data+header, message.c_str(), bodyLength_);
        }

        size_t getNewBodyLength(size_t newLength) {
            if(newLength>maxBytes) {
                return maxBytes;
            }
            return newLength;
        }

        std::string getData() {
            std::string dataString(data, header+bodyLength_);
            return dataString;
        }
        std::string getBody() {
            std::string dataString = getData();
            std::string bodyString = dataString.substr(header, bodyLength_);
            return bodyString;
        }

        bool decodeHeader() {
            char new_header[header+1] = "";
            strncpy(new_header, data, header);
            new_header[header] = '\0';
            int headervalue = atoi(new_header);

            if(headervalue > maxBytes) {
                bodyLength_ = 0;
                return false;
            }
            bodyLength_ = headervalue;
            return true;
        }

        void encodeHeader() {
            char newHeader[header + 1] = "";
            snprintf(newHeader, sizeof(newHeader), "%4zu", bodyLength_);
            std::memcpy(data, newHeader, header);
        }

        size_t getBodyLength() {
            return bodyLength_;
        }

    private:
        char data[header+maxBytes];
        size_t bodyLength_;
        char newData[6] = "Hello";
};

#endif 