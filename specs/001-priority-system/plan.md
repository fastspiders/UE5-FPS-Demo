# Implementation Plan: 功能实现优先级系统

**Branch**: `001-priority-system` | **Date**: 2026-03-02 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `/specs/001-priority-system/spec.md`

## Summary

本计划实现UE5 FPS Demo的三个核心功能优先级系统：基础移动系统(P1)、射击系统(P2)、碰撞与交互系统(P3)。采用UE5标准架构，C++实现核心逻辑，蓝图配置可视化参数，使用Primitive组件替代美术资源。

## Technical Context

**Language/Version**: C++17 / Unreal Engine 5.0+  
**Primary Dependencies**: UE5核心模块（Engine, InputCore, GameplayTasks）  
**Storage**: N/A（无持久化存储需求）  
**Testing**: 手动游戏内测试 + 蓝图单元测试  
**Target Platform**: Windows 10/11  
**Project Type**: 游戏Demo/教学项目  
**Performance Goals**: 60 FPS稳定帧率，输入延迟<16ms  
**Constraints**: 无外部美术资源，使用Primitive组件，内存<500MB  
**Scale/Scope**: 单关卡演示，支持1名玩家本地游戏

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

| Principle | Status | Notes |
|-----------|--------|-------|
| I. UE5 Standard Project Structure | ✅ PASS | 遵循Source/Private/Public分离，Content按功能分类 |
| II. Primitive-First Asset Strategy | ✅ PASS | 角色使用胶囊体+立方体，武器使用几何体组合 |
| III. Feature Priority Enforcement | ✅ PASS | 严格按照P1移动→P2射击→P3碰撞顺序执行 |
| IV. C++/Blueprint Hybrid Architecture | ✅ PASS | 核心系统C++，UI/配置蓝图 |
| V. Student-Friendly Documentation | ✅ PASS | 中文注释，关键概念解释 |

## Project Structure

### Documentation (this feature)

```text
specs/001-priority-system/
├── plan.md              # 本文件
├── spec.md              # 特性规范
├── research.md          # Phase 0: 技术调研
├── data-model.md        # Phase 1: 数据模型设计
├── quickstart.md        # Phase 1: 快速开始指南
├── contracts/           # Phase 1: API契约
└── tasks.md             # Phase 2: 任务清单
```

### Source Code (UE5项目结构)

```text
Source/
├── FPSDemo/
│   ├── FPSDemo.Build.cs
│   ├── Private/
│   │   ├── Characters/
│   │   │   └── FPSCharacter.cpp           # P1: 角色移动控制
│   │   ├── Weapons/
│   │   │   └── FPSWeapon.cpp              # P2: 武器射击系统
│   │   ├── Core/
│   │   │   ├── FPSGameMode.cpp            # 游戏模式
│   │   │   └── FPSPlayerController.cpp    # 玩家控制器
│   │   └── Interactions/
│   │       └── FPSInteractionComponent.cpp # P3: 交互系统
│   └── Public/
│       ├── Characters/
│       │   └── FPSCharacter.h
│       ├── Weapons/
│       │   └── FPSWeapon.h
│       ├── Core/
│       │   ├── FPSGameMode.h
│       │   └── FPSPlayerController.h
│       └── Interactions/
│           └── FPSInteractionComponent.h

Content/
├── Maps/
│   └── Prototype/
│       └── TestMap.umap                   # 测试关卡
├── Blueprints/
│   ├── Characters/
│   │   └── BP_FPSCharacter.uasset         # 角色蓝图
│   ├── Weapons/
│   │   └── BP_Weapon_Base.uasset          # 武器蓝图
│   └── UI/
│       └── WBP_Crosshair.uasset           # 准星UI
└── Materials/
    └── Prototyping/
        ├── M_Player.uasset                # 玩家材质
        ├── M_Weapon.uasset                # 武器材质
        └── M_Environment.uasset           # 环境材质
```

**Structure Decision**: 采用标准UE5 C++项目结构，Source目录按功能模块组织（Characters/Weapons/Core/Interactions），Content目录按资产类型组织（Maps/Blueprints/Materials）。

## Implementation Checklist

1. **Phase 0: 技术调研**
   - [ ] 调研UE5 CharacterMovementComponent配置选项
   - [ ] 调研UE5射线检测（LineTrace）最佳实践
   - [ ] 调研UE5输入系统（Enhanced Input）配置方法
   - [ ] 调研UE5碰撞通道设置和物理交互

2. **Phase 1: 基础架构搭建**
   - [ ] 创建UE5 C++项目FPSDemo
   - [ ] 配置项目构建设置（FPSDemo.Build.cs）
   - [ ] 创建基础游戏模式类（FPSGameMode）
   - [ ] 创建玩家控制器类（FPSPlayerController）
   - [ ] 配置输入映射（Input Mapping）

