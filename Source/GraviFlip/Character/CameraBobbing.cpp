// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBobbing.h"

UCameraBobbing::UCameraBobbing() {
	this->OscillationDuration = 9999999999.f;
	this->OscillationBlendInTime = 0.4f;
	this->OscillationBlendOutTime = 0.4f;
	LocOscillation.Z.Amplitude = 10.f;
	LocOscillation.Z.Frequency = 3.f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
}
