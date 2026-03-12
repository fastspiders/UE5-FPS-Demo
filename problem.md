# 问题追踪日志

---

## 问题 001: VS 无法生成 .sln 文件（环境版本不匹配）

**状态**: ✅ 已解决  
**优先级**: 高（阻塞性）  
**发现日期**: 2026-03-03  
**解决日期**: 2026-03-03  
**相关任务**: T001, T002

### 问题描述

在项目初始化阶段，右键 `FPSDemo.uproject` 文件选择 "Generate Visual Studio project files" 后，无法成功生成 `.sln` 解决方案文件，或者生成的文件无法正常使用。

### 根本原因

**工具和环境版本不匹配**：
- UE5 项目配置文件中指定的 Visual Studio 版本与本机实际安装版本不一致
- Windows SDK 版本号不匹配
- C++ 工具链版本冲突

典型错误信息示例：
```
Error: Visual Studio 2022 not found
Error: Windows SDK version 10.0.xxxxx not found
```

### 解决方案

1. **收集错误信息**：
   - 打开终端（PowerShell 或 CMD）
   - 运行生成命令查看详细报错
   - 复制包含 `error` 关键字的完整错误信息

2. **提供环境信息给 AI**：
   ```
   - Visual Studio 版本：如 2022 Community/Professional/Enterprise v17.x
   - Windows SDK 版本：如 10.0.19041.0
   - UE5 版本：如 5.7.0
   - .NET 版本：如 8.0
   ```

3. **AI 协助修改配置文件**：
   - 检查 `FPSDemo.Build.cs`
   - 检查 `.vsconfig` 文件
   - 调整版本号和依赖项

4. **重新生成**：
   ```bash
   # 方法 A: 右键 FPSDemo.uproject → Generate Visual Studio project files
   # 方法 B: 命令行生成
   "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" -projectfiles -project="D:\UElearning\MyAIGame\FPSDemo\FPSDemo.uproject" -game -engine -progress
   ```

### 经验教训

✅ **下次开发时必须提供**：
- 详细且正确的开发环境版本信息
- Visual Studio 完整版本号（包括小版本号）
- Windows SDK 版本
- UE5 精确版本

---

## 问题 002: VS 编译错误（重复声明）

**状态**: ✅ 已解决  
**优先级**: 高（阻塞性）  
**发现日期**: 2026-03-03  
**解决日期**: 2026-03-03  
**相关任务**: T005-T008

### 问题描述

在 Visual Studio 中编译项目时出现编译错误，提示某些类或函数重复声明。

典型错误信息：
```
error C2011: 'AFPSCharacter': 'class' type redefinition
error C2084: function 'void AFPSCharacter::MoveForward(float)' already has a body
```

### 根本原因

**代码生成与修改不同步**：
1. AI 生成的代码与手动修改的代码存在冲突
2. 头文件 (`.h`) 和实现文件 (`.cpp`) 中的声明不一致
3. 多次生成代码导致重复内容
4. 复制粘贴代码时遗漏了某些部分

### 解决方案

1. **收集错误信息**：
   - 打开 Visual Studio 的 **输出 (Output)** 窗口
   - 筛选包含 `error` 的行
   - 复制完整的错误信息和行号

2. **AI 阅读代码定位问题**：
   - AI 读取报错的 `.h` 和 `.cpp` 文件
   - 对比声明和实现
   - 找出重复或冲突的部分

3. **修复步骤**：
   - 删除重复的声明或实现
   - 确保头文件只声明一次
   - 确保 `.cpp` 文件正确包含对应的 `.h` 文件
   - 检查是否有多个文件定义了相同的符号

4. **清理并重新编译**：
   - 在 VS 中选择 **Build → Clean Solution**
   - 然后 **Build → Rebuild Solution**

### 预防措施

✅ **代码生成最佳实践**：
- 每次生成新代码前备份当前文件
- 使用 Git 进行版本控制
- 保留对话日志以便追溯代码来源
- 明确告知 AI 哪些文件已被手动修改过

---

## 问题 003: 运行时屏幕中心显示蓝色调试图形

**状态**: ✅ 已解决  
**优先级**: 低（视觉干扰）  
**发现日期**: 2026-03-03  
**解决日期**: 2026-03-05  
**相关任务**: T014, T038

