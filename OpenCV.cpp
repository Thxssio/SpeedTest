#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

int main() {
    cv::VideoCapture cap(0);
    cv::QRCodeDetector qrDecoder;

    if (!cap.isOpened()) {
        std::cout << "Erro para abrir o video." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (1) {
        cap >> frame;

        if (frame.empty())
            break;

        // Convertendo a imagem para escala de cinza
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Equalizando o histograma
        cv::Mat img_hist_equalized;
        cv::equalizeHist(gray, img_hist_equalized);

        std::vector<cv::Point> points;
        std::string data = qrDecoder.detectAndDecode(img_hist_equalized, points);

        if (!data.empty()) {
            std::cout << "Decoded Data: " << data << std::endl;
            for (size_t i = 0; i < points.size(); i++) {
                cv::line(frame, points[i], points[(i + 1) % points.size()], cv::Scalar(255, 0, 0), 2);
            }

            // Criando uma máscara para a área do QR Code
            cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8UC1);
            cv::fillConvexPoly(mask, points, cv::Scalar(255, 255, 255), cv::LINE_AA, 0);

            // Criando a imagem cortada
            cv::Mat croppedImage;
            frame.copyTo(croppedImage, mask);

            // Mostrando a imagem cortada em uma janela separada
            cv::imshow("Cropped", croppedImage);
        }

        cv::imshow("Frame", frame);

        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
