# Hw 2

### 作业描述

实现rasterize_triangle(const Triangle& t)，画出一个实心三角形。流程如下：

    1. 创建三角形的二位bounding box

    2. 遍历bounding box内的所有像素（使用其整数索引）。然后，使用像素中心的屏幕空间坐标来检查中心点是否在三角形内。

    3. 如果在内部，则将其位置处的插值深度值(interpolated depth value)与深度缓冲区(depth buffer)中的相应值进行比较。

    4. 如果如果当前点更靠近相机，请设置像素颜色并更新深度缓冲区(depth buffer)。




判断一个点c是否在三角形内，c到三角形三个顶点的向量与三角形三条边的叉积方向相同