### 问题描述

在 UE5 编辑器中点击 **Play** 运行游戏时，屏幕正中心出现：
- 一个**蓝色虚线绘制的多面体**（通常是立方体或球体轮廓）
- 一个**蓝色箭头**指向某个方向

这些图形影响视线，干扰游戏体验。

### 根本原因

**调试可视化代码未移除**：

AI 在生成代码时为了方便调试，添加了以下调试绘制函数：
```cpp
// FPSWeapon.cpp 或其他视角相关代码
DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Blue, false, 2.f, 0, 1.f);
DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10.f, FColor::Red, false, 2.f);
DrawDebugSphere(GetWorld(), Center, Radius, Segments, FColor::Blue, false, Duration);
```

这些代码的作用：
- **蓝色多面体**：显示碰撞检测范围或交互区域
- **蓝色箭头/线**：显示射线检测路径或视角方向
- **持续时间**：通常设置为 2 秒自动消失

**问题**：AI 没有明确告知用户这是调试功能，导致用户误以为是 bug。

### 解决方案

#### 方案 A: 完全移除调试代码（推荐）

1. **让 AI 阅读所有视角相关的 C++ 代码**：
   - `FPSCharacter.cpp`（相机和视角）
   - `FPSWeapon.cpp`（射线检测）
   - `FPSInteractionComponent.cpp`（交互检测）

2. **搜索并删除/注释掉调试绘制函数**：
   ```cpp
   // 查找以下模式
   DrawDebugLine(...)
   DrawDebugPoint(...)
   DrawDebugSphere(...)
   DrawDebugBox(...)
   
   // 删除或注释
   // DrawDebugLine(...);  ← 注释掉
   ```

3. **重新编译并测试**

#### 方案 B: 条件编译（开发阶段有用）

```cpp
#if ENABLE_DRAW_DEBUG
    DrawDebugLine(...);  // 只在 Debug 模式下显示
#endif
```

### 经验教训

✅ **下次开发时必须强调**：
1. **AI 应该明确告知**：
   - 添加了哪些调试代码
   - 调试代码的作用是什么
   - 如何关闭或移除调试功能

2. **开发者应该**：
   - 在终端开发时**保留对话日志**
   - 使用浏览器的保存功能或截图记录重要对话
   - 关闭会话前导出聊天记录
   - 避免不小心关闭会话窗口后丢失上下文

3. **防止信息不对等**：
   - 每次开始新会话时提供之前的关键决策记录
   - 使用 `AGENTS.md` 或类似文件跟踪项目状态
   - 重要的代码变更要记录在案

---

## 问题 004: 第一人称视角下手臂和武器可见性问题

**状态**: ⚠️ 部分解决（武器可见，但手臂静止）  
**优先级**: 低（不影响核心玩法）  
**发现日期**: 2026-03-05  
**相关任务**: T036, T038

### 问题描述

在游戏运行时，由于没有设置动画蓝图，角色的第一人称手臂模型保持静止下垂姿势。虽然武器已通过 `WeaponSocket` 正确附加到右手骨骼 (`ik_hand_r`)，但武器位于视野边缘且方向怪异，无法达到理想的持枪视觉效果。

### 根本原因

1. **缺少动画蓝图**: `BP_FPSCharacter` 的 `Mesh1P` 组件没有设置 Animation Blueprint
2. **缺少持枪姿态**: 没有针对持枪状态的专用动画蓝图
3. **静态骨骼姿势**: `SKM_Manny_Simple` 模型的默认姿势是双臂自然下垂，不适合第一人称持枪视角

### 已实施的解决方案

✅ **已完成**:
- 在 `SKM_Manny_Simple` 的 `ik_hand_r` 骨骼上创建 `WeaponSocket`
- 修改 C++ 代码 `FPSCharacter.cpp:191` 使用 `TEXT("WeaponSocket")` 附加武器
- 武器成功生成并跟随相机移动
- 射击功能正常工作（射线检测、伤害计算、弹药管理）

⏸️ **延期实现**:
- 持枪动画蓝图创建
- 手臂抬起姿势配置
- 武器与手臂的精确对齐

### 影响评估

