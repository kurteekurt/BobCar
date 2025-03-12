#include <iostream>
#include <opencv2/core.hpp>      // For cv::Mat
#include <opencv2/imgcodecs.hpp> // For cv::imread, cv::imwrite
#include <opencv2/imgproc.hpp>   // For cv::cvtColor

// Define the process_image function
extern "C" void processImage(const char *input_image_path,
                             const char *output_image_path) {
  // Load the image using OpenCV C++ functions
  cv::Mat image = cv::imread(input_image_path, cv::IMREAD_COLOR);
  if (image.empty()) {
    std::cerr << "Could not open or find the image." << std::endl;
    return;
  }

  // Process the image (convert to grayscale for demonstration)
  cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

  // Save the processed image
  cv::imwrite(output_image_path, image);
  std::cout << "Processed image saved to: " << output_image_path << std::endl;
}