3. **Phase 2: P1 - 基础移动系统**
   - [ ] 创建FPSCharacter C++类（继承ACharacter）
   - [ ] 添加第一人称相机组件（UCameraComponent）
   - [ ] 实现MoveForward/MoveRight移动函数
   - [ ] 实现StartJump/StopJump跳跃函数
   - [ ] 实现Turn/LookUp视角控制函数
   - [ ] 配置移动参数（速度、加速度、跳跃高度）
   - [ ] 创建BP_FPSCharacter蓝图并配置Primitive可视化
   - [ ] 在测试地图中验证移动功能

4. **Phase 3: P2 - 射击系统**
   - [ ] 创建FPSWeapon C++基类
   - [ ] 实现Fire射击函数（射线检测）
   - [ ] 实现弹药计数和管理逻辑
   - [ ] 添加射击冷却时间控制
   - [ ] 实现伤害传递接口（TakeDamage）
   - [ ] 添加枪口闪光效果（点光源+粒子）
   - [ ] 添加屏幕震动反馈（CameraShake）
   - [ ] 创建BP_Weapon_Base蓝图
   - [ ] 创建WBP_Crosshair准星UI
   - [ ] 在测试地图中放置可破坏目标并验证射击

5. **Phase 4: P3 - 碰撞与交互系统**
   - [ ] 创建FPSInteractionComponent交互组件
   - [ ] 实现交互检测（Overlap检测）
   - [ ] 实现拾取逻辑（Pickup）
   - [ ] 创建生命值系统（HealthComponent）
   - [ ] 实现伤害计算和死亡检测
   - [ ] 实现重生逻辑（Respawn）
   - [ ] 创建可拾取物品蓝图（BP_Pickup_Health, BP_Pickup_Ammo）
   - [ ] 配置碰撞通道（Visibility, Camera, Pawn）
   - [ ] 在测试地图中验证交互功能

6. **Phase 5: 整合与优化**
   - [ ] 整合所有系统到最终测试地图
   - [ ] 性能测试和优化（确保60FPS）
   - [ ] 代码清理和注释完善
   - [ ] 创建快速开始文档（quickstart.md）
   - [ ] 运行Constitution合规性检查

## Complexity Tracking

> **Fill ONLY if Constitution Check has violations that must be justified**

无违规项，所有设计均符合Constitution原则。

## Data Model

### Key Classes and Components

```cpp
// P1: 角色移动系统
class AFPSCharacter : public ACharacter
{
    UCameraComponent* FirstPersonCamera;
    UStaticMeshComponent* Mesh1P;  // 第一人称手臂网格
    
    // 移动函数
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void StartJump();
    void StopJump();
};

// P2: 武器系统
class AFPSWeapon : public AActor
{
    int32 CurrentAmmo;
    int32 MaxAmmo;
    float FireRate;
    float Damage;
    
    void Fire();
    bool CanFire();
    void Reload();
};

// P3: 交互系统
class UFPSInteractionComponent : public UActorComponent
{
    float InteractionDistance;
    
    void Interact();
    void CheckForInteractables();
};

// P3: 生命值系统
class UFPSHealthComponent : public UActorComponent
{
    float CurrentHealth;
    float MaxHealth;
    
    void TakeDamage(float Damage);
    void Die();
    void Respawn();
};
```

### Input Mappings

```cpp
// DefaultInput.ini 或 C++配置
// Axis Mappings
MoveForward: W (1.0), S (-1.0)
MoveRight: A (-1.0), D (1.0)
Turn: Mouse X
LookUp: Mouse Y

// Action Mappings
Jump: Space Bar
Fire: Left Mouse Button
Interact: E Key
Reload: R Key
```

## Testing Strategy

### P1 - 移动系统测试
- **功能测试**: 验证WASD移动、鼠标视角、跳跃功能正常
- **边界测试**: 同时按下多个方向键时的移动合成
- **性能测试**: 确保输入响应延迟<16ms

### P2 - 射击系统测试
- **功能测试**: 验证射线检测、伤害计算、弹药管理
- **精度测试**: 10米距离击中率>70%
- **反馈测试**: 验证枪口闪光、屏幕震动效果

### P3 - 交互系统测试
- **功能测试**: 验证拾取、伤害、死亡重生逻辑
- **碰撞测试**: 验证角色不能穿过墙壁
- **状态测试**: 验证生命值变化和状态同步

## Risk Mitigation

| Risk | Impact | Mitigation |
|------|--------|------------|
| UE5学习曲线陡峭 | 高 | 提供详细注释和文档，分阶段实现 |
| 输入延迟问题 | 中 | 使用Enhanced Input系统，优化Tick频率 |
| 性能不达标 | 中 | 使用Primitive组件，控制Draw Call数量 |
| 蓝图C++通信问题 | 低 | 明确定义UFUNCTION(BlueprintCallable)接口 |

## Next Steps

1. 运行 `/speckit.tasks` 生成详细任务清单
2. 开始Phase 0技术调研
3. 创建UE5项目并配置开发环境