| 方面 | 影响程度 | 说明 |
|------|---------|------|
| 游戏可玩性 | **无影响** | 射击、移动等核心功能正常 |
| 视觉体验 | 中等影响 | 武器位置不自然，沉浸感降低 |
| 后续开发 | 轻微影响 | 添加动画时需要重新调整武器位置 |

### 计划解决方案

#### 短期（当前阶段 - MVP）✅
**接受现状**, 因为:
- 核心射击功能正常工作
- 射线检测、伤害计算、弹药管理都已实现
- 武器可见且跟随视角移动
- **不影响功能测试和游戏性验证**

#### 中期（动画阶段 - 待实施）
1. 创建基础移动动画蓝图 `ABP_FPSCharacter`
   - 混合空间 (Blend Space): Idle/Walk/Run 混合
   - 状态机：地面/空中/瞄准状态
   
2. 创建持枪动画蓝图 `ABP_Rifle_Arms`
   - 使用 UE5 官方持枪动画资源
   - 配置 IK (逆向动力学) 确保手掌握住武器
   
3. 在 `BP_FPSCharacter` 中根据武器状态切换动画蓝图

4. 调整 `WeaponSocket` 位置以匹配持枪动画

#### 长期（优化阶段）
- 添加换弹动画
- 添加武器切换动画
- 添加射击后坐力动画
- 添加蹲下/匍匐等多姿态支持

### 技术要点记录

#### Socket 命名规范
- `ik_hand_r`: 右手 IK 控制点（用于持枪）
- `ik_hand_l`: 左手 IK 控制点（用于辅助握持）
- `WeaponSocket`: 自定义武器附加点（基于 `ik_hand_r` 创建）

#### 武器附加代码
```cpp
// FPSCharacter.cpp:191
CurrentWeapon->AttachToComponent(
    Mesh1P, 
    FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
    TEXT("WeaponSocket")
);
```

---

## 问题 004: 第一人称视角下手臂和武器可见性问题

**状态**: ⚠️ 部分解决（武器可见，但手臂静止）  
**优先级**: 低（不影响核心玩法）  
**发现日期**: 2026-03-05  
**相关任务**: T036, T038

### 问题描述

在游戏运行时，由于没有设置动画蓝图，角色的第一人称手臂模型保持静止下垂姿势。虽然武器已通过 `WeaponSocket` 正确附加到右手骨骼 (`ik_hand_r`)，但武器位于视野边缘且方向怪异，无法达到理想的持枪视觉效果。

### 根本原因

1. **缺少动画蓝图**: `BP_FPSCharacter` 的 `Mesh1P` 组件没有设置 Animation Blueprint
2. **缺少持枪姿态**: 没有针对持枪状态的专用动画蓝图
3. **静态骨骼姿势**: `SKM_Manny_Simple` 模型的默认姿势是双臂自然下垂，不适合第一人称持枪视角

### 已实施的解决方案

✅ **已完成**:
- 在 `SKM_Manny_Simple` 的 `ik_hand_r` 骨骼上创建 `WeaponSocket`
- 修改 C++ 代码 `FPSCharacter.cpp:191` 使用 `TEXT("WeaponSocket")` 附加武器
- 武器成功生成并跟随相机移动
- 射击功能正常工作（射线检测、伤害计算、弹药管理）

⏸️ **延期实现**:
- 持枪动画蓝图创建
- 手臂抬起姿势配置
- 武器与手臂的精确对齐

### 影响评估

| 方面 | 影响程度 | 说明 |
|------|---------|------|
| 游戏可玩性 | **无影响** | 射击、移动等核心功能正常 |
| 视觉体验 | 中等影响 | 武器位置不自然，沉浸感降低 |
| 后续开发 | 轻微影响 | 添加动画时需要重新调整武器位置 |

### 计划解决方案

#### 短期（当前阶段 - MVP）✅
**接受现状**, 因为:
- 核心射击功能正常工作
- 射线检测、伤害计算、弹药管理都已实现
- 武器可见且跟随视角移动
- **不影响功能测试和游戏性验证**

#### 中期（动画阶段 - 待实施）
1. 创建基础移动动画蓝图 `ABP_FPSCharacter`
   - 混合空间 (Blend Space): Idle/Walk/Run 混合
   - 状态机：地面/空中/瞄准状态
   
