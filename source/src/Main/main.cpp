#include "App/App.h"


 
   int main()
   {
		GLFWwindow* widnow = App::InitOpenglImgui();
        App::InitEcsComponent();
        App app;
        app.AppUpdate(widnow); 
        return 0;
   }

