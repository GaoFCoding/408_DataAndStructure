# 平衡二叉树

## 调整最小不平衡子树

![这是图片](./static/total.png "Magic Gardens")

### 1. LL 在A的左孩子的左子树中插入导致的不平衡

![这是图片](./static/LL.png "Magic Gardens")

### 2. RR 在A的右孩子的右子树中插入导致的不平衡

![这是图片](./static/RR.png "Magic Gardens")

### 3. LR 在A的左孩子的右子树中插入导致的不平衡

先左旋后右旋
![这是图片](./static/LR.png "Magic Gardens")

### 4. RL 在A的右孩子的左子树中插入导致的不平衡

先右旋后左旋
![这是图片](./static/RL.png "Magic Gardens")

### 左旋和右旋操作的代码实现

![这是图片](./static/code.png "Magic Gardens")

## 查找效率分析

![这是图片](./static/O.png "Magic Gardens")
根据Nh的递推公式可以算出深度为h的平衡二叉树含有的最少节点数

## 总结

![这是图片](./static/all.png "Magic Gardens")