2. 创建持枪动画蓝图 `ABP_Rifle_Arms`
   - 使用 UE5 官方持枪动画资源
   - 配置 IK (逆向动力学) 确保手掌握住武器
   
3. 在 `BP_FPSCharacter` 中根据武器状态切换动画蓝图

4. 调整 `WeaponSocket` 位置以匹配持枪动画

#### 长期（优化阶段）
- 添加换弹动画
- 添加武器切换动画
- 添加射击后坐力动画
- 添加蹲下/匍匐等多姿态支持

### 技术要点记录

#### Socket 命名规范
- `ik_hand_r`: 右手 IK 控制点（用于持枪）
- `ik_hand_l`: 左手 IK 控制点（用于辅助握持）
- `WeaponSocket`: 自定义武器附加点（基于 `ik_hand_r` 创建）

#### 武器附加代码
```cpp
// FPSCharacter.cpp:191
CurrentWeapon->AttachToComponent(
    Mesh1P, 
    FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
    TEXT("WeaponSocket")
);
```

---

## 问题 005: 角色模型阴影不可见

**状态**: ℹ️ 设计决定（无需修复）  
**优先级**: 极低  
**发现日期**: 2026-03-05

### 问题描述

游戏中可以看到武器的地面阴影，但看不到角色手臂的阴影。

### 原因分析

这是**预期行为**，因为：
1. `Mesh1P` 组件在 C++ 中明确设置了 `CastShadow = false`
2. 第一人称手臂通常不需要投射阴影（节省性能）
3. 武器是独立 Actor，默认开启阴影

### 解决方案

**无需修改**。如果未来需要第三人称视角，可以添加完整的第三人称角色模型负责投射阴影。

---

## 问题 006: 如何创建第一人称准星UI

**状态**: ✅ 已解决  
**优先级**: 中  
**发现日期**: 2026-03-05  
**解决日期**: 2026-03-05  
**相关任务**: T037

### 问题描述

在 FPS 游戏中，需要一个屏幕中心的准星来辅助瞄准。如何在 UE5 中创建并显示一个始终居中的准星UI？

### 需求分析

- 准星必须始终显示在屏幕正中心
- 不随角色移动或视角转动而偏移
- 使用图片准星（比绘制的十字更美观）
- 透明背景 PNG 格式

### 解决方案

#### 步骤 1: 创建 Widget 蓝图

1. 在 **内容浏览器** 中进入 `Content/Blueprints/UI/`
2. **右键** → **用户界面 (User Interface)** → **控件蓝图 (Widget Blueprint)**
3. 选择父类：**User Widget**（用户控件）
4. 命名为 `WBP_Crosshair`

#### 步骤 2: 导入准星图片

1. 准备一张透明背景的 PNG 准星图片（建议 64x64 或 128x128）
2. 在 **内容浏览器** 中右键 → **导入 (Import)**
3. 选择图片文件，命名为 `T_Crosshair`

#### 步骤 3: 设计准星UI

**关键点：必须使用 Canvas Panel 才能让 UI 居中！**

1. 双击打开 `WBP_Crosshair`
2. 在 **面板 (Palette)** 中找到 **画布面板 (Canvas Panel)**
3. 拖动 **画布面板** 到左侧 **层次结构 (Hierarchy)** 的空白处
4. 再从 **面板** 拖动 **图像 (Image)** 到 **画布面板** 上（确保是子项）

**现在的层次结构应该是：**
```
📁 画布面板 0 (CanvasPanel_0)
  └─ 🖼️ Image_0
```

#### 步骤 4: 设置图片纹理

1. 选中 `Image_0` 组件
2. 在右侧 **细节 (Details)** 面板中找到 **外观 (Appearance)** 或 **笔刷 (Brush)**
3. 点击 **图像 (Image)** 旁边的小圆圈 🔘
4. 选择导入的 `T_Crosshair` 纹理

#### 步骤 5: 设置锚点和位置（最关键！）

选中 `Image_0`，在 **细节** 面板的 **插槽 (Canvas Panel Slot)** 中设置：

