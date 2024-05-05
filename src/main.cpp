#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/controller/BindToRenderer.h"

#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Manager/DRFileManager.h"
#include "DRCore2/Threading/DRMultithreadLogger.h"

#include "rapidjson/error/en.h"

// some dll stuff for windows
int         g_iProzess = 0;
int			g_iProzessFunk = 0;
namespace UniLib {
	controller::BindToRenderer* g_RenderBinder = NULL;
	DRCPUScheduler* g_StorageScheduler = NULL;
}

#ifdef _WIN32
//DLL Main Funktion
int WINAPI DllMain(HINSTANCE DllHandle, unsigned long ReasonForCall, void* Reserved)
{
    //Wenn ein weiterer Prozess die dll benutzt
    switch (ReasonForCall)
    {
    case DLL_PROCESS_ATTACH:
        {
            //Der Referenzzähler wird um eins erhöht
            //Start
            g_iProzess++;
        } break;

    case DLL_PROCESS_DETACH:
        {
            //Der Referenzzähler wird um eins reduziert
            //Ende
            g_iProzess--;

            //Sicherstellen, das Exit aufgerufen wird
            if(g_iProzessFunk > g_iProzess)
            {
                LOG_WARNING("Exit musste automatisch aufgerufen werden! SDL");
                UniLib::exit();
                // GameDLLExit();
            }
        } break;

    }


    return 1;
}
#endif //_WIN32

namespace UniLib {
    using namespace lib;

    DRReturn init(int numberParallelStorageOperations/* = 1*/)
    {
		SDL_Init(SDL_INIT_TIMER);
        Core2_init("Logger.html");
        
		g_StorageScheduler = new DRCPUScheduler(numberParallelStorageOperations, "ioThrd");
        return DR_OK;
    }

    void exit() 
    {
		DR_SAVE_DELETE(g_StorageScheduler);
		SDL_Quit();
        Core2_exit();
    }

	std::string readFileAsString(std::string filename)
	{
		//std::string completePath = 
		const char* path = DRFileManager::Instance().getWholePfad(filename.data());
		std::string complete;
		if(path) {
			complete = std::string(path) + std::string("/") + std::string(filename);
		}
		else {
			complete = std::string(filename);
		}

		DRFile file(complete.data(), "rb");
		if(!file.isOpen()) LOG_ERROR("Error by opening file", std::string());
		unsigned long size = file.getSize();
		void* data = malloc(size+1);
		memset(data, 0, size+1);
		if(file.read(data, size, 1)) 
			LOG_ERROR("Error by reading config", std::string());
		file.close();
		/// parsing

		std::string result((const char*)data);
		
		free(data);
		return result;
	}

	rapidjson::Document convertStringToRapidJson(std::string jsonString)
	{
		rapidjson::Document d;
		d.Parse(jsonString.data());
		if (d.HasParseError()) {
			LOG_ERROR(rapidjson::GetParseError_En(d.GetParseError()), rapidjson::Document());
		}
		return d;
	}

	void setBindToRenderer(controller::BindToRenderer* bindToRender)
	{
		g_RenderBinder = bindToRender;
	}

}