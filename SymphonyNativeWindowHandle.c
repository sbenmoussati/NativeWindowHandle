#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#pragma comment( lib, "user32.lib" )

static HWND getMainContentNativeWindowHandle(HWND parentWindowHwnd) {
  if( parentWindowHwnd == NULL ) {
			return NULL;
		}
    
    HWND childWindowHwnd = FindWindowExA(parentWindowHwnd, 0, "Chrome_RenderWidgetHostHWND", NULL);
    HWND titlebarWindowHwnd = NULL;
    HWND contentWindowHwnd = NULL;
    RECT titlebarRect;
    RECT rect;
    do {
      if(GetWindowRect(childWindowHwnd, &rect)) {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
      }
      if(titlebarWindowHwnd == NULL) {
        titlebarWindowHwnd = childWindowHwnd;
        contentWindowHwnd = childWindowHwnd;
        GetWindowRect(childWindowHwnd, &titlebarRect);
      } else {
        if(childWindowHwnd && (rect.bottom - rect.top < titlebarRect.bottom - titlebarRect.top)) {
          GetWindowRect(childWindowHwnd, &titlebarRect);
          contentWindowHwnd = titlebarWindowHwnd;
          titlebarWindowHwnd = childWindowHwnd;
        }
      }
      childWindowHwnd = FindWindowExA(parentWindowHwnd, childWindowHwnd, "Chrome_RenderWidgetHostHWND", NULL);
    }
    while(childWindowHwnd != NULL);
		if( contentWindowHwnd == NULL ) {
      printf("fail, child window not found", contentWindowHwnd);
			return NULL;
		} else if (contentWindowHwnd != titlebarWindowHwnd) {
      return contentWindowHwnd;
    }
    return parentWindowHwnd;
}

int main( int argc, char* argv[] ) {
	if( argc == 2 ) {
		HWND parentWindowHwnd = (HWND)( (uintptr_t) atoll( argv[ 1 ] ) );
    HWND mainWindowContentHwnd = getMainContentNativeWindowHandle(parentWindowHwnd);
		if(mainWindowContentHwnd != NULL) {
      int a = (int)mainWindowContentHwnd;
      printf("%i", a);
      return EXIT_SUCCESS;
    }
	} else {
	  return EXIT_FAILURE;
  }
}
