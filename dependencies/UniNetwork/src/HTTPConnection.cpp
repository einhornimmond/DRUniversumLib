#include "UniNetworkHeader.h"

using namespace Json;
using namespace Poco;
using namespace Poco::Net;

HTTPConnection::HTTPConnection(Json::Value cfg)
	: Connection(1000)
{
	mClientSession.setPort(cfg.get("port", Value(80)).asInt());
	mClientSession.setHost(cfg.get("ip", Value("localhost")).asString());
}

HTTPConnection::~HTTPConnection()
{

}

DRReturn HTTPConnection::run() 
{
	// get send request from queue
	mRequestMutex.lock();
	if(mSendRequests.size() == 0) {
		mRequestMutex.unlock();
		return DR_OK;
	}
	Json::Value sendRequest = mSendRequests.front();
	mSendRequests.pop();
	mRequestMutex.unlock();

	// parse and request
	HTTPRequest request(sendRequest.get("method", "GET").asString(), sendRequest.get("url", "").asString());
	if(sendRequest.get("contentType", "").asString() != "") {
		request.setContentType(sendRequest.get("contentType", "").asString());
		std::string body = sendRequest.get("content", "").asString();
		request.setContentLength((int)body.length());
		mClientSession.sendRequest(request) << body;		
	}
	else {
		mClientSession.sendRequest(request);
	}

	// recv answear
	HTTPResponse response;
	std::string responseString;
	mClientSession.receiveResponse(response) >> responseString;
	mRecvMutex.lock();
	mReciveDatas.push(responseString);
	mRecvMutex.unlock();

	return DR_OK;	
}

DRNet_Status HTTPConnection::send(Json::Value sendRequest)
{
	mRequestMutex.lock();
	mSendRequests.push(sendRequest);
	mRequestMutex.unlock();
	return NET_OK;
}

DRNet_Status HTTPConnection::recv(Json::Value& recvDatas)
{
	mRecvMutex.lock();
	if(mReciveDatas.size() == 0) {
		mRecvMutex.unlock();
		return NET_NOT_READY;
	}
	recvDatas = mReciveDatas.front();
	mReciveDatas.pop();
	mRecvMutex.unlock();
	return NET_COMPLETE;	
}