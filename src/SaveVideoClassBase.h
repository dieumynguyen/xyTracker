#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/video.hpp"

#include <iostream>
#include <string>   // for strings
#include <sstream>
#include <fstream>   
#include <iomanip>


using namespace std;


/**
 * SaveVideo Class.  Saves and displays a video captured from a camaera.
 */ 
class VideoSaver  
{
public:
  /** Constructor. */
  VideoSaver();

  /** Destructor. */
  virtual ~VideoSaver();

  /**
   * Captures and writes the video to the file
   */ 
  int startCaptureAndWrite(const string fname, string codec);

  /**
   * Captures without writing to video file
   */ 
  virtual int startCapture();

  /**
   * makes the current frame available in "Frame"
   */ 
  int getFrame(cv::Mat * pFrame ,double * pTimeStamp, int *pFrameNumber);
  /**
   * returns the current framecounter
   */ 
  int getCurrentFrameNumber();
    
  int close();

  virtual int init(int camIdx);

  /**
   * returns frame size 
   */
  cv::Size getFrameSize();

  /**
   * returns the theoretical FPS set (usually set by the camera)
   */
  double getFPS();

  /**
   * Asks whether writing is finished
   */ 
  bool isFinished();


  /**
   * Whether init was done  (capture device avaibable)
   */ 

  virtual bool isInit();

  bool isCapturing();
  
  bool isRGB() {return m_isRGB;};
  
  int getLostFrameNumber();

	
private:
  
  int stopWriting();

  cv::VideoCapture m_Capture;

  std::fstream m_OutputFile;
  cv::VideoWriter m_Video;

  bool m_writing;
  int m_writingFrameNumber;
  
protected:
  
  virtual void captureThread();
  virtual int stopCamera();
	
  void captureAndWriteThread();
  void waitForNewFrame();

  
  std::clock_t m_timer;  
  cv::Mat m_Frame;
  double m_TimeStamp;
  int m_frameNumber;

  
  float m_FrameRateToUse;
  cv::Size m_FrameSize;

  
  bool m_newFrameAvailable;
  bool m_KeepThreadAlive;
  bool m_KeepWritingAlive;
  bool m_WritingFinished;
  bool m_GrabbingFinished;

  bool m_capturing;
  bool m_isRGB;
    
  std::mutex m_FrameMutex;
  std::condition_variable m_newFrameAvailableCond;
  std::thread * m_captureThread;
  std::thread * m_writingThread;
	
};
