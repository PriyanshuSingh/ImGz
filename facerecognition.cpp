#include "facerecognition.h"
#include <QComboBox>
/*
using namespace std;
FaceRecognition::FaceRecognition()
{
    bool validCsv = read_csv("<fileName>",images,labels);     //enter csv file path
    haar_cascade.load("<pathToHaarCascade>");       //enter haarCascase Path(Frontal face)
    faceRecAlgoComboBox = new QComboBox;
    faceRecAlgoComboBox->addItem("Fisher faces");
    faceRecAlgoComboBox->addItem("LBPH");
    faceRecAlgoComboBox->addItem("Eigen faces");
    faceRecAlgoComboBox->setCurrentIndex(1);
    faceRecAlgoComboBox->setCurrentText("LBPH");

    gammaSlider = new QSlider(Qt::Horizontal);
    gammaSlider->setFocusPolicy(Qt::StrongFocus);
    gammaSlider->setSingleStep(1);
    gammaSlider->setRange(1,40); //To be divided by 10 when passed to the gammaCorrect function
    gammaSlider->setTickPosition(QSlider::NoTicks);
    connect(gammaSlider,SIGNAL(valueChanged(int)),this,SLOT(updateGamma(int)));

    histEqCheckBox = new QCheckBox;
    histEqCheckBox->setText("Histogram Equalization");
    connect(histEqCheckBox,SIGNAL(clicked(bool)),this,SLOT(updateHistEqStatus(bool)));

    sharpnessCheckBox = new QCheckBox;
    sharpnessCheckBox->setText("Sharpness");
    connect(sharpnessCheckBox,SIGNAL(clicked(bool)),SLOT(updateSharpnessStatus(bool)));

    connect(faceRecAlgoComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateFaceRecAlgo(int)));
    connect(this,SIGNAL(imageChanged()),this,SLOT(handleImageChanged()));
}

static int FaceRecognition ::read_csv(const string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
        return 0;
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
    return 1;
}

void FaceRecognition::updateSharpnessStatus(bool status){
    sharpnessStatus = status;
    somethingChanged();
}

void FaceRecognition::updateHistEqStatus(bool x){
    histEqStatus = x;
    somethingChanged();
}

cv::Mat FaceRecognition::correctSharpness(cv::Mat& img){
    cv::Mat temp;
    cv::GaussianBlur(img, temp, cv::Size(0, 0), 3);
    cv::addWeighted(img,1.7,temp,-0.7,0,img);
    return img;
}


cv::Mat FaceRecognition::correctGamma( cv::Mat& img, double gamma ) {
    double inverse_gamma = 1.0 / gamma;

    cv::Mat lut_matrix(1, 256, CV_8UC1 );
    uchar * ptr = lut_matrix.ptr();
    for( int i = 0; i < 256; i++ )
       ptr[i] = (int)( pow( (double) i / 255.0, inverse_gamma ) * 255.0 );

    cv::Mat result;
    cv::LUT( img, lut_matrix, result );

    return result;
}

cv::Mat FaceRecognition::applyHistEq(cv::Mat& img){
    cv::equalizeHist( img, img );
    return img;
}

void FaceRecognition::applyFilter(){
    if(isChanged()){
        vector< cv::Rect_<int> > faces;
        if(!haar_cascade.empty()){
            haar_cascade.detectMultiScale(grayImgMat, faces);

            originalImg.copyTo(processedImg);

            for(int i = 0; i < faces.size(); i++) {
                // Process face by face:
                cv::Rect face_i = faces[i];
                // Crop the face from the image. So simple with OpenCV C++:
                cv::Mat face = grayImgMat(face_i);
                // Resizing the face is necessary for Eigenfaces and Fisherfaces. You can easily
                // verify this, by reading through the face recognition tutorial coming with OpenCV.
                // Resizing IS NOT NEEDED for Local Binary Patterns Histograms, so preparing the
                // input data really depends on the algorithm used.
                //
                // I strongly encourage you to play around with the algorithms. See which work best
                // in your scenario, LBPH should always be a contender for robust face recognition.
                //
                // Since I am showing the Fisherfaces algorithm here, I also show how to resize the
                // face you have just found:
                cv::Mat face_resized;
                cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, cv::INTER_CUBIC);
                //Applying Sharpness
                if(sharpnessStatus)
                    face_resized = correctSharpness(face_resized);
                //Appying histogram equalization
                if(histEqStatus)
                    face_resized = applyHistEq(face_resized);
                //Applying gamma correction
                face_resized = correctGamma(face_resized,gamma);


                // Now perform the prediction, see how easy that is:
                int prediction = currentAlgo->predict(face_resized);
                // And finally write all we've found out to the original image!
                // First of all draw a green rectangle around the detected face:
                cv::rectangle(processedImg, face_i, CV_RGB(0, 255,0), 1);
                // Create the text we will annotate the box with:
                string box_text = format("Prediction = %d", prediction);
                // Calculate the position for annotated text (make sure we don't
                // put illegal values in there):
                int pos_x = std::max(face_i.tl().x - 10, 0);
                int pos_y = std::max(face_i.tl().y - 10, 0);
                // And now put it into the image:
                putText(processedImg, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
            }
        }
        setChanged(false);
    }
}

void FaceRecognition::updateFaceRecAlgo(int i){
    switch (i) {
    case 0:
        currentAlgo = face::createFisherFaceRecognizer();
        break;
    case 1:
        currentAlgo = face::createLBPHFaceRecognizer();
    case 2:
        currentAlgo = face::createEigenFaceRecognizer();
    default:
        break;
    }
    currentAlgo->train(images,labels);
    somethingChanged();
}

void FaceRecognition::handleImageChanged()
{
    cv::cvtColor(originalImg,grayImgMat,CV_BGR2GRAY);
    somethingChanged();
}

void FaceRecognition::updateGamma(int i){
    gamma=i/10;
}

void FaceDetector::somethingChanged()
{
    setChanged(true);
}


bool FaceRecognition::isChanged() const
{
    return changed;
}

void FaceRecognition::setChanged(bool value)
{
    changed = value;
}

cv::Mat FaceRecognition::getImage(){
    return processedImg;
}

void FaceRecognition::createPropertyWidget()
{
    propertyWidget = new QWidget();
    QVBoxLayout *boxLayout = new QVBoxLayout();
    QFormLayout *fLayout = new QFormLayout();
    fLayout->addWidget(faceRecAlgoComboBox);
    fLayout->addWidget(gammaSlider);
    fLayout->addWidget(histEqCheckBox);
    fLayout->addWidget(sharpnessCheckBox);
    boxLayout->addLayout(fLayout);
    propertyWidget->setLayout(boxLayout);
}


void FaceDetector::mouseReleased(QMouseEvent *ev)
{

}

void FaceDetector::mousePressed(QMouseEvent *ev)
{

}

void FaceDetector::mouseMoved(QMouseEvent *ev)
{

}

*/
