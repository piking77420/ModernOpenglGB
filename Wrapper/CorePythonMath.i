%module CorePythonMath

%{
	#include "../source/include/Core/Math/Vector2.h"
    #include "../source/include/Core/Math/Vector3.h"
    #include "../source/include/Core/Math/Vector4.h"
    #include "../source/include/Core/Math/Matrix2X2.h"
    #include "../source/include/Core/Math/Matrix3X3.h"
    #include "../source/include/Core/Math/Matrix4X4.h"
%}


%include "std_string.i"

%include "../source/include/Core/Math/Vector2.h"
%include "../source/include/Core/Math/Vector3.h"
%include "../source/include/Core/Math/Vector4.h"
%include "../source/include/Core/Math/Matrix2X2.h"
%include "../source/include/Core/Math/Matrix3X3.h"
%include "../source/include/Core/Math/Matrix4X4.h"


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