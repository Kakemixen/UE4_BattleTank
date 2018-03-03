// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController begin"));
	ATank* TempTank = GetControlledTank();
	if (TempTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No Tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Has Tank %s"), *TempTank->GetName());
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

