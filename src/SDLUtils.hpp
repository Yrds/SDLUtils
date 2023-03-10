#ifndef SDL_UTILS_INCLUDED
#define SDL_UTILS_INCLUDED


#include <memory>
#include <functional>

#include "SDL2/SDL.h"

namespace SDLUtils {

inline SDL_Point addPoints(SDL_Point pointA, SDL_Point pointB) {
  return {pointA.x + pointB.x, pointA.y + pointB.y};
}

inline SDL_Rect textureRect(SDL_Texture *texture, SDL_Point relative = {0,0}) {
  int width = 0;
  int height = 0;

  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  return {relative.x, relative.y, width, height};
}

using Window = std::unique_ptr<SDL_Window, std::function<void (SDL_Window*)>>;

template<typename... Args>
inline Window createWindow(Args ...args) {
  return {
    SDL_CreateWindow(std::forward<Args>(args)...),
    SDL_DestroyWindow
  };
}

using Renderer = std::unique_ptr<SDL_Renderer, std::function<void (SDL_Renderer*)>>;
template<typename... Args>
inline Renderer createRenderer(Args ...args) {
  return {
    SDL_CreateRenderer(std::forward<Args>(args)...),
    SDL_DestroyRenderer
  };
}

using Texture = std::unique_ptr<SDL_Texture, std::function<void (SDL_Texture*)>>;

template<typename... Args>
inline Texture imgLoadTexture(Args ...args) {
  return {
    IMG_LoadTexture(std::forward<Args>(args)...),
    SDL_DestroyTexture,
  };
}


inline bool testCollision(SDL_Rect &rectA, SDL_Rect &rectB) {
  return (rectA.x < rectB.x + rectB.w && rectA.x + rectA.w > rectB.x &&
          rectA.y < rectB.y + rectB.h && rectA.h + rectA.y > rectB.y);
}

}


#endif // SDL_UTILS_INCLUDED
