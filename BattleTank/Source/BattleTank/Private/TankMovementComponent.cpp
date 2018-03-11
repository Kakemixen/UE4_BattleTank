// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!LeftTrack || !RightTrack) { return; }

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Intention Forward: %f"), *GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Intention Right: %f"), *GetName(), Throw);

}