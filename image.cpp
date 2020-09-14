#include "image.h"

void Image::saveImage(string fileName,vector<unsigned char> &maze, const Feature &f)
{
    float initial=1;
    float p=initial;
    sf::Color quadColor;

    int width=(f.cols * f.cellSize) + 20;
    int height=(f.rows * f.cellSize) + 20;

    sf::Uint8 *pixels=new sf::Uint8[width * height * 4];

    for(int x = 0; x < width; x++)
    {
            for(int y = 0; y < 10; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

     for(int x = 0; x < 10; x++)
    {
            for(int y = 0; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

 for(int x = 0; x < width; x++)
    {
            for(int y = height-10; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

 for(int x = width-10; x <width; x++)
    {
            for(int y =0; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

    for(int x=0;x<f.rows;x++)
    {
        for(int y=0;y<f.cols;y++)
        {

            quadColor.r=(f.start.r*p)+(f.end.r*(1-p));
            quadColor.g=(f.start.g*p)+(f.end.g*(1-p));
            quadColor.b=(f.start.b*p)+(f.end.b*(1-p));
            for(int i=y * f.cellSize + 10;i<y * f.cellSize + 10 +f.cellSize;i++)
            {
                for(int j=x * f.cellSize + 10;j< x* f.cellSize + 10 + f.cellSize;j++)
                {
                    pixels[((i + j * (width )) * 4 )+ 0]=quadColor.r;
                    pixels[((i + j * (width )) * 4 )+ 1]=quadColor.g;
                    pixels[((i + j * (width )) * 4 )+ 2]=quadColor.b;
                    pixels[((i + j * (width )) * 4 )+ 3]=255;
                }      
            }

             if(maze[f.cols * x + y] & topMask)
            {
                for(int i=(y * f.cellSize + 10);i<=(y * f.cellSize +f.cellSize + 10);i++)
                {
                    pixels[((i + (x * f.cellSize +10) * (width)) * 4 )+ 0]=f.borderColor.r;
                    pixels[((i + (x * f.cellSize + 10) * (width )) * 4 )+ 1]=f.borderColor.g;
                    pixels[((i + (x * f.cellSize +10 ) * (width )) * 4 )+ 2]=f.borderColor.b;
                    pixels[((i + (x * f.cellSize+10) * (width )) * 4 )+ 3]=255;
                }
            }

             if(maze[f.cols * x + y] & rightMask)
            {
                for(int i=(x * f.cellSize + 10);i<=(x * f.cellSize +f.cellSize + 10);i++)
                {
                    pixels[(((y * f.cellSize + f.cellSize +10) + i* (width)) * 4 )+ 0]=f.borderColor.r;
                    pixels[(((y * f.cellSize + f.cellSize +10) + i* (width)) * 4 )+ 1]=f.borderColor.g;
                    pixels[(((y * f.cellSize  + f.cellSize+10) + i* (width )) * 4 )+ 2]=f.borderColor.b;
                    pixels[(((y * f.cellSize + f.cellSize +10) + i* (width )) * 4 )+ 3]=255;
                }
            }
            if(maze[f.cols * x + y] & leftMask)
            {
                for(int i=(x * f.cellSize + 10);i<=(x * f.cellSize +f.cellSize + 10);i++)
                {
                    pixels[(((y * f.cellSize  +10) + i* (width )) * 4 )+ 0]=f.borderColor.r;
                    pixels[(((y * f.cellSize  +10) + i* (width )) * 4 )+ 1]=f.borderColor.g;
                    pixels[(((y * f.cellSize  +10) + i* (width )) * 4 )+ 2]=f.borderColor.b;
                    pixels[(((y * f.cellSize  +10) + i* (width )) * 4 )+ 3]=255;
                }
            }
            if(maze[f.cols * x + y] & bottomMask)
            {
                for(int i=(y * f.cellSize + 10);i<=(y * f.cellSize +f.cellSize + 10);i++)
                {
                    pixels[((i + (x * f.cellSize +f.cellSize+10) * (width)) * 4 )+ 0]=f.borderColor.r;
                    pixels[((i + (x * f.cellSize +f.cellSize+ 10) * (width)) * 4 )+ 1]=f.borderColor.g;
                    pixels[((i + (x * f.cellSize+f.cellSize +10 ) * (width )) * 4 )+ 2]=f.borderColor.b;
                    pixels[((i + (x * f.cellSize+f.cellSize+10) * (width )) * 4 )+ 3]=255;
                }
            }
        }
             p=p-(initial/f.rows);
    }

    sf::Image image;
    image.create(f.cols*f.cellSize + 20,f.rows * f.cellSize + 20,pixels);
    image.saveToFile("finally.png");

    delete[] pixels;
}