| 属性 | 值 | 说明 |
|------|-----|------|
| **锚点 (Anchors)** | 中心预设（四个点都在中间） | 让 UI 以屏幕中心为锚点 |
| **对齐 (Alignment)** | X=0.5, Y=0.5 | 完全居中 |
| **位置 (Position)** | X=0, Y=0 | 位于锚点位置 |
| **大小 (Size)** | X=32, Y=32 | 根据图片实际大小调整 |

**或者更直观的方法：**
- 在中间的 **设计视图** 中直接拖动图片到中心
- 拖动四角的控制点调整大小

#### 步骤 6: 在角色蓝图中显示准星

1. 打开 `BP_FPSCharacter`
2. 切换到 **事件图表 (Event Graph)**
3. 添加以下节点：

```
Event BeginPlay
    ↓
Create Widget (Class: WBP_Crosshair)
    - Owning Player: Get Player Controller
    ↓
Add to Viewport
```

**完整节点流程：**
- 右键搜索 `Event BeginPlay`
- 从 Execute 引脚拖线 → 搜索 `Create Widget`
  - Class: 选择 `WBP_Crosshair`
- 从 Create Widget 的返回值拖线 → 搜索 `Add to Viewport`

#### 步骤 7: 编译测试

1. 点击 **编译 (Compile)**
2. 点击 **保存 (Save)**
3. 运行游戏，准星应该显示在屏幕正中心

### 常见问题

#### Q1: 找不到"插槽 (Canvas Panel Slot)"选项
**原因**: Image 没有放在 Canvas Panel 里面  
**解决**: 
- 删除当前 Image
- 先添加 Canvas Panel
- 再把 Image 拖到 Canvas Panel 上（作为子项）

#### Q2: 准星不在屏幕中心
**检查**:
- 锚点是否设置为"中心"预设
- Alignment 是否为 (0.5, 0.5)
- Position 是否为 (0, 0)

#### Q3: 准星太大或太小
**解决**: 调整 Size 的 X 和 Y 值，或使用设计视图的控制点拖动

### 技术要点

- **Canvas Panel** 是唯一支持精确位置控制的 UI 容器
- **锚点 (Anchors)** 决定 UI 相对于屏幕的位置基准
- **对齐 (Alignment)** 决定 UI 在锚点内的对齐方式
- UI 默认在所有玩家屏幕上显示，如需分屏游戏需要特殊处理

### 参考资料

- UE5 UMG 文档：https://docs.unrealengine.com/5.0/umg-ui-designer-in-unreal-engine/
- Widget 蓝图最佳实践

---

## 问题 007: 如何让靶子被击中后朝射击方向倒下

**状态**: ✅ 已解决  
**优先级**: 中  
**发现日期**: 2026-03-05  
**解决日期**: 2026-03-05  
**相关任务**: T039

### 问题描述

在射击游戏中，希望靶子或其他物体被子弹击中后能够朝射击方向倒下，提供真实的命中反馈。如何实现这个效果？

### 需求分析

- 靶子平时保持静止站立（不启用物理）
- 被子弹击中时启用物理
- 倒下的方向与子弹飞行方向一致
- 有适当的冲击力反馈

### 解决方案

#### 步骤 1: 创建靶子蓝图

1. 在 **内容浏览器** 右键 → **蓝图类 (Blueprint Class)**
2. 选择父类：**Actor**
3. 命名为 `BP_Target`
4. 双击打开

#### 步骤 2: 添加网格体组件

1. 在 **组件 (Components)** 面板点击 **+ 添加 (+ Add)**
2. 选择 **静态网格体 (Static Mesh)**
3. 命名为 `TargetMesh`
4. 在 **细节 (Details)** 面板中：
   - **静态网格体 (Static Mesh)**: 选择 `Cube` 或其他形状
   - **碰撞 (Collision)** → **碰撞预设 (Collision Presets)**: 选择 **阻挡全部 (BlockAll)**
   - **物理 (Physics)** → **模拟物理 (Simulate Physics)**: ❌ **取消勾选**（重要！）

#### 步骤 3: 添加伤害响应事件

切换到 **事件图表 (Event Graph)**：

1. 右键空白处 → 搜索 `AnyDamage`
2. 选择 **Event AnyDamage**（这是 Actor 受到伤害时自动触发的事件）

