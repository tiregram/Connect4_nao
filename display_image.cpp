#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>


using namespace cv;


using namespace std;

int piece_color(Vec3b color)
{

  if(7   < color[0] && color[0] < 25  &&
     100 < color[1] && color[1] < 255 &&
     0   < color[2] && color[2] < 255)
    {
      return 1;
    }
  // inRange(imagecvt, Scalar(34,100,0), Scalar(75,255,255) ,imageG);
  if(34 < color[0] && color[0] < 75 &&
     100  < color[1] && color[1] < 255 &&
     0   < color[2] && color[2] < 255)
    {
      return 2;
    }

  return 3;
}

Point center(std::vector<Point> contour)
{
  unsigned long int val_x=0;
  unsigned long int val_y=0;
  for (auto point : contour) {
    val_x += point.x;
    val_y += point.y;
  }

  return Point(val_x/contour.size(),val_y/contour.size());
}

std::vector<Point>  centers(std::vector<std::vector<cv::Point> > contours) {

  std::vector<Point> list_center;

  for(auto contour : contours ){
    list_center.push_back(center(contour));
  }

  return list_center;

}


int main( int argc, char** argv )
{

  if( argc != 2)
    {
      cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
      return -1;
    }

  Mat image;
  Mat imageblur;
  Mat imagecvt;
  Mat imageR;
  Mat imageG;
  Mat imageB,imageBr;

  Mat imageGr;

  image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  if(! image.data )
    {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }

  // cvtColor(image,imageGr , cv::COLOR_BGR2GRAY);
  blur(image,imageblur,cv::Size(50,50));
  cvtColor(imageblur,imagecvt , cv::COLOR_BGR2HSV);
  cvtColor(imageblur,imageGr , cv::COLOR_BGR2GRAY);
  inRange(imagecvt, Scalar(7,100,0), Scalar(25,255,255) ,imageR);

  inRange(imagecvt, Scalar(34,100,0), Scalar(75,255,255) ,imageG);
  inRange(imagecvt, Scalar(100,50,0), Scalar(130,255,255) ,imageB);
  dilate(imageB, imageBr,Mat(),Point(-1,-1),10);

  //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
  std::vector<std::vector<Point> > contours;
  Mat contourOutput = imageBr.clone();
  findContours( contourOutput, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE );

  //Draw the contours
  cv::Scalar colors[3];
  colors[0] = cv::Scalar(255, 0, 0);
  colors[1] = cv::Scalar(0, 255, 0);
  colors[2] = cv::Scalar(0, 0, 255);
  Mat a(image.size(), CV_8UC3, cv::Scalar(0,0,0));

  // for (size_t idx = 0; idx < contours.size(); idx++) {
  //   cv::drawContours(a, contours, idx, colors[idx % 3]);
  // }

  std::vector<std::vector<Point> > contour2(contours.begin()++,
                              contours.end());

  std::vector<Point> list_center = centers(contour2);

  std::sort(list_center.begin(),
            list_center.end(),
            [](Point a,Point b)
            {
              return a.y * 10 + a.x < b.y *  10 + b.x;
            }
            );

  Point po = list_center[0];
  Point px = list_center[1];
  Point py = list_center[7];

  Vec<int,2> vx = px- po;
  Vec<int,2> vy = py- po;

  Matx<float,2,2> v(vx[0],vy[0],
                    vx[1],vy[1]);

  Matx<float,2,2> m = v.inv();

  cout << m << "\n";
  line(a,po,px,colors[0%3]);
  line(a,po,py,colors[1%3]);

  cout <<"vx"<<vx  << "\n";
  cout <<"vy"<< vy << "\n";

  Matx<int,7,6> mat;


  for(auto i : list_center ){

    Matx<int,2,1>  pi = (i-po);

    Matx<float,2,1> p(pi);

    Matx<int,2,1> aze = (m * p);

    int x = (int) round(aze(0,0));
    int y = (int) round(aze(1,0));

    Vec3b colora = imagecvt.at<Vec3b>(i);

    if(not( 0 <= x and x < 7 and
            0 <=y and  y < 6 ))
      {
        cout << "error size " <<x<<":"<<y<< "\n";
        continue;
      }

    mat(x,y) = piece_color(colora);

  }

  cout << mat.t()<<std::endl;

  // for (int i = 0; i < list_center.size(); i++) {
  //   line(a,list_center[i],list_center[i+1],colors[i%3]);
  // }

  // cv::drawContours(a, contours, top, colors[0 % 3]);
  // cv::drawContours(a, contours, top2, colors[1 % 3]);


  //  vector<Vec3f> circles;

  //  /// Apply the Hough Transform to find the circles
  //  for (int i = 50; i < 100; i= i+10) {
  //    for (int j = 50; j < 100; j= j+10) {
  //      HoughCircles( imageGr, circles, CV_HOUGH_GRADIENT, 1, 50 , i, j, 5, 500 );
  //      std::cout << circles.size() << "\n";
  //    }
  // }
  //  HoughCircles( imageR, circles, CV_HOUGH_GRADIENT, 1, 100, 200 , 18, 10, 300);

  // std::cout << circles.size() << "\n";
  // /// Draw the circles detected
  // for( size_t i = 0; i < circles.size(); i++ )
  //   {
  //     Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
  //     int radius = cvRound(circles[i][2]);
  //     // circle center
  //     circle( image, center, 3, Scalar(0,255,0), -1, 8, 0 );
  //     // circle outline
  //     circle( image, center, radius, Scalar(0,0,255), 3, 8, 0 );
  //   }

  namedWindow( "input", CV_WINDOW_NORMAL );
  namedWindow( "R", CV_WINDOW_NORMAL );
  namedWindow( "G", CV_WINDOW_NORMAL );
  // // namedWindow( "B", CV_WINDOW_NORMAL );

  // imshow( "input", image );
  // imshow( "input", a );
  // //  imshow( "R", imageR );

  imshow( "input", imageblur );
  imshow( "R", imageR );
  imshow( "G", imageG );

  // imshow( "R", image );

   while(waitKey(0)!=10);

  return 0;

}
