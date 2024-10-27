#include <Application/UApplication.hpp>
#include <Application/UApplicationDelegate.hpp>

#include <cstdio>

class AppDelegate: public UApplicationDelegate
{
public:
    void ApplicationDidFinishLaunching(UApplication *application, UWindow* window) override
    {
        printf("ApplicationDidFinishLaunching\n");
    }

    void ApplicationWillTerminate(UApplication *application) override
    {
        printf("ApplicationWillTerminate\n");
    }

};


int main(int argc, char* argv[])
{   
    
    UApplication app;
    AppDelegate appDelegate;

    return app.Run(&appDelegate);
}