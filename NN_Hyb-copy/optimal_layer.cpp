#include "optimal_level.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 在源文件中定义变量
int g_OptimalSDPI = 6; // 默认使用SDPI=6作为最优层级

/**
 * 自适应层级选择策略函数
 * 分析电路结构，选择最优的SDPI层级来应用神经网络
 * @param iNoGate 电路中门的数量
 * @return 选择的最优SDPI层级
 */
int selectOptimalLevel(int iNoGate) {
    // 分析各层电路门的分布
    const int MAX_ANALYZE_LEVEL = 20; // 分析的最大层级数
    int levelDistribution[MAX_ANALYZE_LEVEL] = {0};
    
    // 统计各层级门的数量
    for (int i = 0; i < iNoGate; i++) {
        if (g_net[i]->dpi < MAX_ANALYZE_LEVEL) {
            levelDistribution[g_net[i]->dpi]++;
        }
    }
    
    // 对中间层进行评分
    int bestLevel = 6;  // 默认层级
    float bestScore = 0;
    int totalLevels = g_iMaxLevel + 1; // 电路的总层数
    
    // 只考虑3到电路最大层级-1之间的层
    // 通常最底层(靠近PI)和最顶层(靠近PO)不太适合作为决策层
    int minLevel = 3;
    int maxLevel = (totalLevels > 10) ? totalLevels - 3 : totalLevels - 1;
    maxLevel = (maxLevel < 9) ? maxLevel : 9; // 最高只考虑到第9层
    
    for (int level = minLevel; level <= maxLevel; level++) {
        // 考虑门数量和层级位置，中间层得分较高
        float levelPos = (float)level / totalLevels;
        float centralityScore = 1.0f - fabs(levelPos - 0.5f) * 2.0f; // 越接近中间位置得分越高
        
        // 满足最小门数量要求
        if (levelDistribution[level] < 10) continue;
        
        // 最终得分 = 门数量 × 中心位置得分
        float score = levelDistribution[level] * centralityScore;
        
        if (score > bestScore) {
            bestScore = score;
            bestLevel = level;
        }
    }
    
    printf("自适应层级选择: 选择SDPI=%d作为应用神经网络的最佳层级\n", bestLevel);
    return bestLevel;
}