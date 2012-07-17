#include <iostream>
#include <string.h>

#include <SDL.h>
#include <GL/glew.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common/die.h"
#include "common/defaults.h"

#include "client/view/video.h"

int main(void)
{
  InitVideo();

  GLuint vao;
  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  GLuint vbo;
  glGenBuffers( 1, &vbo ); // Generate 1 buffer

  float vertices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  GLuint prog = LoadShaders("resources/shaders/first.vert",
    "resources/shaders/first.frag");

  GLint posAttrib = glGetAttribLocation(prog, "position");
  glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( posAttrib );

  SDL_Event windowEvent;
  while ( true )
  {
    if ( SDL_PollEvent( &windowEvent ) )
    {
      if ( windowEvent.type == SDL_QUIT ) break;
    }
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}


int net_main(void)
{
  struct sockaddr_in sad;
  int fd;

  std::cout << "Setting up udp socket on port " << SERVER_PORT << std::endl;

  if (0 > (fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    die("socket");

  memset(&sad, 0, sizeof(sad));
  sad.sin_family = AF_INET;
  sad.sin_port = htons(SERVER_PORT);
  if (!inet_aton(SERVER_ADDR, &sad.sin_addr))
    die("inet_aton");

  connect(fd, reinterpret_cast<struct sockaddr*>(&sad), sizeof(sad));
  send(fd, "HI", 3, 0);

  close(fd);

  return 0;
}
