# FPS Demo 快速开始指南

## 项目概述

这是一个基于Unreal Engine 5的FPS（第一人称射击）最小可行Demo，用于展示基础游戏机制：
- **移动系统**: WASD移动、鼠标视角、空格跳跃
- **射击系统**: 鼠标左键射击、射线检测、弹药管理
- **交互系统**: 物理碰撞、物品拾取、生命值管理

## 系统要求

- **操作系统**: Windows 10/11 64位
- **开发环境**: Visual Studio 2022
- **Unreal Engine**: 5.0+
- **硬件要求**: 支持DirectX 12的显卡

## 项目结构

```
FPSDemo/
├── Source/FPSDemo/           # C++源代码
│   ├── Public/               # 头文件
│   │   ├── Characters/       # 角色相关
│   │   ├── Weapons/          # 武器系统
│   │   ├── Core/             # 核心系统
│   │   └── Interactions/     # 交互系统
│   └── Private/              # 实现文件
├── Content/                  # 游戏内容
│   ├── Maps/                 # 关卡
│   ├── Blueprints/           # 蓝图
│   └── Materials/            # 材质
└── Config/                   # 配置文件
```

## 控制说明

| 操作 | 按键 | 说明 |
|------|------|------|
| 前进/后退 | W/S | 角色前后移动 |
| 左移/右移 | A/D | 角色左右移动 |
| 视角控制 | 鼠标 | 控制摄像机方向 |
| 跳跃 | 空格 | 角色跳跃 |
| 射击 | 鼠标左键 | 发射武器 |
| 交互 | E | 与物品交互 |
| 换弹 | R | 重新装填弹药 |

## 构建步骤

### 1. 生成Visual Studio项目文件

在项目根目录运行：
```bash
# 右键点击 FPSDemo.uproject 文件，选择 "Generate Visual Studio project files"
# 或者使用命令行（需要Unreal Engine安装路径）：
"C:\Program Files\Epic Games\UE_5.0\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="%CD%\FPSDemo.uproject" -game -engine -progress
```

### 2. 编译项目

打开生成的 `FPSDemo.sln` 文件，在Visual Studio 2022中：
- 选择配置: `Development Editor`
- 选择平台: `Win64`
- 按 `F5` 或点击 `Build` 编译并启动

### 3. 运行游戏

编译成功后：
- 在Unreal Editor中打开 `Content/Maps/Prototype/TestMap`
- 点击 `Play` 按钮开始游戏
- 或使用独立模式：`File -> Package Project -> Windows`

## 核心类说明

### AFPSCharacter (角色控制器)
- **位置**: `Source/FPSDemo/Characters/FPSCharacter.cpp`
- **功能**: 处理玩家移动、视角控制、跳跃
- **关键函数**:
  - `MoveForward/MoveRight`: 移动控制
  - `StartJump/StopJump`: 跳跃控制
  - `FireWeapon`: 武器射击

### AFPSWeapon (武器系统)
- **位置**: `Source/FPSDemo/Weapons/FPSWeapon.cpp`
- **功能**: 实现射击逻辑、弹药管理、伤害计算
- **关键函数**:
  - `Fire`: 执行射击
  - `Reload`: 重新装填
  - `CanFire`: 检查射击条件

### UFPSHealthComponent (生命值)
- **位置**: `Source/FPSDemo/Interactions/FPSHealthComponent.cpp`
- **功能**: 管理角色生命值、受伤、死亡
- **关键函数**:
  - `TakeDamage`: 受到伤害
  - `Heal`: 恢复生命
  - `Die/Respawn`: 死亡和重生

### UFPSInteractionComponent (交互组件)
- **位置**: `Source/FPSDemo/Interactions/FPSInteractionComponent.cpp`
- **功能**: 处理物品拾取、环境交互
- **关键函数**:
  - `Interact`: 执行交互
  - `CheckForInteractables`: 检测可交互对象

## 调试功能

在开发过程中，可以使用以下调试功能：

### 显示调试信息
```cpp
// 在代码中添加
UE_LOG(LogTemp, Log, TEXT("调试信息"));

// 在控制台输入
show collision  // 显示碰撞体
show lines      // 显示射线
stat fps        // 显示帧率
```

### 常用控制台命令
- `slomo 0.5`: 慢动作（0.5倍速）
- `slomo 1`: 恢复正常速度
- `ghost`: 穿墙模式
- `walk`: 恢复正常移动

## 扩展开发

### 添加新武器
1. 继承 `AFPSWeapon` 类创建新武器类
2. 在蓝图中配置武器属性（伤害、射速、弹药）
3. 在角色中添加武器切换逻辑

### 添加新交互对象
1. 创建继承自 `AActor` 的新类
2. 实现交互接口
3. 在关卡中放置并配置

### 性能优化
- 使用 `Primitive` 组件替代复杂网格
- 控制Draw Call数量
- 优化碰撞检测频率

## 常见问题

### Q: 编译失败，提示找不到模块？
A: 确保已安装Visual Studio 2022的C++游戏开发工作负载，并安装了Windows 10/11 SDK。

### Q: 角色无法移动？
A: 检查 `DefaultInput.ini` 配置，确保输入映射正确。验证角色是否被正确设置为玩家控制。

### Q: 射击没有反应？
A: 检查武器是否正确附加到角色，弹药是否充足，以及射线检测的碰撞通道配置。

### Q: 帧率过低？
A: 在编辑器中使用 `stat fps` 查看性能统计，检查是否有性能瓶颈。考虑简化场景或使用更简单的材质。

## 学习资源

- **UE5官方文档**: https://docs.unrealengine.com/5.0/
- **C++编程指南**: https://docs.unrealengine.com/5.0/programming-and-scripting/
- **第一人称射击教程**: https://docs.unrealengine.com/5.0/first-person-shooter-tutorial/

## 版本历史

- **v1.0.0** (2026-03-02)
  - 初始版本
  - 实现基础移动系统
  - 实现射击系统
  - 实现碰撞与交互系统
