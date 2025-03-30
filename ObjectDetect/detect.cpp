/* --- --- --- --- --- --- --- --- ---

THREE FRAMES DIFFERENCE MOTION DETECTION

PROS:
- Objects are more likely to move consistently from frame to frame while
  noises are usually only appear between two frames. With `bitwise_or` of 
  two frame differences, objects' responses are enhanced while noises' 
  responses remain.

CONS:
- The background must remains static. It only works for static cameral.

- Easily disturbed by noise(like tree leaves moving) and background 
  changes(like sudden brightness changes).

THIS FILE USES TWO FRAMES DIFFERENCE.


--- --- --- --- --- --- --- --- --- */

#include "detect.hpp"
#include <opencv2/opencv.hpp>
#include "funcs.hpp"


bool fdObject::isSameObject(const Rect& bbox){

    Rect newest = _rects.back();
    double iou = func::IoU(newest,bbox);

    cout << "DEBUG: fdObject::isSameObject - IOU: "<< iou <<endl;

    return (iou > _min_iou_req);
}

bool fdObject::addFrame(const Rect& bbox){

    _rects.push_back(bbox);
    return true;
}

bool fdObject::getResult(void){

    /* Detection failed. */
    if (_rects.size() < MIN_DETEC_FRM_REQ){
        return false;
    }

    /* Merge rects. */
    Rect merged = _rects[0];
    for (int i = 1; i < _rects.size(); ++i) {
        merged |= _rects[i];
    }

    // _result = merged;
    _result = _rects.back();
    

    return true;

}

Rect fdObject::resultRect(void){

    return _result;
}



bool objDetect::tick(const Mat& frame){

    int round = _clock % _period;

    cout << "DEBUG: objDetect::tick - round: "<< round <<endl;


    if(_clock < _clock_bound){
        _clock ++ ;
    }
    else {
        _clock = 0;
    }

    /* Use frame.clone() to Deep Copy. Otherwise it would be Shallow Copy. */

    cv::cvtColor(frame, _p_frms[round], cv::COLOR_BGR2GRAY);

    if(round == _frm_bound){
        
        Mat resp = objDetect::FramesDiff(_p_frms[round], _p_frms[round-1]);
        vector<Rect> obj_rects = objDetect::getRects(resp);

        // cout << "DEBUG: objDetect::tick - obj_rects.size(): "<< obj_rects.size() <<endl;
        
        for(const Rect& obj_rect: obj_rects){

            _objs.push_back(fdObject(obj_rect));
        }
    }
    else if(round > _frm_bound){

        Mat resp = objDetect::FramesDiff(_p_frms[round], _p_frms[round-1]);
        vector<Rect> obj_rects = objDetect::getRects(resp);

        for(const Rect& obj_rect: obj_rects){

            for(fdObject& obj: _objs){

                if(obj.isSameObject(obj_rect)){
                    obj.addFrame(obj_rect);
                    break;
                }
            }
        }
    }

    if(round == _period -1 ){

        if(_objs.size() != 0){

            int i_write = 0;
            for(int i_read = 0; i_read < _objs.size(); ++ i_read){

                if(_objs[i_read].getResult()){
                    _objs[i_write] = _objs[i_read];
                    ++ i_write;
                }
            }
            _objs.resize(i_write);

            this -> backgrndUpdate(_p_frms[round]);

            if(_objs.size() != 0){
                _res = std::move(_objs);
                return true;
            }
        }
    }

    return false;
}

