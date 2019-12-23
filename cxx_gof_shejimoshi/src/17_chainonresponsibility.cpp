#include <iostream>
#include <string>

using namespace std;

namespace DataDefine {
enum RequestType
{
    REQ_HANDLER1,
    REQ_HANDLER2,
    REQ_HANDLER3
};
};

class Reqest
{
    string description;
    DataDefine::RequestType reqType;
public:
    Reqest(const string &desc, DataDefine::RequestType type) : description(desc), reqType(type) {}
    DataDefine::RequestType getReqType() const { return reqType; }
    const string& getDescription() const { return description; }
};

class ChainHandler{
private: 
    ChainHandler *nextChain;
    void sendReqestToNextHandler(const Reqest & req)
    {
        if (nextChain != NULL)
            nextChain->handle(req);
    }

public:
    ChainHandler() { nextChain = NULL; }
    void setNextChain(ChainHandler *next) { nextChain = next; }

    virtual bool canHandleRequest(const Reqest & req) = 0;
    virtual void processRequest(const Reqest & req) = 0;
    
   
    void handle(const Reqest & req)
    {
        if (canHandleRequest(req))
            processRequest(req);
        else
            sendReqestToNextHandler(req);
    }
};


class Handler1 : public ChainHandler{
protected:
    bool canHandleRequest(const Reqest & req)
    {
        cout << "Handler1 canHandleRequest..." << endl;
        return req.getReqType() == DataDefine::REQ_HANDLER1;
    }
    void processRequest(const Reqest & req)
    {
        cout << "Handler1 is handle reqest: " << req.getDescription() << endl;
    }
};
        
class Handler2 : public ChainHandler{
protected:
    bool canHandleRequest(const Reqest & req)
    {
        cout << "Handler2 canHandleRequest..." << endl;
        return req.getReqType() == DataDefine::REQ_HANDLER2;
    }
    void processRequest(const Reqest & req)
    {
        cout << "Handler2 is handle reqest: " << req.getDescription() << endl;
    }
};

class Handler3 : public ChainHandler{
protected:
    bool canHandleRequest(const Reqest & req)
    {
        cout << "Handler3 canHandleRequest..." << endl;
        return req.getReqType() == DataDefine::REQ_HANDLER3;
    }
    void processRequest(const Reqest & req)
    {
        cout << "Handler3 is handle reqest: " << req.getDescription() << endl;
    }
};

int main(){
    Handler1 h1;
    Handler2 h2;
    Handler3 h3;
    h1.setNextChain(&h2);
    h2.setNextChain(&h3);
    
    Reqest req("process task ... ", DataDefine::REQ_HANDLER3);
    h1.handle(req);
    return 0;
}
