#ifndef cakengine_graphics_opengl_h
#define cakengine_graphics_opengl_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../../api.hpp"


/**
	TYPES CONSTANTS
*/

typedef struct CKType{
	GLenum glconst:16;
	Uint32 size:16;
}CKType;
extern const CKType CK_TYPE_BYTE;
extern const CKType CK_TYPE_UNSIGNEDBYTE;
extern const CKType CK_TYPE_SHORT;
extern const CKType CK_TYPE_UNSIGNEDSHORT;
extern const CKType CK_TYPE_INT;
extern const CKType CK_TYPE_UNSIGNEDINT;
extern const CKType CK_TYPE_FLOAT;
extern const CKType CK_TYPE_2BYTES;
extern const CKType CK_TYPE_3BYTES;
extern const CKType CK_TYPE_4BYTES;
extern const CKType CK_TYPE_DOUBLE;


/**
	RENDER MODE CONSTANTS
*/

enum CKRenderMode{
	CK_RENDERMODE_TRIANGLES = GL_TRIANGLES,
	CK_RENDERMODE_TRIANGLEFAN = GL_TRIANGLE_FAN,
	CK_RENDERMODE_TRIANGLESTRIP = GL_TRIANGLE_STRIP,
	CK_RENDERMODE_LINES = GL_LINES,
	CK_RENDERMODE_LINESTRIP = GL_LINE_STRIP,
	CK_RENDERMODE_LINELOOP = GL_LINE_LOOP,
	CK_RENDERMODE_POINTS = GL_POINTS,
};


/**
	PIXEL FORMAT CONSTANTS
*/

struct CKPixelFormat{
	SDL_PixelFormat *sdl_format;
	GLenum gl_format:16;
	GLenum gli_formatinternal:16;
	GLenum gli_format:16;
};
extern const CKPixelFormat CK_PIXELFORMAT_RGB888;
extern const CKPixelFormat CK_PIXELFORMAT_RGBA8888;


/**
	FRAMEBUFFER MODE CONSTANTS
*/

struct CKFramebufferMode{
	GLenum format_internal:16;
	GLenum format:16;
	GLenum attach_mode:16;
	GLenum texture_type:16;
};
extern CKFramebufferMode CK_FRAMEBUFFERMODE_COLOR;
extern CKFramebufferMode CK_FRAMEBUFFERMODE_DEPTH;
extern CKFramebufferMode CK_FRAMEBUFFERMODE_STENCIL;


/**
	FACE CULLING MODE CONSTANTS
*/

enum CKFaceCullingMode{
	CK_FACECULLINGMODE_FRONT = GL_FRONT,
	CK_FACECULLINGMODE_BACK = GL_BACK,
	CK_FACECULLINGMODE_FRONTANDBACK = GL_FRONT_AND_BACK
};


/**
	FACE FRONT MODE CONSTANTS
*/

enum CKFrontFace{
	CK_FRONTFACE_CLOCKWISE = GL_CW,
	CK_FRONTFACE_COUNTERCLOCKWISE = GL_CCW
};


#endif // cakengine_graphics_opengl_h
