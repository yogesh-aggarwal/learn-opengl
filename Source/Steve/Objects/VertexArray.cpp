#include "VertexArray.hpp"

#include <glad/glad.h>

Result<bool>
VertexArray::AllocateAndBind()
{
   glGenVertexArrays(1, &m_ID);
   Bind();

   return true;
}

Result<bool>
VertexArray::Bind()
{
   glBindVertexArray(m_ID);

   return true;
}

Result<bool>
VertexArray::Unbind()
{
   glBindVertexArray(0);

   return true;
}