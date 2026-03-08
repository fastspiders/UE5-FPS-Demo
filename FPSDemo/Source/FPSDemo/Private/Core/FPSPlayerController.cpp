// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/FPSPlayerController.h"
#include "Characters/FPSCharacter.h"

AFPSPlayerController::AFPSPlayerController()
{
    bShowMouseCursor = false;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFPSPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AFPSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UInputComponent* PlayerInputComponent = InputComponent)
    {
        // 轴映射 - 移动
        PlayerInputComponent->BindAxis("MoveForward", this, &AFPSPlayerController::OnMoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &AFPSPlayerController::OnMoveRight);

        // 轴映射 - 视角
        PlayerInputComponent->BindAxis("Turn", this, &AFPSPlayerController::OnTurn);
        PlayerInputComponent->BindAxis("LookUp", this, &AFPSPlayerController::OnLookUp);

        // 动作映射 - 跳跃
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSPlayerController::OnStartJump);
        PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSPlayerController::OnStopJump);

        // 动作映射 - 射击
        PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSPlayerController::OnFire);

        // 动作映射 - 交互
        PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSPlayerController::OnInteract);

        // 动作映射 - 换弹
        PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSPlayerController::OnReload);
    }
}

void AFPSPlayerController::OnMoveForward(float Value)
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->MoveForward(Value);
    }
}

void AFPSPlayerController::OnMoveRight(float Value)
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->MoveRight(Value);
    }
}

void AFPSPlayerController::OnTurn(float Value)
{
    AddYawInput(Value);
}

void AFPSPlayerController::OnLookUp(float Value)
{
    AddPitchInput(Value);
}

void AFPSPlayerController::OnStartJump()
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->StartJump();
    }
}

void AFPSPlayerController::OnStopJump()
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->StopJump();
    }
}

void AFPSPlayerController::OnFire()
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->FireWeapon();
    }
}

void AFPSPlayerController::OnInteract()
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->Interact();
    }
}

void AFPSPlayerController::OnReload()
{
    if (AFPSCharacter* FPSCharacter = Cast<AFPSCharacter>(GetPawn()))
    {
        FPSCharacter->ReloadWeapon();
    }
}