bool objDetect::backgrndUpdate(const Mat& frame){

    double alpha = 0.1;

    Mat mask = Mat(frame.size(), CV_8UC1, cv::Scalar(255));

    for(fdObject& obj:_objs){

        cv::rectangle(mask, obj.resultRect(), cv::Scalar(0), cv::FILLED);
    }

    imshow("mask", mask);
    
    /* Can be accelerated by CPU Branch Prediction. */
    if(_backgrnd_initialized == false){
        
        _backgrnd_init_counter --;
        if(_backgrnd_init_counter == 0){

            _backgrnd_initialized = true;
        }

        alpha = 0.5;

        if(_backgrnd.empty()){

            _backgrnd = Mat(frame.size(), CV_32FC1, cv::Scalar(0));
        }

    }

    Mat frame_f;
    frame.convertTo(frame_f, CV_32FC1);
    Mat new_backgrnd = (1.0 - alpha) * _backgrnd + alpha * frame_f;
    new_backgrnd.copyTo(_backgrnd, mask);

    Mat tmp;
    _backgrnd.convertTo(tmp, CV_8UC1);
    imshow("Bakcgrnd", tmp);

    return true;

}


vector<fdObject> objDetect::getObjects(void){

    return _res;
}


/* --- --- --- --- --- --- --- --- ---

FUNC NAME: FramesDiff

# Description
Calculate the response of 2 or 3 frames difference.

# Arguments
@ cur_fra:  Current frame, frame `t`.
@ pre_fra:  Previous frame, frame `t-1`.
@ pp_fra:   Frame `t-2`. It's empty for 2 frames difference.

# Returns
@ res:      Response of frames differences.

--- --- --- --- --- --- --- --- --- */

Mat objDetect::FramesDiff(Mat cur_fra, Mat pre_fra, Mat pp_fra){

    Mat cur_b, pre_b;
    // cv::cvtColor(cur_fra, cur_g, cv::COLOR_BGR2GRAY);
    // cv::cvtColor(pre_fra, pre_g, cv::COLOR_BGR2GRAY);

    cv::medianBlur(cur_fra,cur_b, 5);
    cv::medianBlur(pre_fra,pre_b, 5);

    Mat cur_pre_d;
    cv::absdiff(cur_b, pre_b, cur_pre_d);

    Mat resp;

    /* 2 Frames Difference. */
    if(_frm_bound == 1){

        cv::threshold(cur_pre_d, resp,FD_THRESHOLD, 255, cv::THRESH_BINARY);
    }
    /* 3 Frames Difference. */
    else{

        Mat pre_pp_d;
        cv::absdiff(pre_fra, pp_fra, pre_pp_d);

        Mat dd;
        cv::bitwise_or(cur_pre_d, pre_pp_d, dd);

        cv::threshold(dd, resp,FD_THRESHOLD, 255, cv::THRESH_BINARY);
    }

    if(_backgrnd_initialized){

        Mat res;

        Mat backgrnd_i;
        _backgrnd.convertTo(backgrnd_i, CV_8UC1);

        Mat backgrnd_diff;
        cv::absdiff(cur_fra, backgrnd_i, backgrnd_diff);
        cv::threshold(backgrnd_diff, backgrnd_diff,BAKCGRND_THRESHOLD, 255, cv::THRESH_BINARY);

        cv::bitwise_and(resp, backgrnd_diff, res);

        return res;
    }

    // cv::imshow("Resp", res);


    // Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(7,7));

    // cv::morphologyEx(res, res,cv::MORPH_CLOSE,kernel);

    // kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(7,7));

    // cv::morphologyEx(res, res,cv::MORPH_DILATE,kernel);
    

    return resp;
}


/* --- --- --- --- --- --- --- --- ---

FUNC NAME: getRects

# Description
Process frames difference's response and return Rects of detected objects.

# Arguments
@ resp:     Response of frames difference.

# Returns
@ objects:  Vector of Rects(bounding boxes) of detected objects.

--- --- --- --- --- --- --- --- --- */

vector<Rect> objDetect::getRects(Mat resp) {

    vector<Rect> objects;
    vector<vector<cv::Point2i>> contours;

    // Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    // cv::morphologyEx(resp, resp,cv::MORPH_CLOSE,kernel);

    // cv::imshow("CLOSE Resp", resp);
    
    cv:: findContours(resp, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const vector<cv::Point2i>& contour : contours) {

        Rect bbox = cv::boundingRect(contour);
        
        if (bbox.area() > MIN_BBOX_SIZE) { 
            objects.push_back(bbox);
        }
    }

    return objects;
}