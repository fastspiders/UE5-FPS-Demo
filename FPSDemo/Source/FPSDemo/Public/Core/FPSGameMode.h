// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

/**
 * FPS游戏模式基类
 * 负责管理游戏规则、玩家生成和游戏状态
 */
UCLASS()
class FPSDEMO_API AFPSGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AFPSGameMode();

protected:
    virtual void BeginPlay() override;

public:
    /** 玩家重生时间（秒） */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Game Mode")
    float RespawnDelay;

    /** 重生玩家 */
    UFUNCTION(BlueprintCallable, Category = "FPS Game Mode")
    void RespawnPlayer(AController* Controller);

    /** 玩家死亡时调用 */
    UFUNCTION(BlueprintCallable, Category = "FPS Game Mode")
    void OnPlayerKilled(AController* KilledPlayer, AController* Killer);
};
