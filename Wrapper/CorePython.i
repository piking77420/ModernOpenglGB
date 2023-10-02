%module CorePython

%{
    #include "../source/include/External/glad/glad.h"

    #include "../source/include/Core/ECS/Register.h"
    #include "../source/include/Core/ECS/Register.h"

    
    #include "../source/include/Core/ECS/Component.h"
	#include "../source/include/Core/ECS/ECSComponent.h"
	#include "../source/include/Core/ECS/Entity.h"

	#include "../source/include/Core/ECS/PythonScript.h"
	#include "../source/include/Core/ECS/IECSSystem.h"
    #include "../source/include/Core/ECS/Scene.h"



	#include "../source/include/Physics/GraphScene/GraphScene.h"
	#include "../source/include/Physics/Transform/Transform.hpp"

    #include "../source/include/Ressources/Mesh/Mesh.h"
    #include "../source/include/Ressources/Texture/Texture.hpp"


	#include "../source/include/Core/Math/Vector2.h"
    #include "../source/include/Core/Math/Vector3.h"
    #include "../source/include/Core/Math/Vector4.h"
    #include "../source/include/Core/Math/Matrix2X2.h"
    #include "../source/include/Core/Math/Matrix3X3.h"
    #include "../source/include/Core/Math/Matrix4X4.h"

    #include "../source/include/LowRenderer/Cam/Camera.h"



	// Define necessary typedefs and using statements here
    typedef uint32_t (*ECSComponentCreateFunction)(std::vector<uint8_t>& memory, Entity* entity, Component** ptr);
    typedef void(*ECSComponentFreeFunction)(Component* ptr);
    typedef std::string (*GetNameOfComponent)();
%}



Transform* Scene::GetComponent_Transform(Entity* entity) {
    return reinterpret_cast<Transform*>(m_registerScene.GetComponentInternal(Transform::componentTypeID, entity));
}


%include <std_string.i>
%include <std_vector.i>
%include <std_pair.i>
%include <std_map.i>
%include "std_unordered_map.i"

%include "../source/include/External/glad/glad.h"

%include "../source/include/Core/ECS/Component.h"
%include "../source/include/Core/ECS/ECSComponent.h"
%template(EcsComponent_Transform) EcsComponent<Transform>;






%include "../source/include/Core/ECS/Entity.h"
%include "../source/include/Core/ECS/Register.h"


%template(ComponentsData) std::vector< std::pair<uint32_t, std::vector<uint8_t>* >>;
%template(entities) std::vector<Entity*>;
%template(systems) std::vector<IEcsSystem*>;



%include "../source/include/Ressources/Mesh/Mesh.h"
%include "../source/include/Ressources/Texture/Texture.hpp"

%include "../source/include/Core/ECS/Scene.h"
%include "../source/include/Core/ECS/IECSSystem.h"
%include "../source/include/Core/ECS/PythonScript.h"
%include "../source/include/Physics/GraphScene/GraphScene.h"
%include "../source/include/Physics/Transform/Transform.hpp"



%include "../source/include/Core/Math/Vector2.h"
%include "../source/include/Core/Math/Vector3.h"
%include "../source/include/Core/Math/Vector4.h"
%include "../source/include/Core/Math/Matrix2X2.h"
%include "../source/include/Core/Math/Matrix3X3.h"
%include "../source/include/Core/Math/Matrix4X4.h"




%include "../source/include/LowRenderer/Cam/Camera.h"




%extend Vector2 {

	  float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
    }
}


%extend Vector3 {
   float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        if (index == 2) return $self->z;
        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
        if (index == 2) $self->z = value;
    }

}

%extend Vector4 {

      float __getitem__(int index) const {
        if (index == 0) return $self->x;
        if (index == 1) return $self->y;
        if (index == 2) return $self->z;
        if (index == 2) return $self->w;

        return 0.0;
    }

      void __setitem__(int index, float value) {
        if (index == 0) $self->x = value ;
        if (index == 1) $self->y = value;
        if (index == 2) $self->z = value;
        if (index == 2) $self->w = value;
    }
    %rename(toVector2) operator Vector2;
}



