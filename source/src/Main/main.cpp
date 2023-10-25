#include "App/App.h"
#include"EasyFunction.h"

 
   int main()
   {
		GLFWwindow* widnow = App::InitOpenglImgui();
        App app;


        app.AppUpdate(widnow); 
        return 0;
   }

    