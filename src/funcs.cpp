#include "funcs.hpp"


int tcr_count = 0;
array<Tracking,MAX_TCR> tcrs;

bool func::tcrs_init(array<Tracking,MAX_TCR>& tcrs){

    for(int i = 0; i < MAX_TCR; ++ i){
        tcrs[i] = Tracking(i);
    }
    return true;
}

bool Tracking::update(Mat& frame){
    Rect bbox;
    bbox = kcf_p -> update(frame);

    char title[6];
    snprintf(title, sizeof(title), "id:%02d", id);

    cv::putText(frame, title, cv::Point(bbox.x,bbox.y-1),cv::FONT_HERSHEY_SIMPLEX,
                         0.5, cv::Scalar(0,0,255), 1, cv::LINE_AA);
    cv::rectangle(frame,bbox, cv::Scalar(0,0,255));

    return true;
}


bool Tracking::init(Mat first_f, Rect roi, bool hog, bool fixed_window,
                         bool multiscale, bool lab){

    
    state = TCR_RUNN;
    kcf_p = std::make_unique<KCFTracker>(hog, fixed_window, multiscale, lab);
    kcf_p -> init(roi,first_f);

    return true;
}

/* --- --- --- --- --- --- --- --- ---

FUNC NAME: IoU

# Description
Calculate IoU of two Rects.

# Arguments
@ bbox_a:   First bounding box;
@ bbox_b:   Second bounding box;

# Returns
@ iou:      Intersection over union, 0.0 ~ 1.0;

--- --- --- --- --- --- --- --- --- */
double func::IoU(const Rect& bbox_a, const Rect& bbox_b){

    int inter_area = ( bbox_a & bbox_b).area();

    double iou = 1.0 * inter_area / (bbox_a.area() + bbox_b.area() - inter_area);
    
    return iou;
}





