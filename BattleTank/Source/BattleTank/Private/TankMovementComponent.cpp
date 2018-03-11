// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!LeftTrack || !RightTrack) {
		UE_LOG(LogTemp, Error, TEXT("%s No tracks added"), *GetName());
		return;
	}

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("%s Intention Forward: %f"), *GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("%s Intention Right: %f"), *GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}