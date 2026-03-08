// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/FPSGameMode.h"
#include "Core/FPSPlayerController.h"
#include "Characters/FPSCharacter.h"

AFPSGameMode::AFPSGameMode()
{
    // 设置默认玩家角色类
    DefaultPawnClass = AFPSCharacter::StaticClass();
    
    // 设置默认玩家控制器类
    PlayerControllerClass = AFPSPlayerController::StaticClass();
    
    // 默认重生延迟3秒
    RespawnDelay = 3.0f;
}

void AFPSGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // 游戏开始时的初始化逻辑
    UE_LOG(LogTemp, Log, TEXT("FPS Game Mode Started"));
}

void AFPSGameMode::RespawnPlayer(AController* Controller)
{
    if (Controller)
    {
        // 重启玩家（在出生点重新生成）
        RestartPlayer(Controller);
    }
}

void AFPSGameMode::OnPlayerKilled(AController* KilledPlayer, AController* Killer)
{
    if (KilledPlayer)
    {
        // 延迟重生
        FTimerHandle RespawnTimerHandle;
        FTimerDelegate RespawnDelegate;
        RespawnDelegate.BindUFunction(this, FName("RespawnPlayer"), KilledPlayer);
        
        GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
    }
}
