#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/controller/BindToRenderer.h"

#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Manager/DRFileManager.h"
#include "DRCore2/Threading/DRMultithreadLogger.h"

#include "rapidjson/error/en.h"

#include "SDL.h"

// some dll stuff for windows
int         g_iProzess = 0;
int			g_iProzessFunk = 0;
namespace UniLib {
	controller::BindToRenderer* g_RenderBinder = nullptr;
	DRCPUScheduler* g_StorageScheduler = nullptr;
	DRCPUScheduler* g_MainScheduler = nullptr;
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

    DRReturn init(int cpuWorkerCount, int numberParallelStorageOperations/* = 1*/)
    {
		SDL_Init(SDL_INIT_TIMER);
        Core2_init("Logger.html");
        
		g_StorageScheduler = new DRCPUScheduler(numberParallelStorageOperations, "ioThrd");
		g_MainScheduler = new DRCPUScheduler(cpuWorkerCount, "mainWork");
        return DR_OK;
    }

    void exit() 
    {
		DR_SAVE_DELETE(g_StorageScheduler);
		DR_SAVE_DELETE(g_MainScheduler);
		SDL_Quit();
        Core2_exit();
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