**Event AnyDamage 的输出引脚：**
- **Execute**: 执行流
- **Damage**: 伤害值（float）
- **EventInstigator**: 伤害发起者控制器
- **DamageCauser**: 造成伤害的 Actor（武器或子弹）

#### 步骤 4: 构建事件链

按顺序连接以下节点：

```
Event AnyDamage
    ↓
Print String ("🎯 Target Hit! Damage: " + Damage)
    ↓
Set Simulate Physics (Target: TargetMesh, New Simulate Physics: ✓)
    ↓
Get Actor Forward Vector (from DamageCauser or Instigator)
    ↓
Multiply (Vector × Float, B=500)
    ↓
Add Impulse (Target: TargetMesh, Impulse: 计算结果，Velocity Change: ✓)
```

**详细步骤：**

**节点 1: Print String（调试用）**
- 从 `Event AnyDamage` 的 Execute 引脚拖线 → 搜索 `Print String`
- **In String**: `"🎯 Target Hit!"`

**节点 2: Set Simulate Physics**
- 从 `Print String` 的输出引脚拖线 → 搜索 `Set Simulate Physics`
- **Target**: 选择 `TargetMesh`
- **New Simulate Physics**: ✅ 勾选

**节点 3: 获取射击方向**
- 从 `Event AnyDamage` 的 **EventInstigator** 引脚拖线 → 搜索 `Get Actor Forward Vector`
- 这会获取射击者的朝向向量

**节点 4: 放大冲量**
- 从 `Get Actor Forward Vector` 的返回值拖线 → 搜索 `Multiply (vector * float)`
- **B**（倍数）: 输入 `500`（可以根据需要调整）

**节点 5: Add Impulse**
- 从 `Multiply` 拖线 → 搜索 `Add Impulse`
- **Target**: `TargetMesh`
- **Impulse**: 连接刚才的计算结果
- **Velocity Change**: ✅ 勾选（这很重要！）

#### 步骤 5: 编译测试

1. 点击 **编译 (Compile)**
2. 点击 **保存 (Save)**
3. 打开 `TestMap`，将 `BP_Target` 拖入场景
4. 运行游戏，射击靶子

**预期效果：**
- 靶子原本静止不动
- 被击中后突然启用物理
- 朝着子弹飞行的方向倒下

### 关键参数调优

#### 冲量大小（Multiply 的 B 值）

| B 值 | 效果 | 适用场景 |
|------|------|---------|
| 100-300 | 轻微推动 | 小物体、纸片 |
| 500-1000 | 适中推动 | 标准靶子、木箱 |
| 2000-5000 | 强力击飞 | 爆炸效果、重型物体 |

#### Velocity Change 选项

- ✅ **勾选**: 直接改变速度，忽略物体质量（推荐）
- ❌ **不勾选**: 施加力，受物体质量影响

### 进阶效果

#### 方案 A: 使用命中点法线方向

如果想让靶子朝射线命中的方向倒下（而不是射击者朝向）：

1. 从 `Event AnyDamage` 的 **Hit Result** 引脚拖线 → 搜索 `Break Hit Result`
2. 从 **Normal** 引脚拖线 → `Multiply` → `Add Impulse`
3. 这样靶子会朝射线命中表面的法线方向倒下

#### 方案 B: 血量系统（多次射击才倒下）

1. 在 **我的蓝图 (My Blueprint)** 中添加变量：
   - 名称：`Health`
   - 类型：`float`
   - 默认值：`100.0`

2. 修改事件链：
```
Event AnyDamage
    ↓
Subtract: Health = Health - Damage
    ↓
Branch: Health <= 0?
    ├─ True → 启用物理 + Add Impulse
    └─ False → Print String ("Hit! Health: " + Health)
```

#### 方案 C: 添加音效和粒子效果

在 `Add Impulse` 之后添加：

**音效：**
- 添加节点：`Play Sound at Location`
- **Sound**: 选择撞击音效（如 `Impact_Wood` 或 `Impact_Metal`）

**粒子效果：**
- 添加节点：`Spawn Emitter at Location`
- **Emitter Template**: 选择火花或烟雾粒子
- **Location**: `Get Actor Location`

