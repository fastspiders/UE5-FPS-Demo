// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * FPS玩家控制器
 * 负责处理玩家输入和游戏交互
 */
UCLASS()
class FPSDEMO_API AFPSPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AFPSPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // 输入处理函数
    UFUNCTION()
    void OnMoveForward(float Value);

    UFUNCTION()
    void OnMoveRight(float Value);

    UFUNCTION()
    void OnTurn(float Value);

    UFUNCTION()
    void OnLookUp(float Value);

    UFUNCTION()
    void OnStartJump();

    UFUNCTION()
    void OnStopJump();

    UFUNCTION()
    void OnFire();

    UFUNCTION()
    void OnInteract();

    UFUNCTION()
    void OnReload();
};
