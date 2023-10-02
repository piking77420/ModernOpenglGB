import CorePython
from CorePython import*


class CamerMovement(PythonScript) : 


    def Init(self, scene : Scene):
       return _CorePython.PythonScript_Init(self, scene)

    def Awake(self, scene):
        return _CorePython.PythonScript_Awake(self, scene)

    def Start(self, scene):
        return _CorePython.PythonScript_Start(self, scene)

    def OnDrawGizmo(self, scene):
        return _CorePython.PythonScript_OnDrawGizmo(self, scene)

    def FixedUpdate(self, scene):
        return _CorePython.PythonScript_FixedUpdate(self, scene)

    def Update(self, scene : Scene):
        t = scene.GetComponent()
        print("PYTHONNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN")

    def LateUpdate(self, scene):
        return _CorePython.PythonScript_LateUpdate(self, scene)

    def Render(self, shader, scene):
        return _CorePython.PythonScript_Render(self, shader, scene)

    def OnResizeData(self, ComponentTypeID, data):
        return _CorePython.PythonScript_OnResizeData(self, ComponentTypeID, data)

