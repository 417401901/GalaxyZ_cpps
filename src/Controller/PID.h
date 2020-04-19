//
// Created by wangx on 2020/3/3 0003.
//

#ifndef GALAXYZ_CPP_PID_H
#define GALAXYZ_CPP_PID_H


class PID {
public:
    PID(const float kp, const float ki, const float kd, const float ilimit, const float outlimit) :
            Kp(kp), Ki(ki), Kd(kd), ILimit(ilimit), OutLimit(outlimit) {}

    ~PID();

    void setValue(float set, float real);

    float getResult();

private:
    const float Kp;
    const float Ki;
    const float Kd;
    const float ILimit;
    const float OutLimit;

    float CmdOut = 0;
    float SetValue = 0;
    float RealValue = 0;

    float Err = 0;
    float Errlast = 0;
    float Intergral = 0;
};


#endif //GALAXYZ_CPP_PID_H
