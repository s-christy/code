//g++ base.cpp `pkg-config --cflags --libs opencv`;./a.out;rm a.out

#include <stdio.h>
#include <cv.h>
#include <highgui.h>

typedef IplImage* (*callback_prototype)(IplImage*);

IplImage* make_it_gray(IplImage* frame){

    // Allocate space for a new image
    IplImage* gray_frame = cvCreateImage(cvSize(frame->width, frame->height), frame->depth, 1);

    cvCvtColor(frame, gray_frame, CV_RGB2GRAY);
    return gray_frame;
}

/*
 * process_video: retrieves frames from camera and executes a callback to do
 * individual frame processing. Keep in mind that if your callback takes too
 * much time to execute, you might lose a few frames from the camera.
 */
void process_video(){

    // Initialize camera
    CvCapture *capture = 0;
    capture = cvCaptureFromCAM(-1);

    // Create a window for the video
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);

    IplImage* frame = 0;
    char key = 0;
    while (key != 'q'){
      frame = cvQueryFrame(capture);

      // Execute callback on each frame
      IplImage* processed_frame = (*make_it_gray)(frame);

      // Display processed frame
      cvShowImage("result", processed_frame);

      // Release resources
      cvReleaseImage(&processed_frame);

      // Exit when user presses 'q'
      key = cvWaitKey(10);
    }

    // Free memory
    cvDestroyWindow("result");
    cvReleaseCapture(&capture);
}

int main( int argc, char **argv ){
    process_video();
}
