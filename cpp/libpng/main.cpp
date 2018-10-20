//for i in {0..100}; do echo; done;g++ -Wall -lm -lpng png.cpp ;./a.out resources/lion.png last.png;feh last.png ;rm a.out #last.png
//for i in {0..100}; do echo; done;g++ -Wall -lm -lpng png.cpp ;./a.out resources/text.png last.png;feh last.png ;rm a.out #last.png
//for i in {0..100}; do echo; done;g++ -Wall -lm -lpng png.cpp ;./a.out resources/Cats\ Eye.png last.png;feh last.png ;rm a.out #last.png
//for i in {0..100}; do echo; done;g++ -Wall -lm -lpng png.cpp ;./a.out resources/the\ office.png last.png;feh last.png ;rm a.out #last.png

//TODO
//Experiment with video by slicing video into frames, processing each frame, and recompiling
//sort by lumosity instead of channel
//rotate hue
//modulate colors by lumosity
//do a fourier transform, at least a 1-d
//experiment with actual 3x3 filters. Actually create a filter object that holds the filter and the width/height stuff as well
//finish the filter class
//random vector field
//turn everything to vectors

#include <algorithm>
#include <iostream>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//holds an array of pixels and provides methods to manipulate that array
class PixelBuffer{
private:

	//holds pixel information
	class Pixel{
	public:
		int r,g,b,a;
		Pixel(){
			this->r=0;
			this->g=0;
			this->b=0;
			this->a=0;
		}
		Pixel(int r,int g,int b,int a){
			this->r=r;
			this->g=g;
			this->b=b;
			this->a=a;
		}
		int luminance(){
			return 0.2126*r+0.7152*g+0.0722*b;
		}
	};

	//
	class Filter{
	float f[3][3];
	public:
		Filter(){
			//make a highpass filter
			float t[3][3]={
				{0,-1,0},
				{-1,4,-1},
				{0,-1,0}
			};
		}
		void apply(){
		}
	};

	//Actual pixel buffer
	Pixel *pixels;
	Pixel *backBuffer;

	//set the color of pixel[x][y] to (r,g,b). Negative numbers make the channel transparent
	void setPixel(int x, int y, Pixel p){
		if(p.r>=0)pixels[width*y+x].r=p.r;
		if(p.g>=0)pixels[width*y+x].g=p.g;
		if(p.b>=0)pixels[width*y+x].b=p.b;
	}

public:
	int width;
	int height;

	//constructors: passing width and height creates an all black buffer.
	PixelBuffer(){
	}
	PixelBuffer(int width, int height){
		this->width=width;
		this->height=height;
		pixels=new Pixel[width*height];
		backBuffer=new Pixel[width*height];
	}

	//return pixel information
	Pixel getPixel(int x, int y){
		return pixels[width*y+x];
	}

	//draw a rectangle to the buffer
	void drawRect(int x1,int y1,int width,int height,int r, int g, int b){
		for(int x=x1;x<x1+width;x++){
			for(int y=y1;y<y1+height;y++){
				setPixel(x,y,Pixel(r,g,b,0));
			}
		}
	}

	//randomize one of the color channels
	void fuzz(){
		for(int y=0;y<height;y++){
			for(int x=0;x<width;x++){
				setPixel(x,y,Pixel(-1,-1,rand(),0));
			}
		}
	}

	//apply a gradient to the image
	void gradient(){
		for(int y=0;y<height;y++){
			for(int x=0;x<width;x++){
				setPixel(x,y,Pixel(x+y,-1,-1,0));
			}
		}
	}

	//insertion sort for pixel objects
	void sort(int rownum){
		for(int i=0;i<width;i++){
			for(int j=i;j<width;j++){
				if(pixels[width*rownum+i].g<pixels[width*rownum+j].g){
					Pixel t=pixels[width*rownum+i];
					pixels[width*rownum+i]=pixels[width*rownum+j];
					pixels[width*rownum+j]=t;
				}
			}
		}
	}

	//move the red channel by a number of pixels
	void aberration(int n){
		for(int i=0;i<height*width;i++){
			pixels[i].r=pixels[i+n].r;
		}
	}

	//rotate channels
	void rotateChannels(){
		for(int i=0;i<width*height;i++){
			Pixel t=pixels[i];
			pixels[i]=Pixel(t.b,t.r,t.g,t.a);
		}
	}

	//blur
	void blur(int n){
		for(int i=0;i<width*height;i++){
			Pixel t=Pixel(0,0,0,0);
			for(int j=0;j<n;j++){
				t.r+=pixels[i+j].r;
				t.g+=pixels[i+j].g;
				t.b+=pixels[i+j].b;
			}
			pixels[i].r=t.r/n;
			pixels[i].g=t.g/n;
			pixels[i].b=t.b/n;
		}
	}

