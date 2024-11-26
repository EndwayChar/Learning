#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


// 加载图像
SDL_Surface * loadSurface(std::string path);
// 加载纹理
SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
int main(int argc, char* argv[])
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    } 

    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("first SDL program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    // 创建一个简单的图像纹理
    SDL_Texture *texture = loadTexture("/home/superlinux/code/c_cpp_code/pokemen/assets/images/test_image.png", renderer);
    if (!texture)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_SetWindowSize(window, width, height);
    while(1)
    {
        // 关闭窗口
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // 清理资源
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }
        SDL_RenderClear(renderer);
        renderTexture(texture, renderer, 0, 0);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
/**
 * 加载图像到SDL_Surface对象中。
 * 
 * @param path 图像文件的路径。
 * @return 返回一个指向SDL_Surface对象的指针，如果加载失败则返回NULL。
 *
 * 此函数使用SDL_image库的IMG_Load函数来加载图像。
 * 如果图像加载失败，会打印错误信息到标准输出。
 */
SDL_Surface * loadSurface(std::string path)
{
    // 使用SDL_image库加载图像。
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    
    // 检查图像是否成功加载。
    if (loadedSurface == NULL)
    {
        // 如果图像加载失败，打印错误信息。
        std::cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
    }
    
    // 返回加载的图像表面。
    return loadedSurface;
}
// 加载纹理
/**
 * 加载图像文件并创建纹理
 * 
 * @param path 图像文件的路径
 * @param renderer SDL渲染器，用于创建纹理
 * @return 返回创建的纹理指针，如果加载失败则返回nullptr
 * 
 * 此函数使用SDL_image库加载指定路径的图像文件，并使用SDL渲染器创建纹理
 * 如果图像文件加载失败，将打印错误信息并返回nullptr
 */
SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer) {
    // 初始化纹理指针为nullptr
    SDL_Texture* newTexture = nullptr;
    
    // 加载图像文件到SDL_Surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    
    // 如果图像文件加载失败，打印错误信息
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        // 使用加载的图像表面创建纹理
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        
        // 释放图像表面资源
        SDL_FreeSurface(loadedSurface);
    }
    
    // 返回创建的纹理
    return newTexture;
}
/**
 * 渲染纹理到指定位置
 * 
 * 该函数将一个SDL纹理渲染到渲染器指定的位置它首先创建一个SDL_Rect结构体来定义渲染的位置和大小，
 * 然后查询纹理的尺寸以设置SDL_Rect的宽度和高度，最后将纹理渲染到指定的矩形区域
 * 
 * @param texture 要渲染的SDL纹理指针
 * @param renderer SDL渲染器指针，用于渲染纹理
 * @param x 纹理渲染位置的x坐标
 * @param y 纹理渲染位置的y坐标
 */
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y)
{
    // 初始化SDL_Rect结构体，设置渲染位置
    SDL_Rect dstrect = {x, y, 0, 0};
    
    // 查询纹理的宽度和高度，并存储到dstrect中
    SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
    std:: cout << dstrect.w << dstrect.h << std::endl;
    // 将纹理渲染到指定的矩形区域
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}