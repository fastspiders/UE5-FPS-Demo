<#
Spec-Kit + Qoder 对接脚本：
1. 接收 Spec-Kit 需求文本
2. 调用 Qoder AI 生成规范/方案/任务
3. 自动写入 Spec-Kit 标准文件
#>
param(
    [Parameter(Mandatory=$true)]
    [string]$prompt,  # 你的 UE 功能需求
    [Parameter(Mandatory=$true)]
    [string]$type     # 生成类型：spec/plan/tasks
)

# 1. 生成功能编号（Spec-Kit 规范格式）
$featureNum = (Get-ChildItem -Path ./specs -Directory -ErrorAction SilentlyContinue).Count + 1
# 修正：分步处理字符串，避免语法错误
$cleanName = $prompt -replace '[^\w\s]', '' -replace '\s+', '-'
$featureName = $cleanName.Substring(0, [Math]::Min(20, $cleanName.Length))
$featureDir = "./specs/$($featureNum.ToString('000'))-$featureName"

# 2. 创建 Spec-Kit 标准目录
if (-not (Test-Path $featureDir)) {
    New-Item -ItemType Directory -Path $featureDir | Out-Null
}

# 3. 调用 Qoder AI 生成对应内容
$qoderPrompt = switch ($type) {
    "spec" {
        @"
请严格按照 Spec-Kit 规范驱动开发（SDD）格式，生成 UE 游戏功能规范文档（spec.md），要求：
1. 标题：$prompt
2. 结构包含：需求背景、核心功能、验收标准、UE 适配要求（C++/蓝图）
3. 格式为 Markdown，语言为中文，适配 UE 5.3+
"@
    }
    "plan" {
        @"
基于以下 UE 功能规范，生成 Spec-Kit 标准技术方案（plan.md）：
需求：$prompt
要求：
1. 结构：架构设计、UE 模块划分、C++/蓝图分工、性能优化
2. 适配 UE 5.3，考虑帧率/包体/平台兼容性
3. 格式为 Markdown
"@
    }
    "tasks" {
        @"
基于以下 UE 技术方案，拆解为 Spec-Kit 标准可执行任务（tasks.md）：
方案：$prompt
要求：
1. 每个任务包含：编号、描述、技术栈（C++/蓝图/材质）、预估工时
2. 适配 UE 开发流程，从编码到测试
3. 格式为 Markdown 列表
"@
    }
}

# 4. 调用 Qoder CLI 生成内容并写入文件
$output = qodercli -p $qoderPrompt
$output | Out-File -Path "$featureDir/$type.md" -Encoding utf8

# 5. 输出结果提示
Write-Host "✅ Qoder 已生成 $type.md 文件：$featureDir/$type.md"
Write-Host "`n生成内容预览："
Get-Content -Path "$featureDir/$type.md" -Head 10