	//first broken filter
	void broken1(){
		for(int i=0;i<width*height;i++){
			pixels[i].r-=pixels[i+1].r;
		}
	}

	//second broken filter
	void broken2(){
		for(int i=0;i<width*height;i++){
			pixels[i].r=abs(pixels[i].r-pixels[i+1].r);
			pixels[i].g=0;
			pixels[i].b/=2;
		}
	}

	//
	void broken3(){
		for(int i=0;i<width*height;i++){
			pixels[i].r=pixels[i].r*2%255;
			pixels[i].g=pixels[i].g*2%255;
			pixels[i].b=pixels[i].b*2%255;
		}
	}

	//sobel-like filter
	void sobelLike(){
		for(int i=0;i<width*height;i++){
			pixels[i].r=abs(pixels[i].r-pixels[i+1].r);
			pixels[i].g=abs(pixels[i].g-pixels[i+1].g);
			pixels[i].b=abs(pixels[i].b-pixels[i+1].b);
		}
	}

	//modulate brightness
	void modulateBrightness(){
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				int n=10;
				pixels[i*width+j].r=pixels[i*width+j].r*((i*n)%255)/255;
				pixels[i*width+j].g=pixels[i*width+j].g*((i*n)%255)/255;
				pixels[i*width+j].b=pixels[i*width+j].b*((i*n)%255)/255;
			}
		}
	}

	//simple test of most of these functions
	void featureTest(){
		fuzz();
		gradient();
		drawRect(300,400,10,10,0,0,255);
		drawRect(100,100,100,10,0,0,255);
		drawRect(100,200,150,150,-1,-1,255);
		for(int i=0;i<height/2;i++)sort(height/2+i);
		aberration(30);
		rotateChannels();
		blur(100);
		broken1();
		broken2();
		sobelLike();
		modulateBrightness();
		broken3();
	}

	//write pixel buffer to file
	void writeImage(char* filename){

		//initialization
		FILE *fp=fopen(filename,"wb");
		png_structp png_ptr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
		png_infop info_ptr=png_create_info_struct(png_ptr);
		png_init_io(png_ptr,fp);
		png_set_IHDR(png_ptr,info_ptr,width,height,8,PNG_COLOR_TYPE_RGB,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
		png_write_info(png_ptr,info_ptr);

		//write rows to file
		png_bytep row=new png_byte[3*width];
		for(int y=0;y<height;y++){
			for(int x=0;x<width;x++){
				row[x*3+0]=getPixel(x,y).r;
				row[x*3+1]=getPixel(x,y).g;
				row[x*3+2]=getPixel(x,y).b;
			}
			png_write_row(png_ptr,row);
		}

		//free memory
		free(row);
		png_write_end(png_ptr,NULL);
		fclose(fp);
	}

	void read_png_file(char *filename) {
		FILE *fp=fopen(filename,"rb");
		png_structp png=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
		png_infop info=png_create_info_struct(png);
		png_init_io(png,fp);
		png_read_info(png,info);

		width=png_get_image_width(png,info);
		height=png_get_image_height(png,info);
		pixels=new Pixel[width*height];
		backBuffer=new Pixel[width*height];
		png_byte color_type=png_get_color_type(png,info);
		png_byte bit_depth	=png_get_bit_depth(png,info);

		if(bit_depth==16)
			png_set_strip_16(png);

		if(color_type==PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png);

		if(color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)
			png_set_expand_gray_1_2_4_to_8(png);

		if(png_get_valid(png,info,PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png);

		if(color_type==PNG_COLOR_TYPE_RGB||color_type==PNG_COLOR_TYPE_GRAY||color_type==PNG_COLOR_TYPE_PALETTE)
			png_set_filler(png,0xFF,PNG_FILLER_AFTER);

		if(color_type==PNG_COLOR_TYPE_GRAY||color_type==PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png);

		png_read_update_info(png,info);

		png_bytep *row_pointers=new png_bytep[height]();
		for(int y=0;y<height;y++){
			row_pointers[y]=(png_byte*)malloc(png_get_rowbytes(png,info));
		}

		png_read_image(png,row_pointers);

		fclose(fp);
		for(int y=0;y<height;y++){
			for(int x=0;x<width;x++){
				setPixel(x,y,Pixel(
					row_pointers[y][x*4+0],
					row_pointers[y][x*4+1],
					row_pointers[y][x*4+2],
					0
				));
			}
		}
	}
};

//entry-point
int main(int argc,char *argv[]){

	//create an empty PixelBuffer object
	PixelBuffer* p=new PixelBuffer;

	//fill the PixelBuffer with the contents of an input file
	p->read_png_file(argv[1]);

	//apply transformations
	p->featureTest();

	//write image out
	p->writeImage(argv[2]);
}

