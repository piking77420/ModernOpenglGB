#include "Mathf.h"



bool Mathf::IsEqual(float value, float value2)
{

  if(value2 < value)
  {
      if (value2 + TOLERANCE <= value)
      { 
          return true;
      }
      else
      {
          return false;

      } 
  }
  else 
  {
      if (value + TOLERANCE >= value2)
      {
          return true;
      }
      else
      {
          return false;
      }
  }



    return false;
}

Mathf::Mathf()
{
}

Mathf::~Mathf()
{
}
