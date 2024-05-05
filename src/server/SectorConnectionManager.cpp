#include "server/SectorConnectionManager.h"
#include "server/ConnectionToAccountServer.h"
#include "lib/CommandEventManager.h"

namespace UniLib {
	namespace server {

		SectorConnectionManager* SectorConnectionManager::mpInstanz = NULL;

		SectorConnectionManager::SectorConnectionManager()
            : Thread("UniSecCon"), mAccountServer(NULL), mLoginSuccessfully(false), mInitalized(false), 
			mNetRequestsMemoryList(NET_REQUEST_MEMORY_LIST_OBJECT_COUNT), mEventManager(NULL)
		{
            
		}

		SectorConnectionManager::~SectorConnectionManager() 
		{
            DR_SAVE_DELETE(mAccountServer); 
			if(mEventManager) mEventManager->exit();
			DR_SAVE_DELETE(mEventManager);
		}

		SectorConnectionManager* const SectorConnectionManager::getInstance()
		{
			if(!mpInstanz) {
				mpInstanz = new SectorConnectionManager;
			}

			return (SectorConnectionManager*)mpInstanz;
		}

         int SectorConnectionManager::ThreadFunction()
         {			 			  
			 if(mAccountServer) {
				mAccountServer->update();
			 }
             // return good
             return 0;
         }
		 DRReturn SectorConnectionManager::init()
		 {
			 mEventManager = new lib::CommandEventManager;
			 mEventManager->init();
			 return DR_OK;
		 }
         void SectorConnectionManager::login(const char* username, const char* password, DRNetServerConfig* accountServerConfig)
         {
			 if(mAccountServer && mAccountServer->isLogin()) return;
			 if(!mAccountServer) {
				mAccountServer = new ConnectionToAccountServer(accountServerConfig, mEventManager);
				mAccountServer->init();
				mAccountServer->login(username, password);
			 }
			 
             //DRNetRequest* request = getFreeNetRequest();
             //request->method         
         }
       /*  DRReturn SectorConnectionManager::sendRequest(DRNetRequest* request, RequestType type, model::SectorID* sektorID, CallbackCommand* callback)
         {
             lock();
             switch(type) {
             case REQUEST_TYPE_LOGIN: mAccountServer->sendRequest(request, sektorID, callback);
             }
             unlock();
             return DR_OK;
         }
	   */
         // memory management
         DRNetRequest* SectorConnectionManager::getFreeNetRequest()
         {
			 DRNetRequest* request = mNetRequestsMemoryList.NewInstance();
			 if(!request) LOG_ERROR("no space left for a new net request", NULL);
			 return request;
         }
         void SectorConnectionManager::freeNetRequest(DRNetRequest* request)
         {
             mNetRequestsMemoryList.FreeInstance(request);
         }

	}
}

