//
// Created by wangx on 2020/3/3 0003.
//

#include "PID.h"

void PID::setValue(float set, float real) {
    this->SetValue = set;
    this->RealValue = real;
}

float PID::getResult() {
    this->Err = this->SetValue - this->RealValue;
    this->Intergral += this->Err;

    this->Intergral = this->Intergral > this->ILimit ? this->ILimit : this->Intergral;
    this->Intergral = this->Intergral < -this->ILimit ? -this->ILimit : this->Intergral;

    this->CmdOut = this->Kp * this->Err +
                   this->Ki * this->Intergral +
                   this->Kd * (this->Err - this->Errlast);

    this->Errlast = this->Err;

    this->CmdOut = this->CmdOut > this->OutLimit ? this->OutLimit : this->CmdOut;
    this->CmdOut = this->CmdOut < -this->OutLimit ? -this->OutLimit : this->CmdOut;

    return this->CmdOut;
}
