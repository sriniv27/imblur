#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
/**
 * @brief Container to hold user-facing information of the image.
 *
 */
struct ImageData {
private:
  /** Internal store of the image matrix */
  Mat image_;
  /** File path of the input image */
  string filename_;

  /** File path of the output image */
  string outfilename_;
  int rows_;
  int cols_;

public:
  /**
   * @brief Return the size of the smoothing kernel matrix as a cv::Size using the kernels row and
   * column psecificia
   *
   * @return cv::Size
   */
  cv::Size kernelSize() { return cv::Size(this->rows_, this->cols_); }
  /**
   * @brief Provide the cv::Mat representation of the stored image.
   *
   * @return Mat
   */
  Mat image() { return this->image_; }

  /**
   * @brief Provide the filepath of the **source** of the stored image
   *
   * @return string
   */
  string filename() {
    auto fname = this->filename_;
    return fname;
  }

  /**
   * @brief Provide the file path of the **destination** of the stored image; the stored image will
   * be written to this path.
   *
   * @return string
   */
  string outfilename() {
    auto oFname = this->outfilename_;
    return oFname;
  }
  /** Number of rows of the smoothing kernel. */
  int rows() { return this->rows_; };
  /** Number of columns of the smoothing kernel */
  int cols() { return this->cols_; };

  /**
   * @brief Construct a new Image Data object
   *
   * @param filename_
   * @param outfilename_
   */
  ImageData(string _filename, string _outfilename) {

    this->filename_ = _filename;
    load_image();
    this->outfilename_ = _outfilename;
  };
  /**
   * @brief load the image from the stored filename.
   *
   * @return Mat
   */
  void load_image() {
    // TODO: imread flags could be turned into a user configuration later maybe.
    this->image_ = cv::imread(this->filename_, cv::ImreadModes::IMREAD_UNCHANGED);
  }
};