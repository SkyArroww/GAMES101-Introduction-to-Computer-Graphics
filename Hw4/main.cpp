#include <chrono>
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }
}

void naive_bezier(const std::vector<cv::Point2f>& points, cv::Mat& window) {
    auto& p_0 = points[0];
    auto& p_1 = points[1];
    auto& p_2 = points[2];
    auto& p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 + 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        // No Antialiasing
        // window.at<cv::Vec3b>(point.y, point.x)[2] = 255;

        // Antialiasing using the distance between the point and the nearest pixel
        float x = point.x;
        float y = point.y;
        float x1 = std::floor(x);
        float x2 = std::ceil(x);
        float y1 = std::floor(y);
        float y2 = std::ceil(y);
        float dist1 = std::sqrt(std::pow(x - x1, 2) + std::pow(y - y1, 2));
        float dist2 = std::sqrt(std::pow(x - x2, 2) + std::pow(y - y1, 2));
        float dist3 = std::sqrt(std::pow(x - x1, 2) + std::pow(y - y2, 2));
        float dist4 = std::sqrt(std::pow(x - x2, 2) + std::pow(y - y2, 2));

        window.at<cv::Vec3b>(y1, x1)[1] += 255 * (1 - dist1);
        window.at<cv::Vec3b>(y1, x2)[1] += 255 * (1 - dist2);
        window.at<cv::Vec3b>(y2, x1)[1] += 255 * (1 - dist3);
        window.at<cv::Vec3b>(y2, x2)[1] += 255 * (1 - dist4);
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f>& control_points, float t) {
    // TODO: Implement de Casteljau's algorithm
    std::vector<cv::Point2f> points = control_points;
    if (points.size() == 1)
        return points[0];
    else {
        std::vector<cv::Point2f> new_points;
        for (int i = 0; i < points.size() - 1; i++) {
            cv::Point2f point = (1 - t) * points[i] + t * points[i + 1];
            new_points.push_back(point);
        }
        return recursive_bezier(new_points, t);
    }
}

void bezier(const std::vector<cv::Point2f>& control_points, cv::Mat& window) {
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's
    // recursive Bezier algorithm.
    float t = 0.0;
    for (; t <= 1.0; t += 0.0001) {
        auto p = recursive_bezier(control_points, t);

        // No Antialiasing
        // window.at<cv::Vec3b>(p.y, p.x)[1] = 255;

        // Antialiasing using the distance between the point and the nearest pixel
        cv::Point2i p0(
            p.x - std::floor(p.x) < 0.5 ? std::floor(p.x) : std::ceil(p.x),
            p.y - std::floor(p.y) < 0.5 ? std::floor(p.y) : std::ceil(p.y)
        );
        std::vector<cv::Point2i> points = {
            p0,
            cv::Point2i(p0.x - 1, p0.y),
            cv::Point2i(p0.x, p0.y - 1),
            cv::Point2i(p0.x - 1, p0.y - 1),
        };
        float maxdis = std::sqrt(2.);
        std::vector<float> dists;
        for (int i = 0; i < 4; i++) {
            float dis = std::sqrt(std::pow(p.x - .5 - points[i].x, 2) + std::pow(p.y - .5 - points[i].y, 2));
            dists.push_back(dis);
        }
        //using sigmoid
        float sumexpdis = exp(dists[0]) + exp(dists[1]) + exp(dists[2]) + exp(dists[3]);
        float sumdis = dists[0] + dists[1] + dists[2] + dists[3];
        for (int i = 0; i < 4; i++) {
            // float w = dists[i] / sumexpdis;
            // window.at<cv::Vec3b>(points[i].y, points[i].x)[1] = std::min(255.f, window.at<cv::Vec3b>(points[i].y, points[i].x)[1] + 255.f * w);

            // using sigmoid
            float w_exp = exp(dists[i]) / sumexpdis;
            window.at<cv::Vec3b>(points[i].y, points[i].x)[1] = std::min(255.f, window.at<cv::Vec3b>(points[i].y, points[i].x)[1] + 255.f * w_exp);
        }
    }
}

int main() {
    cv::Mat window = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) {
        for (auto& point: control_points) {
            cv::circle(window, point, 3, { 255, 255, 255 }, 3);
        }

        if (control_points.size() == 4) {
            // naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

    return 0;
}
