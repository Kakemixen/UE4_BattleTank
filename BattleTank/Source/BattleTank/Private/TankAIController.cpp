// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());

	GetPawn()->FindComponentByClass<UTankAimingComponent>()->Fire();
}