### 常见问题

#### Q1: 靶子直接被玩家碰撞推倒
**原因**: 初始就启用了物理  
**解决**: 确保 `TargetMesh` 的 **模拟物理** 是 **未勾选** 状态

#### Q2: 靶子被击中后没有任何反应
**检查清单**:
- [ ] `Event AnyDamage` 事件存在
- [ ] `Set Simulate Physics` 节点存在且连接正确
- [ ] `Add Impulse` 节点存在
- [ ] `Add Impulse` 的 **Velocity Change** 已勾选
- [ ] 冲量数值足够大（至少 500）
- [ ] 能看到 `"🎯 Target Hit!"` 输出

#### Q3: 靶子飞出的方向不对
**解决**: 
- 检查 `Get Actor Forward Vector` 的来源是否正确
- 尝试改用射击者的位置到靶子位置的向量：
  ```
  Get Actor Location (DamageCauser) → 
  Find Look At Rotation (Start: Causer, Target: Target) → 
  Get Forward Vector → 
  Multiply → 
  Add Impulse
  ```

#### Q4: 靶子直接飞出地图不落下
**原因**: 冲量太大或重力不够  
**解决**:
- 减小 Multiply 的倍数（如改为 200）
- 增加靶子的质量（在 Details 中设置 Mass = 50）

### 技术要点

- **Event AnyDamage**: 任何 Actor 受到通用伤害时都会触发
- **Set Simulate Physics**: 动态启用/禁用物理模拟
- **Add Impulse**: 施加瞬时冲量（不同于持续力）
- **Velocity Change**: 勾选后直接改变速度，不受质量影响
- **EventInstigator**: 伤害的发起者（通常是玩家控制器）
- **DamageCauser**: 造成伤害的 Actor（武器、子弹、爆炸等）

### 代码实现（C++ 版本）

如果需要 C++ 实现，在 `FPSWeapon.cpp::ApplyDamage()` 中：

```cpp
void AFPSWeapon::ApplyDamage(AActor* HitActor, const FHitResult& HitResult)
{
    if (!HitActor) return;

    // 对角色应用伤害
    AFPSCharacter* HitCharacter = Cast<AFPSCharacter>(HitActor);
    if (HitCharacter)
    {
        HitCharacter->TakeDamage(Damage);
        return;
    }

    // 对其他 Actor 应用通用伤害（触发 Event AnyDamage）
    AController* InstigatorController = GetInstigatorController();
    UGameplayStatics::ApplyDamage(
        HitActor,
        Damage,
        InstigatorController,
        this,
        nullptr
    );
    
    UE_LOG(LogTemp, Log, TEXT("Hit actor: %s - Damage: %.1f"), 
           *HitActor->GetName(), Damage);
}
```

### 参考资料

- UE5 物理系统文档
- UMG 用户界面文档
- GameplayStatics 应用伤害 API

---

## 问题 008: 射击时HUD中弹药数没有变化

**状态**: ⚠️ 待解决  
**优先级**: 中（影响游戏体验）  
**发现日期**: 2026-03-11  
**相关任务**: T037, T053

### 问题描述

在游戏运行时，当玩家射击时，HUD中的弹药数量没有实时更新，导致玩家无法准确了解当前剩余弹药。

### 根本原因

**C++代码中未添加子弹对应的委托**：
- FPSWeapon类中没有定义弹药变化的委托（Delegate）
- 当子弹数量变化时，没有通知HUD进行更新
- 缺少从C++到蓝图的通信机制

### 解决方案

1. **修改C++代码，添加委托**：
   - 在FPSWeapon.h中添加弹药变化的委托声明
   - 在Fire()和Reload()函数中触发委托
   - 确保委托传递当前弹药数量信息

2. **在蓝图中部署**：
   - 在WBP_HUD蓝图中绑定到弹药变化委托
   - 创建更新HUD弹药显示的函数
   - 确保HUD能够接收到并显示最新的弹药数量

3. **测试验证**：
   - 运行游戏并进行射击测试
   - 确认HUD中的弹药数量能够实时更新
   - 测试换弹功能时的弹药数量变化

---

*最后更新：2026-03-11*  
*维护者：开发团队*
