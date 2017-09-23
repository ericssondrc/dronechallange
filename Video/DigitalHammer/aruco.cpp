#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <cstring>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {

    //cv::VideoCapture camera;
    //int device_counts = 0;
    //while (camera.open(device_counts++)) {
    //    cout << device_counts - 1 << endl;
    //}
    //camera.release();
    //std::cout << "devices count : " << device_counts - 1 << std::endl;



    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::Mat markerImage;
    cv::aruco::drawMarker(dictionary, 23, 200, markerImage, 1);
    cv::Mat cameraMatrix, distCoeffs;
    FileStorage fs2("cameraParameters.xml", FileStorage::READ);
    fs2["cameraMatrix"] >> cameraMatrix;
    fs2["distCoeffs"] >> distCoeffs;
    fs2.release();
    while (inputVideo.grab()) {
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        // if at least one marker detected
        if (ids.size() > 0)
        {
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);

            cout << rvecs[0] << endl;
            cout << tvecs[0] << endl;
            cout << endl;

            // draw axis for each marker
            for (int i = 0; i<ids.size(); i++)
                cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
        }


        cv::imshow("out", imageCopy);
        char key = (char)cv::waitKey(10);
        if (key == 27)
            break;
    }
}